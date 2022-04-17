#pragma once

#include <maths/vector2D.hpp>
#include <maths/matrix.hpp>

struct Transform2D
{
    public:
        Transform2D();
        Transform2D( Vec2 position, Vec2 scale, float rotation );
        Transform2D( const Transform2D& other );

        Transform2D& operator=( const Transform2D& other );
        bool operator==( const Transform2D& other ) const;

        const Mat4f& CalculateModelMatrix(); // calculates and returns the matrix member variable.
        Mat4f GetModelMatrix() const; // returns a copy of the matrix member variable.

    public:
        Vec2 m_position;
        Vec2 m_scale;
        float m_rotation;

    private:
        Mat4f m_model_matrix;
};