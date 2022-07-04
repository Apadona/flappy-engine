#pragma once

#include "shader.hpp"
#include "vertex_array.hpp"
#include "sprite.hpp"
#include "texture.hpp"
#include "shapes.hpp"

#include <maths/vector4D.hpp>

// simple 2D renderer.
class Renderer
{
    public:
        Renderer() = default;

        ~Renderer() = default;

        bool Init();

        void DrawTriangle( float pos_x = 0.0f, float pos_y = 0.0f, float scale_x = 1.0f, float scale_y = 1.0f,
                            float rotate = 0.0f, const Vec4& color = {1.0f,1.0f,1.0f,0.0f} );

        void DrawRectangle( float pos_x = 0.0f, float pos_y = 0.0f, float scale_x = 1.0f, float scale_y = 1.0f,
                            float rotate = 0.0f, const Vec4& color = {1.0f,1.0f,1.0f,0.0f} );

        void DrawTriangle( const Transform2D& transform, const Vec4& color = { 1.0f,1.0f,1.0f,0.0f } );
        void DrawRectangle( const Transform2D& transform, const Vec4& color = { 1.0f,1.0f,1.0f,0.0f } );

        void DrawSprite( const Sprite& sprite );

        void ClearColor( float red = 1.0f, float green = 1.0f, float blue = 1.0f, float alpha = 1.0f );

    private:
        void Prepare();

    private:
        Texture m_default_texture; // white texture used in color shader.
        Shader m_shader;
        VertexArray m_triangle_vao;
        VertexArray m_rectangle_vao;

        VertexBuffer m_rectangle_pos_vbo;
        VertexBuffer m_rectangle_uv_vbo;
        IndexBuffer m_triangle_ebo;

        VertexBuffer m_triangle_pos_vbo;
        VertexBuffer m_triangle_uv_vbo;
        IndexBuffer m_rectangle_ebo;
};