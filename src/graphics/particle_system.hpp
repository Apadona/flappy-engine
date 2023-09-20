#pragma once

#include "particle.hpp"
#include "transform_2D.hpp"

enum class SpawnMode
{
    NONE,
    
    RECTANGLE,
    CIRCLE,
    CUBE,
    SPHERE,
    CONE
};

class ParticleSystem
{
    public:
        using Particles = std::vector<Particle>;

        ParticleSystem( double whole_time, double emition_rate, double particle_life_time, bool repeat = true, uint32_t max_count = 0,
                        uint32_t start_count = 0, SpawnMode mode = SpawnMode::RECTANGLE );

        ParticleSystem( const ParticleSystem& other );

        ParticleSystem( ParticleSystem&& other );

        ParticleSystem& operator=( const ParticleSystem& other );

        ParticleSystem& operator=( ParticleSystem&& other );

        Particle& operator[]( uint32_t index );

        const Particle& operator[]( uint32_t index ) const;

        void update(double dt);

        const Particles& GetParticles() const { return m_particles; }

        void SetLifeTimeLimit(double limit) { m_particle_life_time = limit; }

        uint32_t GetStartCount() const { return m_start_count; }

        uint32_t GetCurrentCount() { return m_particles.size(); }

        uint32_t GetMaxCount() { return m_particles.capacity(); }

        double GetEmitionRate() const { return m_emition_rate; }

        void setSpawnMode( SpawnMode mode ) { m_spawn_mode = mode; }

        SpawnMode getSpawnMode() const { return m_spawn_mode; }

        double GetLifeTimeLimit() const { return m_particle_life_time; }
        
        bool isRepeating() const { return m_repeat; }

    private:
        Particle GenerateNewParticle();
        std::uint32_t getFirstDeadParticleIndex(std::uint32_t index) const;
        std::uint32_t getDeadParticles() const;

    private:
        Particles m_particles;

         // the time that particle system should be active (unless repeating is specified).
        double m_whole_time;

         // the time that is spent since particle system started.
        double m_spent_time;

         // particle life time. after exceeding this, particle dies.
        double m_particle_life_time;

        // Vec3 m_start_size;

        // Vec3 m_start_speed;

        // maximum count of the particles that can be active.
        uint32_t m_max_count;

        // particles that should be spawned together at the start.
        uint32_t m_start_count;

        // if set to true, then it would reset and spawn particles again from start.
        bool m_repeat;

        // emition parameters.

         // the rate in seconds which a new particle should be spawned.
        double m_emition_rate;

         // the time that is passed since last spawn. once this exceeds m_emition_rate, it would spawn a particle.
        double m_particle_spawn_time;

        SpawnMode m_spawn_mode;
};

Particle RectangleSpawner( Vec3d center, Vec3d oriention, double length_x, double length_y );

Particle CircleSpawner( Vec3d center, Vec3d oriention, double radius );

Particle CubeSpawner( Vec3d center, Vec3d oriention, double length );

Particle SphereSpawner( Vec3d center, double radius );

Particle ConeSpawner( Vec3d center, Vec3d oriention, double inner_radius, double outer_radius, double height );