#pragma once

#include <maths/vector2D.hpp>
#include <maths/matrix.hpp>
#include <maths/matrix_operations.hpp>

class Transform2D
{
    public:
        Transform2D();
        Transform2D( float pos_x, float pos_y = 0.0f, float scale_x = 1.0f, float scale_y = 1.0f, float rotation = 0.0f );
        Transform2D( Vec2f position, Vec2f scale, float rotation );
        Transform2D( const Transform2D& other );

        inline void SetPosition( float pos_x, float pos_y )
        {
            SetPosition({pos_x,pos_y});
        }

        inline void SetPosition( const Vec2f& pos )
        {
            m_position = pos;
            m_model_matrix = Translate(m_position.x,m_position.y,0.0f,m_model_matrix);
        }

        inline void SetScale( float scale_x, float scale_y )
        {
            SetScale({scale_x,scale_y});
        }

        inline void SetScale( const Vec2f& scale )
        {
            m_scale = scale;
             m_model_matrix = Scale(m_scale.x,m_scale.y,1.0f,m_model_matrix);
        }

        inline void SetRotation( float rotation )
        {
            m_rotation = rotation;
            m_model_matrix = Rotate(0.0f,0.0f,m_rotation,m_model_matrix);
        }

        Vec2f GetPosition() const { return m_position; }
        Vec2f GetScale() const { return m_scale; }
        float GetRotation() const { return m_rotation; }

        // should return a copy of the matrix member variable, because we cannot let the user modify the
        // model matrix by hand without modifying the position/scale/rotation. since they are related to each other.
        Mat4f GetModelMatrix() const;

        Transform2D& operator=( const Transform2D& other );
        bool operator==( const Transform2D& other ) const;


    private:
        void CalculateModelMatrix();

    private:
        Vec2f m_position;
        Vec2f m_scale;
        float m_rotation;

        Mat4f m_model_matrix;
};

class Transform3D
{
    public:
        Transform3D();
        Transform3D( float pos_x, float pos_y = 0.0f, float pos_z = 0.0f, float scale_x = 1.0f, float scale_y = 1.0f,
                     float scale_z = 1.0f, float rot_x = 0.0f, float rot_y = 0.0f, float rot_z = 0.0f );
        Transform3D( const Vec3f& position, const Vec3f& scale, const Vec3f& rotation );
        Transform3D( const Transform3D& other );

        inline void SetPosition( float pos_x, float pos_y, float pos_z )
        {
            SetPosition(pos_x,pos_y,pos_z);
        }

        inline void SetPosition( const Vec3f& pos )
        {
            m_position = pos;
            m_model_matrix = Translate(m_position.x,m_position.y,m_position.z,m_model_matrix);
        }

        inline void SetScale( float scale_x, float scale_y, float scale_z )
        {
            SetScale({scale_x,scale_y,scale_z});
        }

        inline void SetScale( const Vec3f& scale )
        {
            m_scale = scale;
            m_model_matrix = Scale(m_scale.x,m_scale.y,m_scale.z,m_model_matrix);
        }

        inline void SetRotation( float rot_x, float rot_y, float rot_z )
        {
            SetRotation({rot_x,rot_y,rot_z});
        }

        inline void SetRotation( const Vec3f& rotation )
        {
            m_rotation = rotation;
            m_model_matrix = Rotate(m_rotation.x,m_rotation.y,m_rotation.z,m_model_matrix);
        }

        Vec3f GetPosition() const { return m_position; }
        Vec3f GetScale() const { return m_scale; }
        Vec3f GetRotation() const { return m_rotation; }

        // should return a copy of the matrix member variable, because we cannot let the user modify the
        // model matrix by hand without modifying the position/scale/rotation. since they are related to each other.
        Mat4f GetModelMatrix() const;

        Transform3D& operator=( const Transform3D& other );
        bool operator==( const Transform3D& other ) const;


    private:
        void CalculateModelMatrix();

    private:
        Vec3f m_position;
        Vec3f m_scale;
        Vec3f m_rotation;

        Mat4f m_model_matrix;
};