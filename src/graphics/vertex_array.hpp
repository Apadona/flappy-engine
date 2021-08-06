#pragma once

#include "vertex_buffer.hpp"
#include "gl_data_types.hpp"

/*
struct Attribute
{
    GLDataType type;
    GLsizei size;
    std::string name;
};

class Layout;
*/

class VertexArray
{
    public:
        static constexpr std::uint8_t max_layouts = 16; // according to OpenGL standard.

    public:
        VertexArray();

        void Bind( bool bind = true );
        VertexArray& AddVertexBuffer( VertexBuffer& buffer, GLDataType type );
        VertexArray& RemoveVertexBuffer( VertexBuffer& buffer );

        VertexArray& SetIndexBuffer( IndexBuffer& buffer );
        VertexArray& RemoveIndexBuffer();

    private:
        GLuint m_id;
        std::uint8_t m_count;
        bool m_is_bind;
};