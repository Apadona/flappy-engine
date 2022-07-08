#include "mesh.hpp"

Mesh Mesh::triangle
(
    {
        0.0f,0.86f,1.0f,
        -0.5f,0.00f,1.0f,
        0.5f,0.00f,1.0f
    }, 

    {
        0.5f,1.0f,
        0.0f,0.0f,
        1.0f,0.0f
    },

    {
        1.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f
    },

    {
        0,1,2
    }
);

Mesh Mesh::rectangle
(
    {
        0.5f,   0.5f,   1.0f,
        -0.5f,   0.5f,    1.0f,
        -0.5f,   -0.5f,   1.0f,
        0.5f,   -0.5f,   1.0f
    },

    {
        1.0f,1.0f,
        0.0f,1.0f,
        0.0f,0.0f,
        1.0f,0.0f
    },

    {
        1.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f,
        1.0f,1.0f,0.0f
    },

    {
        0,1,2,
        2,3,0
    }
);

Mesh::Mesh( const Mesh& other )
{
    *this = other;
}

Mesh::Mesh( const std::vector<float>& vertex_pos, const std::vector<float>& texture_uv,
          const std::vector<float>& color, const std::vector<uint32_t>& indecies ) :
          m_vertex_pos(vertex_pos), m_texture_uv(texture_uv),
          m_color(color), m_indecies(indecies) {}

Mesh& Mesh::operator=( const Mesh& other )
{
    if( this == &other )
        return *this;

    m_vertex_pos = other.m_vertex_pos;
    m_texture_uv = other.m_texture_uv;
    m_color = other.m_color;
    m_indecies = other.m_indecies;

    return *this;
}

std::vector<float> Mesh::ConstructAttributesInOneBuffer( AttributeType type ) const
{
    auto vertex_count = m_vertex_pos.size() / 3;
    auto vertex_size = 0;

    if( ( type & AttributeType::POSITION ) == AttributeType::POSITION )
        vertex_size += 3;

    if( ( type & AttributeType::TEXTURE_UV ) == AttributeType::TEXTURE_UV )
        vertex_size += 2;

    if( ( type & AttributeType::COLOR ) == AttributeType::COLOR )
        vertex_size += 3;

    auto total_size = vertex_size * vertex_count;
    std::vector<float> buffer(total_size);

    // i for our own buffer counter, j for texture counter and k for position and color counter.
    for( uint32_t vertex_counter = 0, i = 0, j = 0, k = 0; vertex_counter < vertex_count;
        ++vertex_counter, i += vertex_size, j += 2, k += 3 )
    {
        if( ( type & AttributeType::POSITION ) == AttributeType::POSITION )
        {
            buffer[i] = m_vertex_pos[k],
            buffer[i + 1] = m_vertex_pos[k + 1],
            buffer[i + 2] = m_vertex_pos[k + 2];
        }

        if( ( type & AttributeType::TEXTURE_UV ) == AttributeType::TEXTURE_UV )
        {
            buffer[i + 3] = m_texture_uv[j];
            buffer[i + 4] = m_texture_uv[j + 1];
        }

        if( ( type & AttributeType::COLOR ) == AttributeType::COLOR )
        {
            buffer[i + 5] = m_color[k];
            buffer[i + 6] = m_color[k + 1];
            buffer[i + 7] = m_color[k + 2];
        }
    }

    std::cout << "created buffer:\n";
    for( uint32_t i = 0; i < buffer.size(); ++i )
    {
        std::cout << buffer[i] << ' ';

        if( ( i + 1 ) % vertex_size == 0 )
            std::cout << '\n';
    }

    return buffer;
}

std::ostream& operator<<( std::ostream& out, const Mesh& mesh )
{
    auto PrintAttribute = [&out]( const std::vector<float>& vec, const std::string_view& attribute_name,
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

    PrintAttribute(mesh.m_vertex_pos,"position",3);
    PrintAttribute(mesh.m_texture_uv,"texture_uv",2);
    PrintAttribute(mesh.m_color,"color",3);

    return out;
}
