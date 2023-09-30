#pragma once

#include "particle.hpp"
#include "transform.hpp"
#include "texture.hpp"

#include <maths/vector4D.hpp>
#include <maths/curves.hpp>

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

        ParticleSystem();

        ParticleSystem( double whole_time, double particle_life_time, double emition_rate, uint32_t start_count, uint32_t max_count,
                        bool repeat = false, SpawnMode mode = SpawnMode::RECTANGLE );

        ParticleSystem(const ParticleSystem& other);

        ParticleSystem( ParticleSystem&& other );

        ~ParticleSystem();

        ParticleSystem& operator=( const ParticleSystem& other );

        ParticleSystem& operator=( ParticleSystem&& other );

        Particle& operator[]( uint32_t index );

        const Particle& operator[]( uint32_t index ) const;

        void Update( double dt ) ;

        void Reset() { m_spent_time = 0; }

        void SetStartColor( const Vec4f& start_color ) { m_start_color = start_color; }

        void SetEndColor( const Vec4f& end_color ) { m_end_color = end_color; }

        void SetWholeTime( double whole_time ) { m_whole_time = whole_time; }

        void SetEmitionRate( double emition_rate ) { m_emition_rate = emition_rate; }

        inline void SetParticleLifeTime( double particle_life_time )
        {
            if( std::islessequal(particle_life_time, std::numeric_limits<float>::epsilon()) )
            {
                throw std::range_error("error: particle life time should not be either 0 or so small.\n");
            }

            else
            {
                m_particle_life_time = particle_life_time;
            }
        }

        void SetSpawnMode( SpawnMode mode ) { m_spawn_mode = mode; }

        void SetTexture( const std::string path );

        void SetTexture( Texture& texture ) { m_texture = &texture; }

        void SetSizeOverLifeTimeBehaviour( const BezierCurve& curve ) { m_size_over_life_time_curve = curve; }

        void SetColorOverLifeTimeBehaviour( const BezierCurve& curve ) { m_color_over_life_time_curve = curve; }

        inline void SetMaxAllowedParticles( uint32_t max_particle_count )
        {
            m_max_count = max_particle_count;
            m_particles.reserve(m_max_count);
        }

        inline void SetStartParticleCount( uint32_t start_particle_count )
        {
            m_start_count = start_particle_count;

            for( uint32_t i = 0; i < m_start_count; ++i )
            {
                m_particles.push_back(GenerateParticle());
            }
        }

        void SetRepeating( bool repeat ) { m_repeat = repeat; }

        const Particles& GetParticles() const { return m_particles; }

        Texture* GetTexture() { return m_texture; }

        const Vec4f& GetStartColor() const { return m_start_color; }

        const Vec4f& GetEndColor() const { return m_end_color; } 

        double GetWholeTime() const { return m_whole_time; }

        double GetSpentTime() const { return m_spent_time; }

        uint32_t GetStartCount() const { return m_start_count; }

        uint32_t GetCurrentCount() { return m_particles.size(); }

        uint32_t GetMaxCount() { return m_particles.capacity(); }

        double GetEmitionRate() const { return m_emition_rate; }

        double GetTimeFromLastParticleSpawn() const { return m_particle_spawn_time; }

        double GetLifeTimeLimit() const { return m_particle_life_time; }

        SpawnMode getSpawnMode() const { return m_spawn_mode; }

        BezierCurve GetSizeOverLifeTimeBehaviour() const { return m_size_over_life_time_curve; }

        BezierCurve GetColorOverLifeTimeBehaviour() const { return m_color_over_life_time_curve; }

        bool IsRepeating() const { return m_repeat; }

    private:
        std::uint32_t getFirstDeadParticleIndex( std::uint32_t index ) const;
        std::uint32_t getDeadParticles() const;

        Particle GenerateParticle() const;

        void RegisterDeadParticle( int64_t index );

        int64_t FindFirstDeadParticleIndex();

    private:
        // list of the particles which are made and managed.
        Particles m_particles;

        // texture that gets applied to all particles within a particle system.
        Texture* m_texture;

        // when a particle dies i.e particle.m_life_time gets exceeds by particlesystem.m_particle_life_time, its index from the vector
        // gets stored here. so that when a new particle is to be emitted it would use this index to index into the dead particles'
        // vector memory storage instead of allocating a new one (if possible though).
        std::vector<int64_t> m_deadParticleIndexes;

        Vec4f m_start_color;

        Vec4f m_end_color;

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
        double m_particle_life_time; 

        // decides in what shape to emit particles( circle,cone,cube, etc... )
        SpawnMode m_spawn_mode;

        // it specifies how the size of particles changes based on the time that has passed after their creation.
        BezierCurve m_size_over_life_time_curve;

        // it specifies how the color of the particles changes based on the time that has passed after their creation.
        BezierCurve m_color_over_life_time_curve;

        // if set to false, particle system stops emiting particles after the time that it is active (m_spent_time) is greater than
        // its whole time (m_whole_time).
        bool m_repeat;

        // if set to false, particle system stops emiting particles but its acitve time (m_spent_time) gets increased by update time.
        // this could be used to interrupt or delay the work of a particle system. 
        bool m_active;
};

Vec3d RectangleSpawner( Vec3d center, Vec3d oriention, double length_x, double length_y );

Vec3d CircleSpawner( Vec3d center, Vec3d oriention, double radius );

Vec3d CubeSpawner( Vec3d center, Vec3d oriention, double length );

Vec3d SphereSpawner( Vec3d center, double radius );

Vec3d ConeSpawner( Vec3d center, Vec3d oriention, double inner_radius, double outer_radius, double height );