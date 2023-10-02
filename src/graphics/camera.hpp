#pragma once

#include "transform.hpp"

#include <maths/vector3D.hpp>
#include <maths/matrix.hpp>

enum class CameraProjection
{
    NONE,
    ORTHOGONICAL,
    PERSPECTIVE
};

class Camera : public Transform3D 
{
    public:
        Camera();
    
        Camera( const Vec3f& position, const Vec3f& look, const Vec3f& up );

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


        const Mat4f& GetProjectionMatrix()
        {
            return m_projection_matrix;
        }

        CameraProjection GetProjectionType() const { return m_projection_type; }

    protected:
        virtual void CalculateAndSetProjectionMatrix();
        
        void CalculateAndSetViewMatrix()
        {
            m_view_matrix = LookAt(GetPosition(),m_look_direction,m_up_vector);
        }

        virtual void CalculateProjectionMatrix();

    protected:
        Mat4f m_view_matrix;
        Mat4f m_projection_matrix;

        // NOTE: position value comes from inheriting Transform3D class. 
        Vec3f m_look_direction;
        Vec3f m_up_vector;

        CameraProjection m_projection_type;
};

class OrthogonicalCamera : public Camera
{
    public:
        OrthogonicalCamera();
        OrthogonicalCamera( float x_min, float x_max, float y_min, float y_max, float z_min, float z_max );

        void SetMinX( float x_min )
        {
            m_x_min = x_min;
            CalculateAndSetProjectionMatrix();
        }

        void SetMaxX( float x_max )
        {
            m_x_max = x_max;
            CalculateAndSetProjectionMatrix();
        }

        void SetMinY( float y_min )
        {
            m_y_min = y_min;
            CalculateAndSetProjectionMatrix();
        }

        void SetMaxY( float y_max )
        {
            m_y_max = y_max;
            CalculateAndSetProjectionMatrix();
        }

        void SetMinZ( float z_min )
        {
            m_z_min = z_min;
            CalculateAndSetProjectionMatrix();
        }

        void SetMaxZ( float z_max )
        {
            m_z_max = z_max;
            CalculateAndSetProjectionMatrix();
        }

        float GetMinX() const
        {
            return m_x_min;
        }

        float GetMaxX() const
        {
            return m_x_max;
        }

        float GetMinY() const
        {
            return m_y_min;
        }

        float GetMaxY() const
        {
            return m_y_max;
        }

        float GetMinZ() const
        {
            return m_z_min;
        }

        float GetMaxZ() const
        {
            return m_z_max;
        }

    private:
        void CalculateAndSetProjectionMatrix() override;

    private:
        float m_x_min;
        float m_x_max;
        float m_y_min;
        float m_y_max;
        float m_z_min;
        float m_z_max;
};

class PerspectiveCamera : public Camera
{
    public:
        PerspectiveCamera();
        PerspectiveCamera( float fov = 45, float m_aspect_ratio = 4.0f / 3.0f, float near = 0.1f, float far = 1000 );

        void SetFieldOfView( float field_of_view )
        {
            m_field_of_view = field_of_view;
            CalculateAndSetProjectionMatrix();
        }
        
        void SetAspectRatio( float aspect_ratio )
        {
            m_aspect_ratio = aspect_ratio;
            CalculateAndSetProjectionMatrix();
        }

        void SetNearPlane( float near )
        {
            m_near = near;
            CalculateAndSetProjectionMatrix();
        }

        void SetFarPlane( float far )
        {
            m_far = far;
            CalculateAndSetProjectionMatrix();
        }

        float GetFieldOfView() const
        {
            return m_field_of_view;
        }

        float GetAspectRatio() const
        {
            return m_aspect_ratio;
        }

        float GetNearPlane() const
        {
            return m_near;
        }

        float GetFarPlane() const
        {
            return m_far;
        }

    private:
        void CalculateAndSetProjectionMatrix() override;

    private:
        float m_field_of_view;
        float m_aspect_ratio;
        float m_near;
        float m_far;
};

// class CameraManipulator
// {
//     public:
//         CameraManipulator( Camera* camera )
//         {
//         }

//     private:
//         // CameraType m_type;
// };