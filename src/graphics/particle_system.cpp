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
    m_current_count = 0;
    m_max_count = 0;
    m_emition_rate = 0;
    m_particle_spawn_time = 0;
    m_particle_life_time = 0;
    m_spawn_mode = SpawnMode::NONE;
    m_repeat = false;
    m_active = true;
    m_enable_sprite_sheet = false;
}

ParticleSystem::ParticleSystem( double whole_time, double particle_life_time, double emition_rate, uint32_t start_count, uint32_t max_count,
                                bool repeat, SpawnMode mode ) : Transform3D()
{
    m_texture = nullptr;
    m_start_color = Vec4f(1.0f,1.0f,1.0f,1.0f);
    m_end_color = Vec4f(1.0f,1.0f,1.0f,1.0f);
    m_whole_time = whole_time;
    m_spent_time = 0;
    m_start_count = start_count;
    m_current_count = m_start_count;
    m_max_count = max_count;
    m_emition_rate = emition_rate;
    m_particle_spawn_time = 0;
    m_particle_life_time = particle_life_time;
    m_spawn_mode = mode;
    m_repeat = repeat;
    m_active =  true;
    m_enable_sprite_sheet = false;

    m_dead_particle_indexes.resize(m_max_count,0); // 0 -> alive. 1 -> dead.
    m_particles.reserve(m_max_count);

    PushParticles(m_start_count);
}

ParticleSystem::ParticleSystem( const ParticleSystem& other ) : Transform3D()
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
        m_dead_particle_indexes = other.m_dead_particle_indexes;
        m_start_color = other.m_start_color;
        m_end_color = other.m_end_color;
        m_whole_time = other.m_whole_time;
        m_spent_time = other.m_spent_time;
        m_start_count = other.m_start_count;
        m_current_count = other.m_current_count;
        m_max_count = other.m_max_count;
        m_emition_rate = other.m_emition_rate;
        m_particle_spawn_time = other.m_particle_spawn_time;
        m_particle_life_time = other.m_particle_life_time;
        m_spawn_mode = other.m_spawn_mode;
        m_repeat = other.m_repeat;
        m_active = other.m_active;
        m_enable_sprite_sheet = other.m_enable_sprite_sheet;
    }

    return *this;
}

ParticleSystem& ParticleSystem::operator=( ParticleSystem&& other )
{
    if( this != &other )
    {
        m_particles = std::move(other.m_particles);
        m_texture = other.m_texture;
        
        m_dead_particle_indexes = std::move(other.m_dead_particle_indexes);
        m_start_color = other.m_start_color;
        m_end_color = other.m_end_color;
        m_whole_time = other.m_whole_time;
        m_spent_time = other.m_spent_time;
        m_start_count = other.m_start_count;
        m_current_count = other.m_current_count;
        m_max_count = other.m_max_count;
        m_emition_rate = other.m_emition_rate;
        m_particle_spawn_time = other.m_particle_spawn_time;
        m_particle_life_time = other.m_particle_life_time;
        m_spawn_mode = other.m_spawn_mode;
        m_repeat = other.m_repeat;
        m_active = other.m_active;
        m_enable_sprite_sheet = other.m_enable_sprite_sheet;

        other.m_texture = nullptr;
        m_start_color = Vec4f(1.0f,1.0f,1.0f,0.0f);
        m_end_color = Vec4f(1.0f,1.0f,1.0f,0.0f);
        other.m_whole_time = false;
        other.m_spent_time = 0;
        other.m_start_count = 0;
        other.m_current_count = 0;
        other.m_max_count = 0;
        other.m_emition_rate = 0;
        other.m_particle_spawn_time = 0;
        other.m_particle_life_time = 0;
        other.m_spawn_mode = SpawnMode::NONE;
        other.m_repeat = false;
        other.m_active = false;
        other.m_enable_sprite_sheet = false;
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
    if( !m_active )
        return;

    m_spent_time += dt;

    // where all the logic about particle Generation happens.
    if( m_spent_time < m_whole_time || m_repeat )
    {
        if( m_current_count < m_max_count )
        {
            m_particle_spawn_time += dt;

            while( m_particle_spawn_time >= m_emition_rate )
            {
                int64_t index = FindFirstDeadParticleIndex();

                if( index == -1 )
                    m_particles.push_back(GenerateParticle());

                else
                    m_particles[index] = GenerateParticle();

                m_current_count++;
                m_particle_spawn_time -= m_emition_rate;
            }
        }
    }

    // where all the logic about particle update happens.
    for( size_t particle_index = 0; particle_index < m_particles.size(); ++particle_index )
    {
        Particle& particle = m_particles[particle_index];

        particle.m_life_time += dt;
        if( particle.m_life_time >= m_particle_life_time && !particle.m_is_dead ) // particle is now dead.
        {
            particle.m_is_dead = true;
            RegisterDeadParticle(particle_index);
        }

        else // particle is alive.
        {
            particle.m_position += particle.m_velocity * dt;
            double particle_life_percentage = particle.m_life_time / m_particle_life_time;
            double calculated = m_size_over_life_time_curve.Calculate(particle_life_percentage);
            particle.m_scale = Vec3f(calculated,calculated,calculated);
            double relative = particle.m_life_time / m_particle_life_time;
            particle.m_color = m_start_color * ( 1 - relative ) + m_end_color * relative;
            
            if( m_enable_sprite_sheet )
                m_atlas.ProceedByTime(dt);
        }
    }
}

void ParticleSystem::SetTexture( const std::string& path )
{
    Texture* texture = new Texture(path);
    if( texture )
    {
        SetTexture(*texture);
    }
}

void ParticleSystem::SetTexture( Texture& texture )
{
    if( texture )
    {
        m_texture = &texture;
        m_atlas.SetTexture(*m_texture);
        TextureManager::Get().UseTexture(*m_texture);
    }
}

void ParticleSystem::Reset()
{
    m_current_count = 0;
    m_spent_time = 0;
    m_particle_spawn_time = 0;

    m_dead_particle_indexes.clear();
    m_dead_particle_indexes.resize(m_max_count,0);

    m_particles.clear();

    PushParticles(m_start_count);
}

Particle ParticleSystem::GenerateParticle() const
{
    Particle particle;

    switch( m_spawn_mode )
    {
        case SpawnMode::NONE: // just spawn at random positions. 
            particle.m_position = Vec3f(Random::NextFloat(0.0f,0.1f), -1 + Random::NextFloat(0.0f,0.3f),-1 + Random::NextFloat(0.0f,0.1f));
        break;

        case SpawnMode::RECTANGLE:
            particle.m_position = RectangleSpawner(GetPosition(),GetRotation(),0.2f,0.2f);
        break;

        case SpawnMode::CIRCLE:
            particle.m_position = CircleSpawner(GetPosition(),{0.0f,0.0f,0.0f},0.5f);
        break;

        case SpawnMode::CUBE:
            particle.m_position = CubeSpawner(GetPosition(),{0.0f,0.0f,0.0f},0.5f);
        break;

        case SpawnMode::SPHERE:
            particle.m_position = SphereSpawner(GetPosition(),0.5f);
        break;

        case SpawnMode::CONE:
            particle.m_position = ConeSpawner(GetPosition(),{0.0f,0.0f,0.0f},0.5f,0.5f,1.0f);
        break;
    }   

    particle.m_velocity = Vec3f(0.0f,0.3f,0.0f);

    return particle;
}

void ParticleSystem::PushParticles( int64_t particle_count )
{
    for( int i = 0; i < particle_count; ++i )
    {
        m_particles.push_back(GenerateParticle());
    }

    m_current_count += particle_count;
}

void ParticleSystem::RegisterDeadParticle( int64_t index )
{
    for( size_t j = 0; j < m_dead_particle_indexes.size(); ++j )
    {
        if ( m_dead_particle_indexes[j] == -1 )
        {
            m_dead_particle_indexes[j] = index;
            m_current_count--;

            return;
        }
    }
}

int64_t ParticleSystem::FindFirstDeadParticleIndex()
{
    for( size_t i = 0; i < m_dead_particle_indexes.size(); ++i )
    {
        int64_t index = m_dead_particle_indexes[i];

        if( index != -1 )
        {
            m_dead_particle_indexes[i] = -1;
            return index;
        }
    }

    return -1;
}

Vec3f RectangleSpawner( Vec3f center, Vec3f oriention, float length_x, float length_y )
{
    // Vec3f spawn_position,spawn_velocity,spawn_acceleration;
    // Vec3f upper_left_corner = {center.x - length_x / 2, center.y - length_y / 2, center.z};

    Vec3f spawn_position;

    spawn_position.x = Random::NextDouble(0.0,1.0) * length_x / 2 + center.x;
    spawn_position.y = Random::NextDouble(0.0,1.0) * length_y / 2 + center.y;

    return spawn_position;
}

Vec3f CircleSpawner( Vec3f center, Vec3f oriention, float radius )
{
    Vec3f spawn_position;

    spawn_position.x = std::sin(Random::NextDouble(0.0,1.0)) * radius + center.x;
    spawn_position.y = std::cos(Random::NextDouble(0.0,1.0)) * radius + center.y;

    return spawn_position;
}

Vec3f CubeSpawner( Vec3f center, Vec3f oriention, float length )
{
    Vec3f upper_left_corner = {center.x - length / 2, center.y - length / 2, center.z - length / 2};

    Vec3f spawn_position;

    spawn_position.x = Random::NextDouble(0.0,1.0) * length + upper_left_corner.x;
    spawn_position.y = Random::NextDouble(0.0,1.0) * length + upper_left_corner.y;
    spawn_position.z = Random::NextDouble(0.0,1.0) * length + upper_left_corner.z;

    return spawn_position;
}

Vec3f SphereSpawner( Vec3f center, float radius )
{
    Vec3f spawn_position;

    spawn_position.x = std::sin(Random::NextDouble(0.0,1.5)) * radius + center.x;
    spawn_position.y = std::cos(Random::NextDouble(0.0,1.5)) * radius + center.y;

    return spawn_position;
}

Vec3f ConeSpawner( Vec3f center, Vec3f oriention, float inner_radius, float outer_radius, float height )
{
    return {0.0,0.0,0.0};
}
