#include "particle_system.hpp"
#include "texture_manager.hpp"

#include <utils/random.hpp>

ParticleSystem::ParticleSystem()
{
    m_texture = nullptr;
    m_start_color = Vec4f(1.0,1.0,1.0,1.0);
    m_end_color = Vec4f(1.0,1.0,1.0,1.0);
    m_whole_time = 0;
    m_spent_time = 0;
    m_start_count = 0;
    m_max_count = 0;
    m_emition_rate = 0;
    m_particle_spawn_time = 0;
    m_particle_life_time = 0;
    m_spawn_mode = SpawnMode::NONE;
    m_repeat = false;
    m_active = true;
}

ParticleSystem::ParticleSystem( double whole_time, double particle_life_time, double emition_rate, uint32_t start_count, uint32_t max_count,
                                bool repeat, SpawnMode mode )
{
    m_texture = nullptr;
    m_start_color = Vec4f(1.0,1.0,1.0,1.0);
    m_end_color = Vec4f(1.0,1.0,1.0,1.0);
    m_whole_time = whole_time;
    m_spent_time = 0;
    m_start_count = start_count;
    m_max_count = max_count;
    m_emition_rate = emition_rate;
    m_particle_spawn_time = 0;
    m_particle_life_time = particle_life_time;
    m_spawn_mode = mode;
    m_repeat = repeat;
    m_active =  true;

    // m_deadParticleIndexes.resize(m_max_count,-1);
    m_particles.reserve(m_max_count);

    for( uint32_t i = 0; i < m_start_count; ++i )
    {
        m_particles.push_back(GenerateParticle());
    }
}

ParticleSystem::ParticleSystem( const ParticleSystem& other )
{
    *this = other;
}

ParticleSystem::ParticleSystem( ParticleSystem&& other )
{
    *this = std::forward<ParticleSystem>(other);
}

ParticleSystem::~ParticleSystem()
{
    if( m_texture )
    {
        delete m_texture;
    }
}

ParticleSystem& ParticleSystem::operator=( const ParticleSystem& other )
{
    if( this != &other )
    {
        m_particles = other.m_particles;
        m_texture = other.m_texture;
        m_deadParticleIndexes = other.m_deadParticleIndexes;
        m_start_color = other.m_start_color;
        m_end_color = other.m_end_color;
        m_whole_time = other.m_whole_time;
        m_spent_time = other.m_spent_time;
        m_start_count = other.m_start_count;
        m_max_count = other.m_max_count;
        m_emition_rate = other.m_emition_rate;
        m_particle_spawn_time = other.m_particle_spawn_time;
        m_particle_life_time = other.m_particle_life_time;
        m_spawn_mode = other.m_spawn_mode;
        m_repeat = other.m_repeat;
        m_active = other.m_active;
    }

    return *this;
}

ParticleSystem& ParticleSystem::operator=( ParticleSystem&& other )
{
    if( this != &other )
    {
        m_particles = std::move(other.m_particles);
        m_texture = other.m_texture;
        m_deadParticleIndexes = std::move(other.m_deadParticleIndexes);
        m_start_color = other.m_start_color;
        m_end_color = other.m_end_color;
        m_whole_time = other.m_whole_time;
        m_spent_time = other.m_spent_time;
        m_start_count = other.m_start_count;
        m_max_count = other.m_max_count;
        m_emition_rate = other.m_emition_rate;
        m_particle_spawn_time = other.m_particle_spawn_time;
        m_particle_life_time = other.m_particle_life_time;
        m_spawn_mode = other.m_spawn_mode;
        m_repeat = other.m_repeat;
        m_active = other.m_active;

        other.m_texture = nullptr;
        m_start_color = Vec4f(1.0f,1.0f,1.0f,0.0f);
        m_end_color = Vec4f(1.0f,1.0f,1.0f,0.0f);
        other.m_whole_time = false;
        other.m_spent_time = 0;
        other.m_start_count = 0;
        other.m_max_count = 0;
        other.m_emition_rate = 0;
        other.m_particle_spawn_time = 0;
        other.m_particle_life_time = 0;
        other.m_spawn_mode = SpawnMode::NONE;
        other.m_repeat = false;
        other.m_active = false;
    }

    return *this;
}

Particle& ParticleSystem::operator[]( uint32_t index )
{
    return m_particles.at(index);
}

const Particle& ParticleSystem::operator[]( uint32_t index ) const
{
    return m_particles.at(index);
}

void ParticleSystem::Update( double dt )
{
    m_spent_time += dt;

    if( m_spent_time < m_whole_time  )
    {
        // where all the logic about particle Generation happens.
        m_particle_spawn_time += dt;
        if( m_particle_spawn_time > m_emition_rate )
        {
            while( m_particle_spawn_time >= m_emition_rate && m_particles.size() < m_max_count )
            {
                int64_t index = FindFirstDeadParticleIndex();

                if( index == -1 )
                {
                    m_particles.push_back(GenerateParticle());
                }

                else
                {
                    m_particles[index] = GenerateParticle();
                }

                m_particle_spawn_time -= m_emition_rate;
            }
        }

        // where all the logic about particle update happens.
        for( int64_t i = 0; i < m_particles.size(); ++i )
        {
            Particle& particle = m_particles[i];

            particle.m_life_time += dt;
            if( particle.m_life_time >= m_particle_life_time ) // particle is dead.
            {
                particle.m_is_dead = true;
                m_deadParticleIndexes.push_back(i);
            }

            else // particle is alive.
            {
                particle.m_position += particle.m_velocity * dt;
                double particle_life_percentage = particle.m_life_time / m_particle_life_time;
                double calculated = m_size_over_life_time_curve.Calculate(particle_life_percentage);
                particle.m_scale = Vec3d(calculated,calculated,calculated);
                double relative = particle.m_life_time / m_particle_life_time;
                particle.m_color = m_start_color * ( 1 - relative ) + m_end_color * relative;
            }
        }
    }

    else 
    {
        if( m_repeat )
        {
            m_spent_time = 0.0;
        }
    }
}

void ParticleSystem::SetTexture( const std::string path )
{
    Texture* texture = new Texture(path);

    if( texture )
    {
        m_texture = texture;
        TextureManager::Get().UseTexture(*texture);
    }
}

Particle ParticleSystem::GenerateParticle() const
{
    Particle particle;

    switch( m_spawn_mode )
    {
        case SpawnMode::NONE: // just spawn at random positions. 
            particle.m_position = Vec3d(Random::NextDouble(0.0,0.1), -1 + Random::NextDouble(0.0,0.3),-1 + Random::NextDouble(0.0,0.1));
        break;

        case SpawnMode::RECTANGLE:
            particle.m_position = RectangleSpawner({0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},0.2,0.2);
        break;

        case SpawnMode::CIRCLE:
            particle.m_position = CircleSpawner({0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},0.5);
        break;

        case SpawnMode::CUBE:
            particle.m_position = CubeSpawner({0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},0.5);
        break;

        case SpawnMode::SPHERE:
            particle.m_position = SphereSpawner({0.0f,0.0f,0.0f},0.5);
        break;

        case SpawnMode::CONE:
            particle.m_position = ConeSpawner({0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},0.5,0.5,1.0);
        break;
    }   

    particle.m_velocity = Vec3d(0.0,0.3,0.0);

    return particle;
}   

void ParticleSystem::RegisterDeadParticle( int64_t index )
{
    (void)index;
}

int64_t ParticleSystem::FindFirstDeadParticleIndex()
{
    for( int i = 0; i < m_deadParticleIndexes.size(); ++i )
    {
        int64_t index = m_deadParticleIndexes[i];

        if( index != -1 )
        {
            m_deadParticleIndexes[i] = -1;
            return index;
        }
    }

    return -1;
}


Vec3d RectangleSpawner( Vec3d center, Vec3d oriention, double length_x, double length_y )
{
    // Vec3d spawn_position,spawn_velocity,spawn_acceleration;
    Vec3d upper_left_corner = {center.x - length_x / 2, center.y - length_y / 2, center.z};

    Vec3d spawn_position;

    spawn_position.x = Random::NextDouble(0.0,1.0) * length_x / 2 + center.x;
    spawn_position.y = Random::NextDouble(0.0,1.0) * length_y / 2 + center.y;

    return spawn_position;
}

Vec3d CircleSpawner( Vec3d center, Vec3d oriention, double radius )
{
    Vec3d spawn_position;

    spawn_position.x = std::sin(Random::NextDouble(0.0,1.0)) * radius + center.x;
    spawn_position.y = std::cos(Random::NextDouble(0.0,1.0)) * radius + center.y;

    return spawn_position;
}

Vec3d CubeSpawner( Vec3d center, Vec3d oriention, double length )
{
    Vec3d upper_left_corner = {center.x - length / 2, center.y - length / 2, center.z - length / 2};

    Vec3d spawn_position;

    spawn_position.x = Random::NextDouble(0.0,1.0) * length + upper_left_corner.x;
    spawn_position.y = Random::NextDouble(0.0,1.0) * length + upper_left_corner.y;
    spawn_position.z = Random::NextDouble(0.0,1.0) * length + upper_left_corner.z;

    return spawn_position;
}

Vec3d SphereSpawner( Vec3d center, double radius )
{
    Vec3d spawn_position;

    spawn_position.x = std::sin(Random::NextDouble(0.0,1.5)) * radius + center.x;
    spawn_position.y = std::cos(Random::NextDouble(0.0,1.5)) * radius + center.y;

    return spawn_position;
}

Vec3d ConeSpawner( Vec3d center, Vec3d oriention, double inner_radius, double outer_radius, double height )
{
    return {0.0,0.0,0.0};
}
