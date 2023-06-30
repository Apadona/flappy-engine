#include "mesh.hpp"

Mesh Mesh::triangle
(
    AttributeBuffer
    ({
        0.0f,   1.0f,   1.0f,
        -1.0f,  -1.0f,  1.0f,
        1.0f,   -1.0f,  1.0f
    }), 

    AttributeBuffer
    ({
        0.5f,   1.0f,
        0.0f,   0.0f,
        1.0f,   0.0f
    }),

    AttributeBuffer
    ({
        1.0f,   1.0f,   1.0f,
        1.0f,   1.0f,   1.0f,
        1.0f,   1.0f,   1.0f
    }),

    AttributeBuffer
    ({
        1.0f,   0.0f,   0.0f,
        0.0f,   1.0f,   0.0f,
        0.0f,   0.0f,   1.0f
    }),

    ElementBuffer
    ({
        0,1,2
    })
);

Mesh Mesh::rectangle
(
    AttributeBuffer
    ({
        1.0f,   1.0f,   1.0f,
        -1.0f,  1.0f,   1.0f,
        -1.0f,  -1.0f,  1.0f,
        1.0f,   -1.0f,  1.0f
    }),

    AttributeBuffer
    ({
        1.0f,   1.0f,
        0.0f,   1.0f,
        0.0f,   0.0f,
        1.0f,   0.0f
    }),

    AttributeBuffer
    ({
        1.0f,   0.0f,   0.0f,
        0.0f,   1.0f,   0.0f,
        0.0f,   0.0f,   1.0f,
        1.0f,   1.0f,   0.0f
    }),

    AttributeBuffer
    ({
        1.0f,   1.0f,   1.0f,
        1.0f,   1.0f,   1.0f,
        1.0f,   1.0f,   1.0f,
        1.0f,   1.0f,   1.0f
    }),

    ElementBuffer
    ({
        0,1,2,
        2,3,0
    })
);

Mesh::Mesh( const Mesh& other )
{
    *this = other;
}

Mesh::Mesh( Mesh&& other )
{
    *this = std::forward<Mesh>(other);
}

Mesh::Mesh( const AttributeBuffer& positions, const AttributeBuffer& uvs,
            const AttributeBuffer& colors, const AttributeBuffer& normals,
            const ElementBuffer& indicies )
{
    SetPositionAttribute(positions);
    SetUVAttribute(uvs);
    SetColorAttribute(colors);
    SetNormalAttribute(normals);
    SetIndicies(indicies);
}

Mesh& Mesh::operator=( const Mesh& other )
{
    if( this != &other )
    {
        SetPositionAttribute(other.m_positions);
        SetPositionAttribute(other.m_uvs);
        SetPositionAttribute(other.m_colors);
        SetNormalAttribute(other.m_normals);
        SetIndicies(other.m_indicies);
    }

    return *this;
}

Mesh& Mesh::operator=(Mesh&& other)
{
    if( this != &other )
    {
        m_positions = std::move(other.m_positions);
        m_uvs = std::move(other.m_uvs);
        m_colors = std::move(other.m_colors);
        m_normals = std::move(other.m_normals);
        m_indicies = std::move(other.m_indicies);
    }

    return *this;
}

void Mesh::SetPositionAttribute(const AttributeBuffer& buffer)
{
    m_positions = buffer;
}

void Mesh::SetUVAttribute(const AttributeBuffer& buffer)
{
    m_uvs = buffer;
}

void Mesh::SetColorAttribute(const AttributeBuffer& buffer)
{
    m_colors = buffer;
}

void Mesh::SetNormalAttribute(const AttributeBuffer& buffer)
{
    m_normals = buffer;
}

void Mesh::SetIndicies(const ElementBuffer& indicies)
{
    m_indicies = indicies;
}

const AttributeBuffer& Mesh::GetPositionAttribute() const
{
    return m_positions;
}

const AttributeBuffer& Mesh::GetUVAttribute() const
{
    return m_uvs;
}

const AttributeBuffer& Mesh::GetColorAttribute() const
{
    return m_colors;
}

const AttributeBuffer& Mesh::GetNormalAttribute() const
{
    return m_normals;
}

const ElementBuffer& Mesh::GetIndicies() const
{
    return m_indicies;
}

AttributeBuffer Mesh::ConstructAttributesInOneBuffer( const VertexBuffer::BufferLayout& layout )
{
    AttributeType required_flags = AttributeType::NONE;

    for( auto& i : layout.m_elements )
        required_flags |= i.m_attrib_type;

    return ConstructAttributesInOneBuffer(required_flags);
}

AttributeBuffer Mesh::ConstructAttributesInOneBuffer( AttributeType type ) const
{
    auto vertex_count = m_positions.size() / 3;
    auto vertex_size = 0;

    if( ( type & AttributeType::POSITION ) == AttributeType::POSITION )
        vertex_size += 3;

    if( ( type & AttributeType::TEXTURE_UV ) == AttributeType::TEXTURE_UV )
        vertex_size += 2;

    if( ( type & AttributeType::COLOR ) == AttributeType::COLOR )
        vertex_size += 3;

    CORE_LOG_ASSERT(vertex_size != 0,"cannot make an attribute buffer with size of 0!\n");

    auto total_size = vertex_size * vertex_count;
    AttributeBuffer buffer(total_size);

    // i for our own buffer counter, j for texture counter and k for position and color counter.
    for( uint32_t vertex_counter = 0, i = 0, j = 0, k = 0; vertex_counter < vertex_count;
        ++vertex_counter, i += vertex_size, j += 2, k += 3 )
    {
        if( ( type & AttributeType::POSITION ) == AttributeType::POSITION )
        {
            buffer[i] = m_positions[k],
            buffer[i + 1] = m_positions[k + 1],
            buffer[i + 2] = m_positions[k + 2];
        }

        if( ( type & AttributeType::TEXTURE_UV ) == AttributeType::TEXTURE_UV )
        {
            buffer[i + 3] = m_uvs[j];
            buffer[i + 4] = m_uvs[j + 1];
        }

        if( ( type & AttributeType::COLOR ) == AttributeType::COLOR )
        {
            buffer[i + 5] = m_colors[k];
            buffer[i + 6] = m_colors[k + 1];
            buffer[i + 7] = m_colors[k + 2];
        }
    }

    return buffer;
}

std::ostream& operator<<( std::ostream& out, const Mesh& mesh )
{
    auto PrintAttribute = [&out]( const auto& vec, const std::string_view& attribute_name,
                                  uint8_t component_count )
    {
        out << "attribute " << attribute_name << ((vec.empty())? " is empty." : ":\n");

        for( uint32_t i = 0; i < vec.size(); ++i )
        {
            out << vec[i] << ' ';

            if( ( i + 1 ) % component_count == 0 )
                out << '\n';
        }
    };

    PrintAttribute(mesh.m_positions,"positions",3);
    PrintAttribute(mesh.m_uvs,"uvs",2);
    PrintAttribute(mesh.m_colors,"colors",3);
    PrintAttribute(mesh.m_normals,"normals",3);
    PrintAttribute(mesh.m_indicies,"indicies",1);

    return out;
}
