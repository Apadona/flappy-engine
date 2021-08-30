#pragma once

#include "shader.hpp"
#include "vertex_array.hpp"
#include <maths/vector4D.hpp>

// simple 2D renderer.
class Renderer
{
    public:
        Renderer() = default;

        ~Renderer() = default;

        bool Init();

        void DrawTriangle( float pos_x, float pos_y, float scale_x = 1.0f, float scale_y = 1.0f,
                                    float rotate = 0.0f, Vec4 color = {1.0f,1.0f,1.0f,0.0f} );

        void DrawRectangle( float pos_x, float pos_y, float scale_x = 1.0f, float scale_y = 1.0f,
                                    float rotate = 0.0f, Vec4 color = {1.0f,1.0f,1.0f,0.0f} );

        void ClearColor( float red, float green, float blue, float alpha = 1.0f );

    private:
        void Prepare();

    private:
        Shader m_shader;
        VertexArray m_triangle_vao;
        VertexArray m_rectangle_vao;
};