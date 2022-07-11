#pragma once

#include "buffers.hpp"

enum struct AttributeType : uint32_t
{
    NONE =                  0x0,

    POSITION =              0x01,
    TEXTURE_UV =            0x02,
    COLOR =                 0x04,
    NORMAL =                0x08,

    /* user defined.
    OTHER_1 =               0x10,
    OTHER_2 =               0x20,
    OTHER_3 =               0x40,
    OTHER_4 =               0x80,*/

    ALL =                   POSITION | TEXTURE_UV | COLOR | NORMAL
};

inline constexpr AttributeType operator|( AttributeType first, AttributeType second )
{
    return static_cast<AttributeType>( AsInteger(first) | AsInteger(second) );
}

inline constexpr AttributeType operator|=( AttributeType first, AttributeType second )
{
    first = first | second;
    return first;
}

inline constexpr AttributeType operator&( AttributeType first, AttributeType second )
{
    return static_cast<AttributeType>( AsInteger(first) & AsInteger(second) );
}

class VertexBuffer : public GLBuffer<GLfloat,GL_ARRAY_BUFFER>
{
    friend class Renderer;
    friend class VertexArray;

    public:
        struct BufferElement
        {
            BufferElement() = default;
            BufferElement( const std::string& title, GLDataType type, AttributeType attrib_type );
            BufferElement( const std::string& title, AttributeType attrib_type );

            std::string m_title;
            AttributeType m_attrib_type;
            GLDataType m_type;
        };

        struct BufferLayout
        {
            BufferLayout();
            BufferLayout( const BufferLayout& other );
            BufferLayout( const std::initializer_list<BufferElement>& _list );

            BufferLayout& operator=( const BufferLayout& other );

            void AddElement( const BufferElement& element );

            std::vector<BufferElement> m_elements;
            std::vector<GLuint> m_offsets;
            std::uint16_t m_stride;
        };
    
    public:
        VertexBuffer() = default;
        VertexBuffer( const std::vector<float>& data, const BufferLayout& layout, VertexDataUsage usage
                    = VertexDataUsage::STATIC );

        VertexBuffer( const VertexBuffer& other );
        VertexBuffer( VertexBuffer&& other );

        void SetLayout( const BufferLayout& layout );

        void Fill( const std::vector<float>& data, const BufferLayout& layout );

        BufferLayout& GetLayout() { return m_layout; }

    private:
        BufferLayout m_layout;
};