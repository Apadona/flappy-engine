#pragma once

#include "shader.hpp"
#include "vertex_array.hpp"
#include "mesh.hpp"
#include "texture.hpp"
#include "sprite.hpp"
#include "text.hpp"

#include <maths/vector4D.hpp>

enum BlendingFactor
{
    IS_ZERO,
    IS_ONE,
    EQUAL_CONSTANT_COLOR,
    EQUAL_ONE_MINUS_CONSTANT_COLOR,
    EQUAL_CONSTANT_ALPHA,
    EQUAL_ONE_MINUS_CONSTANT_ALPHA,
    EQUAL_SOURCE_COLOR,
    EQUAL_ONE_MINUS_SOURCE_COLOR,
    EQUAL_DESTINATION_COLOR,
    EQUAL_SOURCE_ALPHA,
    EQUAL_ONE_MINUS_SOURCE_ALPHA,
    EQUAL_DESTINATION_ALPHA,
    EQUAL_ONE_MINUS_DESTINATION_ALPHA
};

enum RenderFlags
{
    NONE                            = 0x00,

    BLENDING_IS_ON                  = 0x01,
    DEPTH_TESTING_IS_ON             = 0x02
};

using ScreenSize = uint16_t;

// simple 2D renderer.
class Renderer
{
    public:
        Renderer() = default;

        ~Renderer() = default;

        bool Init( ScreenSize size_x, ScreenSize size_y );

        // These functions draw by pixel cordinates.
        void DrawTriangle( ScreenSize a_x, ScreenSize a_y, ScreenSize b_x, ScreenSize b_y,
                           ScreenSize c_x, ScreenSize c_y, Texture& texture );

        void DrawTriangle( ScreenSize a_x, ScreenSize a_y, ScreenSize b_x, ScreenSize b_y, ScreenSize c_x,
                           ScreenSize c_y, const Vec4& color = m_default_color, Texture& texture = m_default_texture01 );

        void DrawRectangle( ScreenSize pos_x, ScreenSize pos_y, ScreenSize width, ScreenSize height,
                            Texture& texture );

        void DrawRectangle( ScreenSize pos_x, ScreenSize pos_y, ScreenSize width, ScreenSize height,
                            const Vec4& color = m_default_color, Texture& texture = m_default_texture01 );

        // These functions draw by normalized screen cordinates ( center is (0.0,0.0) ).
        void DrawTriangle( float pos_x, float pos_y, float scale_x, float scale_y, float rotate,
                           Texture& texture );

        void DrawTriangle( float pos_x, float pos_y, float scale_x, float scale_y, float rotate,
                           const Vec4& color = m_default_color, Texture& texture = m_default_texture01 );

        void DrawTriangle( const Transform2D& transform, Texture& texture );

        void DrawTriangle( const Transform2D& transform, const Vec4& color = m_default_color,
                           Texture& texture = m_default_texture01 );

        void DrawRectangle( float pos_x, float pos_y, float scale_x, float scale_y, float rotate,
                            Texture& texture );

        void DrawRectangle( float pos_x, float pos_y, float scale_x, float scale_y, float rotate,
                            const Vec4& color = m_default_color, Texture& texture = m_default_texture01 );

        void DrawRectangle( const Transform2D& transform, Texture& texture );

        void DrawRectangle( const Transform2D& transform, const Vec4& color = m_default_color,
                            Texture& texture = m_default_texture01 );

        void DrawSprite( const Sprite& sprite );

        void ClearColor( float red = 1.0f, float green = 1.0f, float blue = 1.0f, float alpha = 1.0f ) const;

    private:
        void Prepare( VertexArray& va, const Transform2D& transform, Texture& texture, const Vec4& color );
        void PrepareForTextRendering();

        void DrawCommand() const;
        void DrawIndexedCommand( const IndexBuffer& ib ) const;
        void ClearColorCommand( float red, float green, float blue, float alpha ) const;
        void BlendCommand( bool enable, BlendingFactor source, BlendingFactor destination );

    private:
        RenderFlags m_render_flags = RenderFlags::NONE;

        // these sizes are used for some rendering measures.
        ScreenSize m_render_width;
        ScreenSize m_render_height;

        VertexBuffer m_triangle_vbo;
        IndexBuffer m_triangle_ebo;

        VertexBuffer m_rectangle_vbo;
        IndexBuffer m_rectangle_ebo;

        VertexArray m_rectangle_vao;
        VertexArray m_triangle_vao;

        static Texture m_default_texture01; // white texture used in color shader.
        static Vec4 m_default_color; // default color used in color shader.

        Shader m_shader;
};