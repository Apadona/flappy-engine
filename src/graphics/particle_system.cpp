#include "particle_system.hpp"
#include <utils/random.hpp>

ParticleSystem::ParticleSystem( uint32_t max_count, uint32_t start_count, double emition_rate, double particle_life_time, double whole_time, bool repeat )
{
    m_max_count = max_count;
    m_start_count = start_count;

    m_particles.reserve(m_max_count);

    for( uint32_t i = 0; i < m_start_count; ++i )
    {
        Particle particle;
        particle.m_position = Vec3(Random::NextDouble(0.0,0.1), -1 + Random::NextDouble(0.0,0.3),-1 + Random::NextDouble(0.0,0.1));
        particle.m_velocity = Vec3(Random::NextDouble(-0.01,0.01),Random::NextDouble(-0.01,0.01),Random::NextDouble(-0.01,0.01));
        m_particles.push_back(particle);
    }
    
    m_life_time_limit = particle_life_time;
    m_emition_rate = emition_rate;
    m_spent_time = 0.0;
    m_whole_time = whole_time;
    m_repeat = repeat;
    m_particle_spawn_time = 0.0;
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
        m_start_count = other.m_start_count;
        m_emition_rate = other.m_emition_rate;
        m_life_time_limit = other.m_life_time_limit;
        m_repeat = other.m_repeat;
    }

    return *this;
}

ParticleSystem& ParticleSystem::operator=( ParticleSystem&& other )
{
    if( this != &other )
    {
        m_particles = std::move(other.m_particles);
        m_start_count = other.m_start_count;
        m_emition_rate = other.m_emition_rate;
        m_life_time_limit = other.m_life_time_limit;
        m_repeat = other.m_repeat;

        other.m_start_count = 0;
        other.m_emition_rate = 0;
        other.m_life_time_limit = 0;
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
            i.life_time += dt;
            if( i.life_time >= m_life_time_limit ) // dead.
            {
                i.life_time = 0;
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