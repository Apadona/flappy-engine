#pragma once

#include "gl_data_types.hpp"
#include "buffers.hpp"
#include "vertex_buffer.hpp"

class VertexArray
{
    friend std::ostream& operator<<( std::ostream& out, const VertexArray& array );

    // TODO: must do better than this.
    struct AttributeData
    {
        public:
            AttributeData();

            GLint location;
            VertexBuffer* vertex_buffer;
    };

    public:
        static constexpr GLint max_attributes = 16; // according to OpenGL standard.

    public:
        VertexArray();
        
        void Init();

        void Bind( bool bind = true );

        VertexArray& AddLayout( VertexBuffer& buffer );
        VertexArray& RemoveLayout( GLint location );

        VertexArray& SetIndexBuffer( IndexBuffer& buffer );
        VertexArray& RemoveIndexBuffer();

    private:
        GLuint m_id;
        GLint m_attribute_count; // number of layouts.
        bool m_is_bind;

        std::array<AttributeData,max_attributes> m_attributes;
        IndexBuffer* m_bound_ebo;
};