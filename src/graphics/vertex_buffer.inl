#include "vertex_buffer.hpp"

template<typename T,GLenum type>
GLBuffer<T,type>::GLBuffer( const std::vector<T>& data, VertexDataUsage usage )
{
    Fill(m_data);
}

template<typename T,GLenum type>
void GLBuffer<T,type>::Fill( const std::vector<T>& data, VertexDataUsage usage )
{
    m_data = data;

    if( m_data.empty() )
    {
        LOG_WARNING("empty buffer sent to GPU!");
        return;
    }

    glGenBuffers(1,&m_id);
    glBindBuffer(type,m_id);
    glBufferData(type,sizeof(m_data) * m_data.size(),m_data.data(), usage );
}

template<typename T,GLenum type>
void GLBuffer<T,type>::Bind( bool bind )
{
    constexpr if( type == GL_ARRAY_BUFFER )
    {
        if( bind && m_is_bound == false )
        {
            glBindBuffer(GL_ARRAY_BUFFER,m_id);
            m_is_bound = true;
        }

        else if( bind == false && m_is_bound == true )
            glBindBuffer(GL_ARRAY_BUFFER,0);
    }

    constexpr else if( type == GL_ELEMENT_ARRAY_BUFFER )
    {
        if( bind && m_is_bound == false )
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_id);

        else if( bind == false && m_is_bound == true )
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    }
}