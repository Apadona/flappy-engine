#include "particle_system.hpp"
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
    m_life_time_limit = particle_life_time;
    m_repeat = repeat;
    m_spawn_mode = mode;

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
        m_life_time_limit = other.m_life_time_limit;
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
        m_life_time_limit = other.m_life_time_limit;
        m_spawn_mode = other.m_spawn_mode;
        m_repeat = other.m_repeat;

        other.m_whole_time = false;
        other.m_spent_time = 0;
        other.m_start_count = 0;
        other.m_max_count = 0;
        other.m_emition_rate = 0;
        other.m_particle_spawn_time = 0;
        other.m_life_time_limit = 0;
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

void ParticleSystem::update( double dt )
{
    m_spent_time += dt;

    if( m_spent_time < m_whole_time  )
    {
        m_particle_spawn_time += dt;
        if( m_particle_spawn_time > m_emition_rate )
        {
            while( m_particle_spawn_time >= m_emition_rate && m_particles.size() < m_max_count )
            {
                Particle particle;
                particle.m_position = Vec3(Random::NextDouble(0.0,0.1),-1 + Random::NextDouble(0.0,0.3),Random::NextDouble(0.0,0.1));
                m_particles.push_back(particle);
                m_particle_spawn_time -= m_emition_rate;
            }

        }

        for( auto& i : m_particles )
        {
            i.m_life_time += dt;
            if( i.m_life_time >= m_life_time_limit ) // dead.
            {
                i.m_life_time = 0;
                i.m_position = Vec3(Random::NextDouble(0.0,0.1), -1 + Random::NextDouble(0.0,0.3),Random::NextDouble(0.0,0.1));
                i.m_velocity = Vec3(Random::NextDouble(-0.01,0.01),Random::NextDouble(-0.01,0.01),Random::NextDouble(-0.01,0.01));
            }

            else // alive
            {
                i.m_position += i.m_velocity;
            }
        }
    }

    else
    {
        if( m_repeat == true )
        {
            m_spent_time = 0.0;
        }
    }
}

Particle ParticleSystem::GenerateParticle() const
{
    Particle particle;
    particle.m_position = Vec3(Random::NextDouble(0.0,0.1), -1 + Random::NextDouble(0.0,0.3),-1 + Random::NextDouble(0.0,0.1));
    particle.m_velocity = Vec3(Random::NextDouble(-0.01,0.01),Random::NextDouble(-0.01,0.01),Random::NextDouble(-0.01,0.01));

    return particle;
}


Particle RectangleSpawner( Vec3d center, Vec3d oriention, double length_x, double length_y )
{
    // Vec3d spawn_position,spawn_velocity,spawn_acceleration;
    Vec3d upper_left_corner = {center.x - length_x / 2, center.y - length_y / 2, center.z};

    Particle to_be_spawned;
    to_be_spawned.m_life_time = 0;
    to_be_spawned.m_position.x = Random::NextDouble(0.0,1.0) * length_x + upper_left_corner.x;
    to_be_spawned.m_position.y = Random::NextDouble(0.0,1.0) * length_y + upper_left_corner.y;
    to_be_spawned.m_velocity = Vec3(Random::NextDouble(-0.01,0.01),Random::NextDouble(-0.01,0.01),Random::NextDouble(-0.01,0.01));

    return to_be_spawned;
}

Particle CircleSpawner( Vec3d center, Vec3d oriention, double radius )
{
    Particle to_be_spawned;
    to_be_spawned.m_life_time = 0;
    to_be_spawned.m_position.x = std::sin(Random::NextDouble(0.0,1.5)) * radius + center.x;
    to_be_spawned.m_position.y = std::cos(Random::NextDouble(0.0,1.5)) * radius + center.y;
    to_be_spawned.m_velocity = Vec3(Random::NextDouble(-0.01,0.01),Random::NextDouble(-0.01,0.01),Random::NextDouble(-0.01,0.01));

    return to_be_spawned;
}

Particle CubeSpawner( Vec3d center, Vec3d oriention, double length )
{
    Vec3d upper_left_corner = {center.x - length / 2, center.y - length / 2, center.z - length / 2};

    Particle to_be_spawned;
    to_be_spawned.m_life_time = 0;
    to_be_spawned.m_position.x = Random::NextDouble(0.0,1.0) * length + upper_left_corner.x;
    to_be_spawned.m_position.y = Random::NextDouble(0.0,1.0) * length + upper_left_corner.y;
    to_be_spawned.m_position.z = Random::NextDouble(0.0,1.0) * length + upper_left_corner.z;
    to_be_spawned.m_velocity = Vec3(Random::NextDouble(-0.01,0.01),Random::NextDouble(-0.01,0.01),Random::NextDouble(-0.01,0.01));

    return to_be_spawned;
}

Particle SphereSpawner( Vec3d center, double radius )
{
    Particle to_be_spawned;
    to_be_spawned.m_life_time = 0;
    to_be_spawned.m_position.x = std::sin(Random::NextDouble(0.0,1.5)) * radius + center.x;
    to_be_spawned.m_position.y = std::cos(Random::NextDouble(0.0,1.5)) * radius + center.y;
    to_be_spawned.m_velocity = Vec3(Random::NextDouble(-0.01,0.01),Random::NextDouble(-0.01,0.01),Random::NextDouble(-0.01,0.01));

    return to_be_spawned;
}

Particle ConeSpawner( Vec3d center, Vec3d oriention, double inner_radius, double outer_radius, double height )
{
    
}
