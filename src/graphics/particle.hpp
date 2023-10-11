#pragma once

#include <maths/vector3D.hpp>
#include <maths/vector4D.hpp>

struct Particle
{
    Particle() : m_position(0.0f,0.0f,0.0f) , m_scale(1.0f,1.0f,1.0f), m_rotation(0.0f,0.0f,0.0f),
                 m_velocity(0.0f,0.0f,0.0f), m_acceleration(0.0f,0.0f,0.0f), m_color(1.0f,1.0f,1.0f,1.0f), 
                 m_life_time(0.0f), m_is_dead(false) {}

    Particle( const Particle& other )
    {
        *this = other;
    }

    inline Particle& operator=( const Particle& other )
    {
        if( this != &other )
        {
            m_position = other.m_position;
            m_scale = other.m_scale;
            m_rotation = other.m_rotation;
        
            m_velocity = other.m_velocity;
            m_acceleration = other.m_acceleration;

            m_color = other.m_color;

            m_life_time = other.m_life_time;

            m_is_dead = other.m_is_dead;

        }

        return *this;
    }

    Vec3f m_position;
    Vec3f m_scale;
    Vec3f m_rotation;

    Vec3f m_velocity;
    Vec3f m_acceleration;

    Vec4f m_color;

    double m_life_time;

    bool m_is_dead;
};