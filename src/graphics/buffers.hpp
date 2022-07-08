#pragma once

#include <glad/glad.h>

#include <engine_pch.hpp>

#include "gl_data_types.hpp"

enum class VertexDataUsage
{
    STATIC =            GL_STATIC_DRAW,
    DYNAMIC =           GL_DYNAMIC_DRAW,
    STREAM =             GL_STREAM_DRAW 
};

// represends an OpenGL Buffer.
template<typename T, GLenum type>
class GLBuffer
{
    friend class VertexArray;
    friend class Renderer;

    public:
        GLBuffer() = default;
        GLBuffer( const std::vector<T>& data, VertexDataUsage usage = VertexDataUsage::STATIC );
        GLBuffer( std::vector<T>&& data, VertexDataUsage usage = VertexDataUsage::STATIC );
        GLBuffer( const GLBuffer<T,type>& buffer );
        GLBuffer( GLBuffer<T,type>&& buffer );

        ~GLBuffer();

        GLBuffer<T,type>& operator=( const GLBuffer<T,type>& other );
        GLBuffer<T,type>& operator=( GLBuffer<T,type>&& other );

        void Fill( const std::vector<T>& data, VertexDataUsage usage = VertexDataUsage::STATIC );

        void Bind( bool bind = true );
        bool IsFilled() const { return m_data.size() != 0; };

        constexpr GLenum Type() const { return type; }
    
    protected:
        GLuint m_id;
        std::vector<T> m_data;
        VertexDataUsage m_usage;
        bool m_is_bound = false;
};

using IndexBuffer = GLBuffer<GLuint,GL_ELEMENT_ARRAY_BUFFER>;

#include "buffers.inl"