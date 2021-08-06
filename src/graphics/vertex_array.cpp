#include "vertex_array.hpp"

#include <utils/logger.hpp>

VertexArray::VertexArray() : m_count(0), m_is_bind(false)
{
    glGenVertexArrays(1,&m_id);
}

void VertexArray::Bind( bool bind )
{
    if( bind && !m_is_bind )
        glBindVertexArray(m_id);

    else if( !bind && m_is_bind )
        glBindVertexArray(0);
}

VertexArray& VertexArray::AddVertexBuffer( VertexBuffer& buffer, GLDataType type )
{
    if( !buffer.IsFilled() )
    {
        LOG_WARNING("empty vertex buffer used for rendering!");
        return *this;
    }
    
    Bind();

    buffer.Bind();

    GLint component_count = CalculateComponent(type);
    GLenum gl_type = CalculateType(type);
    glVertexAttribPointer(m_count,component_count,gl_type,GL_FALSE,0,(void*)0);
    glEnableVertexAttribArray(m_count++);

    buffer.Bind(false);
    
    return *this;
}

VertexArray& VertexArray::RemoveVertexBuffer( VertexBuffer& buffer )
{

}