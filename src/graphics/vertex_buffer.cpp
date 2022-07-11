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

        default: // to avoid compiler warning.
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

VertexBuffer::BufferLayout::BufferLayout() : m_stride(0) {}

VertexBuffer::BufferLayout::BufferLayout( const BufferLayout& other ) : m_elements(other.m_elements),
                                          m_offsets(other.m_offsets), m_stride(other.m_stride)
{
    *this = other;
}

VertexBuffer::BufferLayout::BufferLayout( const std::initializer_list<BufferElement>& _list ) : m_stride(0)
{
    for( auto& element : _list )
        AddElement(element);
}

VertexBuffer::BufferLayout& VertexBuffer::BufferLayout::operator=(
                            const VertexBuffer::BufferLayout& other )
{
    if( this == &other )
        return *this;

    m_elements = other.m_elements;
    m_stride = other.m_stride;
    m_offsets = other.m_offsets;

    return *this;
}

void VertexBuffer::BufferLayout::AddElement( const VertexBuffer::BufferElement& element )
{
    if( m_elements.empty() ) // first element has offset 0.
        m_offsets.push_back(0);
    else
        m_offsets.push_back(m_stride);

    auto _size = CalculateSize(element.m_type);
    m_stride += _size;

    m_elements.push_back(element);
}

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