#include "vertex_buffer.hpp"

inline constexpr GLDataType GetGLDataTypeFromAttribute( AttributeType type )
{
    switch( type )
    {
        case AttributeType::NONE:
            return GLDataType::NONE;

        case AttributeType::POSITION:
            return GLDataType::VEC3;

        case AttributeType::TEXTURE_UV:
            return GLDataType::VEC2;

        case AttributeType::COLOR:
            return GLDataType::VEC3;

        case AttributeType::NORMAL:
            return GLDataType::VEC3;

        case AttributeType::ALL:
            return GLDataType::NONE;

        default: // to avoid compiler flags.
            return GLDataType::NONE;
    }
}

VertexBuffer::BufferElement::BufferElement( const std::string& title, GLDataType type,
                                            AttributeType attrib_type ) :
                                            m_title(title), m_attrib_type(attrib_type),
                                            m_type(type) {}
VertexBuffer::BufferElement::BufferElement( const std::string& title, AttributeType attrib_type ) :
                                            m_title(title),
                                            m_attrib_type(attrib_type),                                         
                                            m_type(GetGLDataTypeFromAttribute(m_attrib_type)) {}

VertexBuffer::BufferLayout::BufferLayout( const std::initializer_list<BufferElement>& _list ) :
                                            m_elements(_list) {}

VertexBuffer::VertexBuffer( const std::vector<float>& data, const BufferLayout& layout,
                            VertexDataUsage usage ) :
                            GLBuffer<float,GL_ARRAY_BUFFER>(data,usage), m_layout(layout) {}

VertexBuffer::VertexBuffer( const VertexBuffer& other ) :
                            GLBuffer<float,GL_ARRAY_BUFFER>(other.m_data,other.m_usage)
{
    Fill(other.m_data,other.m_layout);
}

void VertexBuffer::SetLayout( const BufferLayout& layout )
{
    m_layout = layout;
}

void VertexBuffer::Fill( const std::vector<float>& data, const BufferLayout& layout )
{
    GLBuffer<float,GL_ARRAY_BUFFER>::Fill(data);

    SetLayout(layout);
}