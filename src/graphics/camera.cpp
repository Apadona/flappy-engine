#include "camera.hpp"


Camera::Camera() : Transform3D({0.0f,0.0f,0.0f},{1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f}), m_look_direction({0.0f,0.0f,0.0f}),
                   m_up_vector({0.0,1.0f,0.0}), m_projection_type(CameraProjection::NONE)
{
    CalculateAndSetViewMatrix();
}

Camera::Camera( const Vec3f& position, const Vec3f& look, const Vec3f& up ) : Transform3D(position,{1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f}),
                                                                              m_look_direction(look), m_up_vector(up),
                                                                              m_projection_type(CameraProjection::NONE)
{
    CalculateAndSetViewMatrix();
}

OrthogonicalCamera::OrthogonicalCamera() : m_x_min(0.0f), m_x_max(100.0f), m_y_min(0.0f), m_y_max(100.0f), m_z_min(0.0f), m_z_max(100.0f)
{
    
}

OrthogonicalCamera::OrthogonicalCamera( float x_min, float x_max, float y_min, float y_max, float z_min, float z_max ) : m_x_min(x_min),
                                        m_x_max(x_max), m_y_min(y_min), m_y_max(y_max), m_z_min(z_min), m_z_max(z_max)
{
    CalculateAndSetProjectionMatrix();
}

void OrthogonicalCamera::CalculateAndSetProjectionMatrix()
{
    m_projection_matrix = Ortho(m_x_max,m_x_min,m_y_max,m_y_min,m_z_max,m_z_min);
}

PerspectiveCamera::PerspectiveCamera( float field_of_view, float aspect_ratio, float near, float far ) : m_field_of_view(field_of_view),
                                      m_aspect_ratio(aspect_ratio), m_near(near), m_far(far)

{
    m_projection_type = CameraProjection::PERSPECTIVE;
}

void PerspectiveCamera::CalculateAndSetProjectionMatrix()
{
    m_projection_matrix = Perspective(m_aspect_ratio,m_field_of_view,m_near,m_far);
}