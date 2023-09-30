#pragma once

#include "transform.hpp"

#include <maths/vector3D.hpp>
#include <maths/matrix.hpp>

class Camera : public Transform3D 
{
    public:
        Camera( const Vec3f& position, const Vec3f& look, const Vec3f& up ) : Transform3D(position,{1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f}),
                                                                              m_look_direction(look), m_up_vector(up) {}

        inline void SetLookDirection( const Vec3f& look_direction )
        {
            m_look_direction = look_direction;
            CalculateAndSetViewMatrix();
        }

        inline void SetUpVector( const Vec3f& up_vector )
        {
            m_up_vector = up_vector;
            CalculateAndSetViewMatrix();
        }

        const Vec3f& GetLookDirection() const
        {
            return m_look_direction;
        }

        const Vec3f& GetUpVector() const
        {
            return m_up_vector;
        }

        const Mat4f& GetViewMatrix() const
        {
            return m_view_matrix;
        }

        // virtual Mat4f CalculateProjectionMatrix() const;

    private:
        void CalculateAndSetViewMatrix()
        {
            m_view_matrix = LookAt(GetPosition(),m_look_direction,m_up_vector);
        }

    protected:
        const Mat4f& GetProjectionMatrix()
        {
            return m_proj_matrix;
        }
        
    private:
        Mat4f m_view_matrix;
        Mat4f m_proj_matrix;

        // NOTE: position value comes from inheriting Transform3D class. 
        Vec3f m_look_direction;
        Vec3f m_up_vector;
};

class OrthogonicalCamera : public Camera
{

};

class PerspectiveCamera : public Camera
{
    public:
        PerspectiveCamera( float fov = 45, float m_aspect_ratio = 4.0f / 3.0f, float near = 0.1f, float far = 1000 );

        void SetFieldOfView( float fov );
        
        void SetAspectRatio( float aspect_ratio );

        void SetNearPlane( float near );

        void SetFarPlane( float far );

        float GetFieldOfView() const;

        float GetAspectRatio() const;

        float GetNearPlane() const;

        float GetFarPlane() const;

    private:
        Mat4f CalculateProjectionMatrix() const;

    private:
        float m_field_of_view;
        float m_aspect_ratio;
        float m_near;
        float m_far;
};

class CameraManipulator
{
    public:
        CameraManipulator( Camera* camera )
        {
        }

    private:
        // CameraType m_type;
};