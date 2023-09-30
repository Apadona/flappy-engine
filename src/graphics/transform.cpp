#include "transform.hpp"

///////////////////////// TRANSFORM 2D /////////////////////////

Transform2D::Transform2D() : m_position(0.0,0.0), m_scale(1.0,1.0), m_rotation(0.0)
{
    CalculateModelMatrix();
}

Transform2D::Transform2D( float pos_x, float pos_y, float scale_x, float scale_y, float rotation ) :
                             m_position(pos_x,pos_y), m_scale(scale_x,scale_y), m_rotation(rotation)
{
    CalculateModelMatrix();
}

Transform2D::Transform2D( Vec2f position, Vec2f scale, float rotation ) : m_position(position), m_scale(scale),
                                                                        m_rotation(rotation)
{
    CalculateModelMatrix();
}

Transform2D::Transform2D( const Transform2D& other )
{
    *this = other;
}

Transform2D& Transform2D::operator=( const Transform2D& other )
{
    if( this != &other )
    {
        m_position = other.m_position;
        m_scale = other.m_scale;
        m_rotation = other.m_rotation;
        m_model_matrix = other.m_model_matrix;
    }

    return *this;
}

bool Transform2D::operator==( const Transform2D& other ) const
{
    return m_position == other.m_position && m_scale == other.m_scale && m_rotation == other.m_rotation;
}

void Transform2D::CalculateModelMatrix()
{
    m_model_matrix = Translate(m_position.x,m_position.y,0.0f,m_model_matrix) *
                     Scale(m_scale.x,m_scale.y,1.0f,m_model_matrix) *
                     Rotate(0.0f,0.0f,m_rotation,m_model_matrix);
}

Mat4f Transform2D::GetModelMatrix() const
{
    return m_model_matrix;
}

///////////////////////// TRANSFORM 3D /////////////////////////

Transform3D::Transform3D() : m_position(0.0,0.0,0.0), m_scale(1.0,1.0,1.0f), m_rotation(0.0,0.0,0.0)
{
    CalculateModelMatrix();
}

Transform3D::Transform3D( float pos_x, float pos_y, float pos_z, float scale_x, float scale_y, float scale_z,
                          float rot_x, float rot_y, float rot_z ) : m_position(pos_x,pos_y,pos_z),
                          m_scale(scale_x,scale_y,scale_z), m_rotation(rot_x,rot_y,rot_z)
{
    CalculateModelMatrix();
}

Transform3D::Transform3D( const Vec3f& position, const Vec3f& scale, const Vec3f& rotation ) :
                          m_position(position), m_scale(scale), m_rotation(rotation)
{
    CalculateModelMatrix();
}

Transform3D::Transform3D( const Transform3D& other )
{
    *this = other;
}

Transform3D& Transform3D::operator=( const Transform3D& other )
{
    if( this != &other )
    {
        m_position = other.m_position;
        m_scale = other.m_scale;
        m_rotation = other.m_rotation;
        m_model_matrix = other.m_model_matrix;
    }

    return *this;
}

bool Transform3D::operator==( const Transform3D& other ) const
{
    return m_position == other.m_position && m_scale == other.m_scale && m_rotation == other.m_rotation;
}

void Transform3D::CalculateModelMatrix()
{
    m_model_matrix = Translate(m_position.x,m_position.y,m_position.z,m_model_matrix) *
    Scale(m_scale.x,m_scale.y,m_scale.z,m_model_matrix) *
    Rotate(m_rotation.x,m_rotation.y,m_rotation.z,m_model_matrix);
}

Mat4f Transform3D::GetModelMatrix() const
{
    return m_model_matrix;
}