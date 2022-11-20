#pragma once

#include <maths/vector2D.hpp>
#include <maths/matrix.hpp>
#include <maths/matrix_operations.hpp>

class Transform2D
{
    public:
        Transform2D();
        Transform2D( float pos_x, float pos_y = 0.0f, float scale_x = 1.0f, float scale_y = 1.0f, float rotation = 0.0f );
        Transform2D( Vec2 position, Vec2 scale, float rotation );
        Transform2D( const Transform2D& other );

        void SetPosition( float pos_x, float pos_y )
        {
            m_position = {pos_x,pos_y};
            m_model_matrix = Translate(m_position.x,m_position.y,0.0f,m_model_matrix);
        }

        void SetScale( float scale_x, float scale_y )
        {
            m_scale = {scale_x,scale_y};
            m_model_matrix = Scale(m_scale.x,m_scale.y,1.0f,m_model_matrix);
        }

        void SetRotation( float rotation )
        {
            m_rotation = rotation;
            m_model_matrix = Rotate(0.0f,0.0f,m_rotation,m_model_matrix);
        }

        Vec2 GetPosition() const { return m_position; }
        Vec2 GetScale() const { return m_scale; }
        float GetRotation() const { return m_rotation; }

        // should return a copy of the matrix member variable, because we cannot let the user modify the
        // model matrix by hand without modifying the position/scale/rotation. since they are related to each other.
        Mat4f GetModelMatrix() const;

        Transform2D& operator=( const Transform2D& other );
        bool operator==( const Transform2D& other ) const;


    private:
        void CalculateModelMatrix();

    private:
        Vec2 m_position;
        Vec2 m_scale;
        float m_rotation;

        Mat4f m_model_matrix;
};