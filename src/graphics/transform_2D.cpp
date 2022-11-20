#include "transform_2D.hpp"

Transform2D::Transform2D() : m_position(0.0f,0.0f), m_scale(1.0f,1.0f), m_rotation(0.0f)
{
    CalculateModelMatrix();
}

Transform2D::Transform2D( float pos_x, float pos_y, float scale_x, float scale_y, float rotation ) :
                             m_position(pos_x,pos_y), m_scale(scale_x,scale_y), m_rotation(rotation)
{
    CalculateModelMatrix();
}

Transform2D::Transform2D( Vec2 position, Vec2 scale, float rotation ) : m_position(position), m_scale(scale),
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
    m_model_matrix = Translate(m_position.x,m_position.y,0.0f,m_model_matrix);
    m_model_matrix = Scale(m_scale.x,m_scale.y,1.0f,m_model_matrix);
    m_model_matrix = Rotate(0.0f,0.0f,m_rotation,m_model_matrix);
}

Mat4f Transform2D::GetModelMatrix() const
{
    return m_model_matrix;
}