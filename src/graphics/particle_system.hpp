#pragma once

#include "particle.hpp"
#include "transform_2D.hpp"

class ParticleSystem
{
    public:
        using Particles = std::vector<Particle>;

        // using iterator = Particles::iterator;
        // using const_iterator = Particles::const_iterator;
        // using reverse_iterator = Particles::reverse_iterator;
        // using const_reverse_iterator = Particles::const_reverse_iterator;

        // iterator begin() { return m_particles.begin(); }

        // iterator end() { return m_particles.end(); }

        // const_iterator cbegin() const { return m_particles.cbegin(); }

        // const_iterator cend() const { return m_particles.cend(); }

        // reverse_iterator rbegin() const { return m_particles.rbegin(); }

        // reverse_iterator rend() const { return m_particles.rend(); }

        // const_reverse_iterator crbegin() const { return m_particles.crbegin(); }

        // const_reverse_iterator crend() const { return m_particles.crend(); }

        ParticleSystem(uint32_t max_count, uint32_t start_count, double emition_rate, double duration, double whole_time, bool repeat = true);

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

        double GetLifeTimeLimit() const { return m_life_time_limit; }
        
        bool isRepeating() const { return m_repeat; }

    private:
        std::uint32_t getFirstDeadParticleIndex(std::uint32_t index) const;
        std::uint32_t getDeadParticles() const;

    private:
        Particles m_particles;
        uint32_t m_max_count;
        uint32_t m_start_count;
        double m_emition_rate;
        double m_spent_time;
        double m_particle_spawn_time;
        double m_life_time_limit; // particle life time.
        double m_whole_time;
        bool m_repeat;
};