#pragma once

#include <maths/vector3D.hpp>

struct Particle
{
    Vec3 m_position;
    Vec3 m_Scale;
    Vec3 m_rotation;

    Vec3 m_velocity;
    Vec3 m_acceleration;
    bool is_dead;

    double life_time;
};