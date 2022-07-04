#pragma once

#include "vertex_buffer.hpp"
#include "gl_data_types.hpp"

class VertexArray
{
    public:
        static constexpr GLint max_layouts = 16; // according to OpenGL standard.

    public:
        VertexArray();

        void Bind( bool bind = true );

        VertexArray& AddLayout( VertexBuffer& buffer, GLDataType type );
        VertexArray& AddLayout( VertexBuffer&& buffer, GLDataType type );
        //VertexArray& RemoveVertexBuffer( VertexBuffer& buffer );

        VertexArray& SetIndexBuffer( IndexBuffer& buffer );
        VertexArray& SetIndexBuffer( IndexBuffer&& buffer );
        //VertexArray& RemoveIndexBuffer();

    private:
        GLuint m_id;
        GLint m_count; //number of layouts.
        GLint m_offset; //for figuring out the offset of the current buffer.
        bool m_is_bind;
};