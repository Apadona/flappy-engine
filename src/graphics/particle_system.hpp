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

        ParticleSystem( double whole_time, double particle_life_time, double emition_rate, uint32_t start_count, uint32_t max_count,
                        bool repeat = false, SpawnMode mode = SpawnMode::RECTANGLE );

        ParticleSystem(const ParticleSystem& other);

        ParticleSystem( ParticleSystem&& other );

        ParticleSystem& operator=( const ParticleSystem& other );

        ParticleSystem& operator=( ParticleSystem&& other );

        Particle& operator[]( uint32_t index );

        const Particle& operator[]( uint32_t index ) const;

        void update(double dt);

        const Particles& GetParticles() const { return m_particles; }

        void SetLifeTimeLimit(double limit) { m_life_time_limit = limit; }

        uint32_t GetStartCount() const { return m_start_count; }

        uint32_t GetCurrentCount() { return m_particles.size(); }

        uint32_t GetMaxCount() { return m_particles.capacity(); }

        double GetEmitionRate() const { return m_emition_rate; }

        void setSpawnMode( SpawnMode mode ) { m_spawn_mode = mode; }

        SpawnMode getSpawnMode() const { return m_spawn_mode; }

        double GetLifeTimeLimit() const { return m_life_time_limit; }
        
        bool isRepeating() const { return m_repeat; }

    private:
        std::uint32_t getFirstDeadParticleIndex(std::uint32_t index) const;
        std::uint32_t getDeadParticles() const;

        Particle GenerateParticle() const;

    private:
        Particles m_particles;

        // the time that particle system should be active( emits particles. ) unless m_repeat is set to true.
        double m_whole_time;

        // the time that particle system has been active.
        double m_spent_time;

        // the start number of particles.
        uint32_t m_start_count;

        // the max number of particles that can exist at a time.
        uint32_t m_max_count;

        // emition parameters.
        // the rate at which a new particle is spawned.
        double m_emition_rate;

        // the time from the previous particle spawn.
        double m_particle_spawn_time;

        // particle life time. after this time is exceeded, it would die.
        double m_life_time_limit; 

        SpawnMode m_spawn_mode;

        bool m_repeat;
};

Particle RectangleSpawner( Vec3d center, Vec3d oriention, double length_x, double length_y );

Particle CircleSpawner( Vec3d center, Vec3d oriention, double radius );

Particle CubeSpawner( Vec3d center, Vec3d oriention, double length );

Particle SphereSpawner( Vec3d center, double radius );

Particle ConeSpawner( Vec3d center, Vec3d oriention, double inner_radius, double outer_radius, double height );