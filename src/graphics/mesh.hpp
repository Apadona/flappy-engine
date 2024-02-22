#pragma once

#include <engine_pch.hpp>
#include "vertex_buffer.hpp"

using AttributeBuffer = std::vector<float>;
using ElementBuffer = std::vector<uint32_t>;

class Mesh
{
    friend std::ostream& operator<<( std::ostream& out, const Mesh& mesh );

    public:
        Mesh() = default;
        Mesh( const Mesh& other );
        Mesh( Mesh&& other );
        Mesh( const AttributeBuffer& positions, const AttributeBuffer& uvs = {},
              const AttributeBuffer& colors = {}, const AttributeBuffer& normals = {},
              const ElementBuffer& indecies = {} );

        Mesh& operator=( const Mesh& other );
        Mesh& operator=( Mesh&& other );

        void SetPositionAttribute(const AttributeBuffer& position_attrtibue);
        void SetUVAttribute(const AttributeBuffer& uv_attrtibue);
        void SetColorAttribute(const AttributeBuffer& color_attrtibue);
        void SetNormalAttribute(const AttributeBuffer& normal_attrtibue);
        void SetIndicies(const ElementBuffer& indicies );

        const AttributeBuffer& GetPositionAttribute() const;
        const AttributeBuffer& GetUVAttribute() const;
        const AttributeBuffer& GetColorAttribute() const;
        const AttributeBuffer& GetNormalAttribute() const;
        const ElementBuffer& GetIndicies() const;

        AttributeBuffer ConstructAttributesInOneBuffer( const VertexBuffer::BufferLayout& layout );
        AttributeBuffer ConstructAttributesInOneBuffer( AttributeType type ) const;

    public:
        static Mesh triangle;
        static Mesh rectangle;
        static Mesh Cube;

    private:
        AttributeBuffer m_positions;
        AttributeBuffer m_uvs;
        AttributeBuffer m_colors;
        AttributeBuffer m_normals;
        
        ElementBuffer m_indicies;
};

std::ostream& operator<<( std::ostream& out, const Mesh& mesh );