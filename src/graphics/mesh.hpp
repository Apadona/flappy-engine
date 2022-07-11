#pragma once

#include <engine_pch.hpp>
#include "vertex_buffer.hpp"

struct Mesh
{
    Mesh() = default;
    Mesh( const Mesh& other );
    Mesh( Mesh&& other ) = delete;
    Mesh( const std::vector<float>& vertex_pos, const std::vector<float>& texture_uv,
          const std::vector<float>& color, const std::vector<uint32_t>& indecies );

    Mesh& operator=( const Mesh& other );
    Mesh& operator=( Mesh&& other ) = delete;

    std::vector<float> ConstructAttributesInOneBuffer( const VertexBuffer::BufferLayout& layout );
    std::vector<float> ConstructAttributesInOneBuffer( AttributeType type ) const;

    std::vector<float> m_vertex_pos;
    std::vector<float> m_texture_uv;
    std::vector<float> m_color;
    std::vector<uint32_t> m_indecies;
    
    static Mesh triangle;
    static Mesh rectangle;
};

std::ostream& operator<<( std::ostream& out, const Mesh& mesh );