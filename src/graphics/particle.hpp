#pragma once

#include <maths/vector3D.hpp>

struct Particle
{
    Particle()
    {
        std::memset(this,0,sizeof(this));
    }

    Particle( const Particle& other )
    {
        *this = other;
    }

    Particle& operator=( const Particle& other )
    {
        if( this != &other )
        {
            m_position = other.m_position;
            m_scale = other.m_scale;
            m_rotation = other.m_rotation;
        
            m_velocity = other.m_velocity;
            m_acceleration = other.m_acceleration;

            m_life_time = other.m_life_time;

            m_is_dead = other.m_is_dead;
        }

        return *this;
    }

    Vec3 m_position;
    Vec3 m_scale;
    Vec3 m_rotation;

    Vec3 m_velocity;
    Vec3 m_acceleration;

    double m_life_time;

    bool m_is_dead;
};