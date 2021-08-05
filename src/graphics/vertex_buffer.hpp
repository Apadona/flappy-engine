#pragma once

#include <glad/glad.h>

#include <vector>

enum class VertexDataUsage
{
    STATIC =            GL_STATIC_DRAW,
    DYNAMIC =           GL_DYNAMIC_DRAW,
    STREAM =             GL_STREAM_DRAW 
};

// represends an OpenGL Buffer (index or vertex).
template<typename T, GLenum type>
class GLBuffer
{
    friend class VertexArray;

    public:
        GLBuffer() = default;
        GLBuffer( const std::vector<T>& data, VertexDataUsage usage = VertexDataUsage::STATIC );

        void Fill( const std::vector<T>& data, VertexDataUsage usage = VertexDataUsage::STATIC );

        void Bind( bool bind = true );
        bool IsFilled() const { return m_data.size() != 0; };

        constexpr GLenum Type() const { return type; }
    
    private:
        GLuint m_id;
        std::vector<T> m_data;
        bool m_is_bound = false;
};

using VertexBuffer = GLBuffer<GLfloat,GL_ARRAY_BUFFER>;
using IndexBuffer = GLBuffer<GLuint,GL_ELEMENT_ARRAY_BUFFER>;

#include "vertex_buffer.inl"