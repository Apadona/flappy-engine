#include "particle_system.hpp"
#include "texture_manager.hpp"
#include <utils/random.hpp>


ParticleSystem::ParticleSystem( double whole_time, double particle_life_time, double emition_rate, uint32_t start_count, uint32_t max_count,
                                bool repeat, SpawnMode mode )
{
    m_whole_time = whole_time;
    m_spent_time = 0;
    m_start_count = start_count;
    m_max_count = max_count;
    m_emition_rate = emition_rate;
    m_particle_spawn_time = 0;
    m_particle_life_time = particle_life_time;
    m_repeat = repeat;
    m_spawn_mode = mode;

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
        m_whole_time = other.m_whole_time;
        m_spent_time = other.m_spent_time;
        m_start_count = other.m_start_count;
        m_max_count = other.m_max_count;
        m_emition_rate = other.m_emition_rate;
        m_particle_spawn_time = other.m_particle_spawn_time;
        m_particle_life_time = other.m_particle_life_time;
        m_spawn_mode = other.m_spawn_mode;
        m_repeat = other.m_repeat;
    }

    return *this;
}

ParticleSystem& ParticleSystem::operator=( ParticleSystem&& other )
{
    if( this != &other )
    {
        m_particles = std::move(other.m_particles);
        m_whole_time = other.m_whole_time;
        m_spent_time = other.m_spent_time;
        m_start_count = other.m_start_count;
        m_max_count = other.m_max_count;
        m_emition_rate = other.m_emition_rate;
        m_particle_spawn_time = other.m_particle_spawn_time;
        m_particle_life_time = other.m_particle_life_time;
        m_spawn_mode = other.m_spawn_mode;
        m_repeat = other.m_repeat;

        other.m_whole_time = false;
        other.m_spent_time = 0;
        other.m_start_count = 0;
        other.m_max_count = 0;
        other.m_emition_rate = 0;
        other.m_particle_spawn_time = 0;
        other.m_particle_life_time = 0;
        other.m_spawn_mode = SpawnMode::NONE;
        other.m_repeat = false;
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
            particle.m_position = Vec3(Random::NextDouble(0.0,0.1), -1 + Random::NextDouble(0.0,0.3),-1 + Random::NextDouble(0.0,0.1));
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

    particle.m_velocity = Vec3(0.0,Random::NextDouble(0.0,0.15),0.0);
    particle.m_is_dead = false;

    return particle;
}   

void ParticleSystem::RegisterDeadParticle( int64_t index )
{
    
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


Vec3 RectangleSpawner( Vec3d center, Vec3d oriention, double length_x, double length_y )
{
    // Vec3d spawn_position,spawn_velocity,spawn_acceleration;
    Vec3 upper_left_corner = {center.x - length_x / 2, center.y - length_y / 2, center.z};

    Vec3 spawn_position;

    spawn_position.x = Random::NextDouble(0.0,1.0) * length_x / 2 + center.x;
    spawn_position.y = Random::NextDouble(0.0,1.0) * length_y / 2 + center.y;

    return spawn_position;
}

Vec3 CircleSpawner( Vec3d center, Vec3d oriention, double radius )
{
    Vec3 spawn_position;

    spawn_position.x = std::sin(Random::NextDouble(0.0,1.0)) * radius + center.x;
    spawn_position.y = std::cos(Random::NextDouble(0.0,1.0)) * radius + center.y;

    return spawn_position;
}

Vec3 CubeSpawner( Vec3d center, Vec3d oriention, double length )
{
    Vec3 upper_left_corner = {center.x - length / 2, center.y - length / 2, center.z - length / 2};

    Vec3 spawn_position;

    spawn_position.x = Random::NextDouble(0.0,1.0) * length + upper_left_corner.x;
    spawn_position.y = Random::NextDouble(0.0,1.0) * length + upper_left_corner.y;
    spawn_position.z = Random::NextDouble(0.0,1.0) * length + upper_left_corner.z;

    return spawn_position;
}

Vec3 SphereSpawner( Vec3d center, double radius )
{
    Vec3 spawn_position;

    spawn_position.x = std::sin(Random::NextDouble(0.0,1.5)) * radius + center.x;
    spawn_position.y = std::cos(Random::NextDouble(0.0,1.5)) * radius + center.y;

    return spawn_position;
}

Vec3 ConeSpawner( Vec3d center, Vec3d oriention, double inner_radius, double outer_radius, double height )
{
    return {0.0,0.0,0.0};
}
