#pragma once

#include "shader.hpp"
#include "vertex_array.hpp"
#include "mesh.hpp"
#include "texture.hpp"
#include "sprite.hpp"
#include "text.hpp"
#include "particle_system.hpp"
#include "camera.hpp"

#include <maths/vector4D.hpp>

enum BlendingFactor
{
    ZERO,
    ONE,
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

enum RenderFlags : int32_t
{
    NONE                            = 0x00,

    BLENDING_IS_ON                  = 0x01,
    DEPTH_TESTING_IS_ON             = 0x02
};

inline constexpr RenderFlags operator|( RenderFlags first, RenderFlags second )
{
    return static_cast<RenderFlags>( AsInteger(first) | AsInteger(second) );
}

inline constexpr RenderFlags operator&( RenderFlags first, RenderFlags second )
{
    return static_cast<RenderFlags>( AsInteger(first) & AsInteger(second) );
}

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
                           ScreenSize c_y, const Vec4f& color = m_default_color, Texture& texture = m_default_texture01 );

        void DrawRectangle( ScreenSize pos_x, ScreenSize pos_y, ScreenSize width, ScreenSize height,
                            Texture& texture );

        void DrawRectangle( ScreenSize pos_x, ScreenSize pos_y, ScreenSize width, ScreenSize height,
                            const Vec4f& color = m_default_color, Texture& texture = m_default_texture01 );

        // These functions draw by normalized screen cordinates ( center is (0.0,0.0) ).
        void DrawTriangle( float pos_x, float pos_y, float scale_x, float scale_y, float rotate,
                           Texture& texture );

        void DrawTriangle( float pos_x, float pos_y, float scale_x, float scale_y, float rotate,
                           const Vec4f& color = m_default_color, Texture& texture = m_default_texture01 );

        void DrawTriangle( const Transform2D& transform, Texture& texture );

        void DrawTriangle( const Transform2D& transform, const Vec4f& color = m_default_color,
                           Texture& texture = m_default_texture01 );

        void DrawRectangle( float pos_x, float pos_y, float scale_x, float scale_y, float rotate,
                            Texture& texture );

        void DrawRectangle( float pos_x, float pos_y, float scale_x, float scale_y, float rotate,
                            const Vec4f& color = m_default_color, Texture& texture = m_default_texture01 );

        void DrawRectangle( const Transform2D& transform, Texture& texture );

        void DrawRectangle( const Transform2D& transform, const Vec4f& color = m_default_color,
                            Texture& texture = m_default_texture01 );

        void DrawSprite( const Sprite& sprite );

        void DrawText( Text& text );

        void DrawParticles( ParticleSystem& particle_system );

        void ClearColor( float red = 1.0f, float green = 1.0f, float blue = 1.0f, float alpha = 1.0f ) const;

        void SetCamera( Camera* camera );

        const Camera* GetCamera() const;

    private:
        void Prepare( VertexArray& va, const Transform2D& transform, Texture& texture, const Vec4f& color );
        void PrepareForTextRendering( Text& text, Font& font );

        void DrawCommand() const;
        void DrawIndexedCommand( const IndexBuffer& ib ) const;
        void DrawInstancedCommand( uint32_t count, uint32_t attrib_divisor ) const;

        void ClearColorCommand( float red, float green, float blue, float alpha ) const;

        void BlendCommand( bool enable, BlendingFactor source, BlendingFactor destination );

    private:
        RenderFlags m_render_flags = RenderFlags::NONE;

        // these sizes are used for some rendering measures.
        ScreenSize m_render_width;
        ScreenSize m_render_height;

        // all the data needed to render a triangle for a modern rendering API.
        VertexBuffer m_triangle_vbo;
        IndexBuffer m_triangle_ebo;
        VertexArray m_triangle_vao;

        // all the data needed to render a rectangle for a modern rendering API.
        VertexBuffer m_rectangle_vbo;
        IndexBuffer m_rectangle_ebo;
        VertexArray m_rectangle_vao;

        static Texture m_default_texture01; // default white texture used in color shader.
        static Vec4f m_default_color; // default white color used in color shader.

        Shader m_default_shader;
        Camera* m_scene_camera;
};