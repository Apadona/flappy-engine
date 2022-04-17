#include "vertex_array.hpp"

#include <utils/logger.hpp>

VertexArray::VertexArray() : m_count(0), m_offset(0), m_is_bind(false)
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

VertexArray& VertexArray::AddLayout( VertexBuffer& buffer, GLDataType type )
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
    GLint type_size = CalculateSize(type);

    glVertexAttribPointer(m_count,component_count,gl_type,GL_FALSE,type_size,(void*)0);
    glEnableVertexAttribArray(m_count++);

    buffer.Bind(false);
    
    return *this;
}

VertexArray& VertexArray::AddLayout( VertexBuffer&& buffer, GLDataType type )
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
    GLint type_size = CalculateSize(type);

    glVertexAttribPointer(m_count,component_count,gl_type,GL_FALSE,type_size,(void*)0);
    glEnableVertexAttribArray(m_count++);

    buffer.Bind(false);
    
    return *this;
}

VertexArray& VertexArray::SetIndexBuffer( IndexBuffer& buffer )
{
    Bind();
    buffer.Bind();

    return *this;
}

VertexArray& VertexArray::SetIndexBuffer( IndexBuffer&& buffer )
{
    Bind();
    buffer.Bind();

    return *this;
}