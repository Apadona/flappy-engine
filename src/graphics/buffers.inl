//#include "buffers.hpp"
#include <utils/logger.hpp>

template<typename T,GLenum type>
GLBuffer<T,type>::GLBuffer( const std::vector<T>& data, VertexDataUsage usage )
{
    Fill(data,usage);
}

template<typename T,GLenum type>
GLBuffer<T,type>::GLBuffer( std::vector<T>&& data, VertexDataUsage usage )
{
    Fill(data,usage);
}

template<typename T,GLenum type>
GLBuffer<T,type>::GLBuffer( const GLBuffer<T,type>& other )
{
    Fill(other.m_data,other.usage);
}

template<typename T,GLenum type>
GLBuffer<T,type>::GLBuffer( GLBuffer<T,type>&& other ) : m_data(std::move(other.m_data))
{
    Fill(m_data,other.usage);
}

template<typename T,GLenum type>
GLBuffer<T,type>& GLBuffer<T,type>::operator=( const GLBuffer<T,type>& other )
{
    if( *this != &other )
        Fill(other.m_data,other.m_usage);

    return *this;
}

template<typename T,GLenum type>
GLBuffer<T,type>& GLBuffer<T,type>::operator=( GLBuffer<T,type>&& other )
{
    if( *this != &other )
    {
        Fill(other.m_data,other.m_usage);

        other.m_id = 0;
        other.m_is_bound = false;
    }

    return *this;
}

template<typename T,GLenum type>
void GLBuffer<T,type>::Fill( const std::vector<T>& data, VertexDataUsage usage )
{
    m_data = data;
    m_usage = usage;

    if( m_data.empty() )
    {
        CORE_LOG_WARNING("empty buffer sent to GPU!");
        return;
    }

    glGenBuffers(1,&m_id);
    glBindBuffer(type,m_id);
    glBufferData(type,sizeof(m_data[0]) * m_data.size(),m_data.data(), (GLenum)m_usage );
    
    Bind(false);
}

template<typename T,GLenum type>
void GLBuffer<T,type>::Bind( bool bind )
{
    if( type == GL_ARRAY_BUFFER )
    {
        if( bind && m_is_bound == false )
        {
            glBindBuffer(GL_ARRAY_BUFFER,m_id);
            m_is_bound = true;
        }

        else if( bind == false && m_is_bound == true )
            glBindBuffer(GL_ARRAY_BUFFER,0);
    }

    else if( type == GL_ELEMENT_ARRAY_BUFFER )
    {
        if( bind && m_is_bound == false )
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_id);

        else if( bind == false && m_is_bound == true )
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    }
}

template<typename T, GLenum type>
GLBuffer<T,type>::~GLBuffer()
{
    // glDeleteBuffers(1,&m_id);
}
