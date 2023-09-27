#include "renderer.hpp"
#include "texture_manager.hpp"
#include <maths/matrix_operations.hpp>

#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image/stb_image.h>

namespace
{
    Vec2f ConvertScreenCoordinatesToOpenGLCoordinates( ScreenSize pos_x, ScreenSize pos_y,
                                                       ScreenSize screen_width, ScreenSize screen_height )
    {
        // screen coordinates starts from top-left of the screen.
        float normalized_pos_x = static_cast<float>(pos_x) / screen_width;
        float normalized_pos_y = static_cast<float>(pos_y) / screen_height;

        return { normalized_pos_x * 2.0f - 1.0f, -normalized_pos_y * 2 + 1 };
    }

    Vec2f CalculateTriangleCenter( ScreenSize render_width, ScreenSize render_height, ScreenSize a_x,
                                   ScreenSize a_y,ScreenSize b_x, ScreenSize b_y, ScreenSize c_x,
                                   ScreenSize c_y )
    {
        Vec2f a_pos_normalized = ConvertScreenCoordinatesToOpenGLCoordinates(a_x,a_y,render_width,render_height);

        Vec2f b_pos_normalized = ConvertScreenCoordinatesToOpenGLCoordinates(b_x,b_y,render_width,render_height);

        Vec2f c_pos_normalized = ConvertScreenCoordinatesToOpenGLCoordinates(c_x,c_y,render_width,render_height);

        float average_pos_x = ( a_pos_normalized.x + b_pos_normalized.x + c_pos_normalized.x ) / 3;
        float average_pos_y = ( a_pos_normalized.y + b_pos_normalized.y + c_pos_normalized.y ) / 3;

        return {average_pos_x,average_pos_y};
    }

    Vec2f CalculateRectangleCenter( ScreenSize pos_x, ScreenSize pos_y, ScreenSize width, ScreenSize height )
    {
        return { pos_x + static_cast<float>(width) / 2, pos_y + static_cast<float>(height) / 2 };
    }

    Vec2f CalculateRectangleScale( ScreenSize width, ScreenSize height, ScreenSize screen_width,
                                   ScreenSize screen_height )
    {
        return { static_cast<float>(width) / screen_width, static_cast<float>(height) / screen_height };
    }

    Vec4f CalculateRectangleNormalizedPositionAndScale( ScreenSize pos_x, ScreenSize pos_y, ScreenSize width,
                                                        ScreenSize height, ScreenSize render_width,
                                                        ScreenSize render_height )
    {
        Vec2f center = CalculateRectangleCenter(pos_x,pos_y,width,height);
        Vec2f normalized_center = ConvertScreenCoordinatesToOpenGLCoordinates(center.x,center.y,render_width,render_height);
        Vec2f normalized_scale = CalculateRectangleScale(width,height,render_width,render_height);

        return {normalized_center.x,normalized_center.y,normalized_scale.x,normalized_scale.y};
    }
}

Texture Renderer::m_default_texture01;
Vec4 Renderer::m_default_color;

bool Renderer::Init( ScreenSize size_x, ScreenSize size_y )
{
    m_render_width = size_x;
    m_render_height = size_y;

    m_triangle_vao.Init();
    m_rectangle_vao.Init();

    auto triangle_data = Mesh::triangle.ConstructAttributesInOneBuffer(AttributeType::POSITION | AttributeType::TEXTURE_UV);
    
    m_triangle_vbo.Fill(triangle_data,
    {
        {"input_pos",AttributeType::POSITION},
        {"input_uv",AttributeType::TEXTURE_UV}
    });
    m_triangle_ebo.Fill(Mesh::triangle.GetIndicies());
    m_triangle_vao.AddLayout(m_triangle_vbo);
    m_triangle_vao.SetIndexBuffer(m_triangle_ebo);

    auto rectangle_data = Mesh::rectangle.ConstructAttributesInOneBuffer(AttributeType::POSITION | AttributeType::TEXTURE_UV);

    m_rectangle_vbo.Fill(rectangle_data,
    {
        {"input_pos",AttributeType::POSITION},
        {"input_uv",AttributeType::TEXTURE_UV}
    });
    m_rectangle_ebo.Fill(Mesh::rectangle.GetIndicies());
    m_rectangle_vao.AddLayout(m_rectangle_vbo);
    m_rectangle_vao.SetIndexBuffer(m_rectangle_ebo);

    if( !m_default_texture01.Create("data/textures/awesomeface.png") )
        CORE_LOG_ERROR("could not create default texture01!\n");

    m_default_color = {1.0f,1.0f,1.0f,1.0f};

    if( m_default_shader.Create("data/shaders/default.vert","data/shaders/default.frag") )
    {
        m_default_shader.PrintAttributes();
        m_default_shader.PrintUnifroms();

        return true;
    }

    return false;
}

void Renderer::DrawTriangle( ScreenSize a_x, ScreenSize a_y, ScreenSize b_x, ScreenSize b_y,
                             ScreenSize c_x, ScreenSize c_y, Texture& texture )
{
    Vec2f center = CalculateTriangleCenter(m_render_width,m_render_height,a_x,a_y,b_x,b_y,c_x,c_y);

    DrawTriangle(center.x,center.y,1.0f,1.0,0.0f,texture);
}

void Renderer::DrawTriangle( ScreenSize a_x, ScreenSize a_y, ScreenSize b_x, ScreenSize b_y,
                             ScreenSize c_x, ScreenSize c_y, const Vec4f& color, Texture& texture )
{
    Vec2f center = CalculateTriangleCenter(m_render_width,m_render_height,a_x,a_y,b_x,b_y,c_x,c_y);

    DrawTriangle(center.x,center.y,1.0f,1.0,0.0f,color,texture);
}

void Renderer::DrawTriangle( float pos_x, float pos_y, float scale_x, float scale_y,
                             float rotate, Texture& texture )
{
    Transform2D transform( {pos_x,pos_y}, {scale_x, scale_y}, rotate );

    DrawTriangle(transform,texture);
}

void Renderer::DrawTriangle( float pos_x, float pos_y, float scale_x, float scale_y,
                             float rotate, const Vec4& color, Texture& texture )
{    
    Transform2D transform( {pos_x,pos_y}, {scale_x, scale_y}, rotate );

    DrawTriangle(transform,color,texture);
}

void Renderer::DrawTriangle( const Transform2D& transform, Texture& texture )
{
    DrawTriangle(transform,m_default_color,texture);
}

void Renderer::DrawTriangle( const Transform2D& transform, const Vec4& color, Texture& texture )
{
    Prepare(m_triangle_vao,transform,texture,color);

    DrawIndexedCommand(m_triangle_ebo);
}

void Renderer::DrawRectangle( ScreenSize pos_x, ScreenSize pos_y, ScreenSize width, ScreenSize height,
                              Texture& texture )
{
    Vec4f rentangle_properties = CalculateRectangleNormalizedPositionAndScale(pos_x,pos_y,width,height,
                                 m_render_width,m_render_height);

    DrawRectangle(rentangle_properties.x,rentangle_properties.y,rentangle_properties.z,
                  rentangle_properties.w,0.0f,texture);
}

void Renderer::DrawRectangle( ScreenSize pos_x, ScreenSize pos_y, ScreenSize width, ScreenSize height,
                              const Vec4f& color, Texture& texture )
{
    Vec4f rentangle_properties = CalculateRectangleNormalizedPositionAndScale(pos_x,pos_y,width,height,
                                 m_render_width,m_render_height);

    DrawRectangle(rentangle_properties.x,rentangle_properties.y,rentangle_properties.z,
                  rentangle_properties.w,0.0f,color,texture);
}

void Renderer::DrawRectangle( float pos_x, float pos_y, float scale_x, float scale_y,
                              float rotate, Texture& texture )
{
    Transform2D transform( {pos_x,pos_y}, {scale_x, scale_y}, rotate );

    DrawRectangle(transform,texture);
}

void Renderer::DrawRectangle( float pos_x, float pos_y, float scale_x, float scale_y,
                              float rotate, const Vec4f& color, Texture& texture )
{
    Transform2D transform( {pos_x,pos_y}, {scale_x, scale_y}, rotate );

    DrawRectangle(transform,color,texture);
}

void Renderer::DrawRectangle( const Transform2D& transform, Texture& texture )
{
    DrawRectangle(transform,m_default_color,texture);
}

void Renderer::DrawRectangle( const Transform2D& transform, const Vec4& color, Texture& texture )
{
    Prepare(m_rectangle_vao,transform,texture,color);

    DrawIndexedCommand(m_rectangle_ebo);
}

void Renderer::DrawSprite( const Sprite& sprite )
{
    DrawRectangle(sprite.m_transform,sprite.m_color,*(sprite.m_texture));
}

void Renderer::DrawText( Text& text )
{
    if( text )
    {
        auto font = text.GetFont();
        if( font )
        {
            //auto str = text.GetText();
            //for( int i = 0; i < str.size(); ++i )
            //{
            //    if( font->HasCharacter(str[i]) )
            //    {
            //        auto place = font->m_atlas.GetCharacterCoordinatesInTexture(str[i]);
                    //Transform2D transform(text.GetPosition().x,text.GetPosition().y);

                    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                    BlendCommand(true,EQUAL_SOURCE_ALPHA,EQUAL_ONE_MINUS_SOURCE_ALPHA);
                    DrawRectangle(200,150,256,256,text.GetColor(),*(font->m_atlas.GetTexture()));
                //}

                //else
                    //CORE_LOG_ERROR("the character ",str[i]," was not present in the font!");
        }

        else
            CORE_LOG_ERROR("text is not accociated with any font!");
    }

    else
        CORE_LOG_ERROR("text is empty!");

    // else
        //DrawText(text,FontLoader::default_font);
}

void Renderer::DrawParticles( ParticleSystem& particle_system )
{
    BlendCommand(true,BlendingFactor::EQUAL_SOURCE_ALPHA,BlendingFactor::ONE); // additive blending.

    auto particles = particle_system.GetParticles();

    for( int i = 0; i < particles.size(); ++i )
    {
        auto& particle = particles[i];

        if( !particles[i].m_is_dead )
        {
            auto* texture =  particle_system.GetTexture();
            DrawRectangle(particle.m_position.x,particle.m_position.y,particle.m_scale.x,particle.m_scale.y,
                          0.0,particle.m_color,texture ? *texture : m_default_texture01);
        }
    }

    BlendCommand(false,BlendingFactor::EQUAL_SOURCE_ALPHA,BlendingFactor::EQUAL_ONE_MINUS_SOURCE_ALPHA);
}

void Renderer::ClearColor( float red, float green, float blue, float alpha ) const
{
    ClearColorCommand(red,green,blue,alpha);
}

void Renderer::Prepare( VertexArray& va, const Transform2D& transform, Texture& texture, const Vec4& color )
{
    //BlendCommand(true,EQUAL_SOURCE_ALPHA,EQUAL_ONE_MINUS_SOURCE_ALPHA);
    m_default_shader.Use();

    va.Bind();

    TextureManager::Get().UseTexture(texture);

    m_default_shader.SetUniform("transform_matrix",transform.GetModelMatrix());
    m_default_shader.SetUniform("texture_image01",TextureManager::Get().GetTextureUnitLocation(texture).value()); 
    m_default_shader.SetUniform("blend_color",color);
    m_default_shader.SetUniform("sample_offset",texture.m_sample_offset);
    m_default_shader.SetUniform("sample_ratio",texture.m_sample_ratio);
}

void Renderer::PrepareForTextRendering( Text& text, Font& font )
{
    
}

void Renderer::DrawCommand() const
{
    glDrawArrays(GL_TRIANGLES,0,3);
}

void Renderer::DrawIndexedCommand( const IndexBuffer& ib ) const
{
    glDrawElements(GL_TRIANGLES,ib.m_data.size(),GL_UNSIGNED_INT,nullptr);
}

void Renderer::DrawInstancedCommand( uint32_t count, uint32_t attrib_divisor ) const
{

}

void Renderer::ClearColorCommand( float red, float green, float blue, float alpha ) const
{
    GLbitfield clear_mask = GL_COLOR_BUFFER_BIT;
    if( ( m_render_flags & RenderFlags::DEPTH_TESTING_IS_ON ) != 0 )
        clear_mask |= GL_DEPTH_BUFFER_BIT;

    glClearColor(red,green,blue,alpha);
    glClear(clear_mask);
}

void Renderer::BlendCommand( bool enable, BlendingFactor source, BlendingFactor destination )
{
    // only disable blending if it is already enabled.
    if( !enable && ( m_render_flags & RenderFlags::BLENDING_IS_ON ) )
    {
        m_render_flags = m_render_flags & static_cast<RenderFlags>(~RenderFlags::BLENDING_IS_ON);
        glDisable(GL_BLEND);
    }

    // else,
    // only enable blending if it is already disabled.
    else if( enable && !( m_render_flags & RenderFlags::BLENDING_IS_ON ) )
    {
        m_render_flags = m_render_flags | static_cast<RenderFlags>(RenderFlags::BLENDING_IS_ON);
        glEnable(GL_BLEND);
        
        auto helper = []( BlendingFactor factor )
        {
            switch( factor )
            {
                case BlendingFactor::ZERO:
                    return GL_ZERO;

                case BlendingFactor::ONE:
                    return GL_ONE;

                case BlendingFactor::EQUAL_CONSTANT_COLOR:
                    return GL_CONSTANT_COLOR;

                case BlendingFactor::EQUAL_ONE_MINUS_CONSTANT_ALPHA:
                    return GL_ONE_MINUS_CONSTANT_ALPHA;

                case BlendingFactor::EQUAL_SOURCE_COLOR:
                    return GL_SRC_COLOR;

                case BlendingFactor::EQUAL_ONE_MINUS_SOURCE_COLOR:
                    return GL_ONE_MINUS_SRC_COLOR;

                case BlendingFactor::EQUAL_DESTINATION_COLOR:
                    return GL_DST_COLOR;

                case BlendingFactor::EQUAL_SOURCE_ALPHA:
                    return GL_SRC_ALPHA;

                case BlendingFactor::EQUAL_ONE_MINUS_SOURCE_ALPHA:
                    return GL_ONE_MINUS_SRC_ALPHA;

                case BlendingFactor::EQUAL_DESTINATION_ALPHA:
                    return GL_DST_ALPHA;

                case BlendingFactor::EQUAL_ONE_MINUS_DESTINATION_ALPHA:
                    return GL_ONE_MINUS_DST_ALPHA;

                default:
                    return GL_INVALID_ENUM;
            }
        };

        GLuint source_command, destination_command;
        source_command = helper(source);
        destination_command = helper(destination);
        bool correct_command = true;

        if ( source_command == GL_INVALID_ENUM )
        {
            CORE_LOG_ERROR("invalid blending factor value is set for source color!\n");
            correct_command = false;
        }

        if ( destination_command == GL_INVALID_ENUM )
        {
            CORE_LOG_ERROR("invalid blending factor value is set for destination color!\n");
            correct_command = false;
        }

        if( !correct_command )
            return;

        glBlendFunc(source_command,destination_command);
    }
}