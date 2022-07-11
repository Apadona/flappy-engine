#include "renderer.hpp"
#include "texture_manager.hpp"
#include <maths/matrix_operations.hpp>

#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image/stb_image.h>

bool Renderer::Init()
{
    m_triangle_vao.Init();
    m_rectangle_vao.Init();

    auto triangle_data = Mesh::triangle.ConstructAttributesInOneBuffer(AttributeType::POSITION | AttributeType::TEXTURE_UV);
    
    m_triangle_vbo.Fill(triangle_data,
    {
        {"input_pos",AttributeType::POSITION},
        {"input_uv",AttributeType::TEXTURE_UV}
    });
    m_triangle_ebo.Fill(Mesh::triangle.m_indecies);
    m_triangle_vao.AddLayout(m_triangle_vbo);
    m_triangle_vao.SetIndexBuffer(m_triangle_ebo);

    auto rectangle_data = Mesh::rectangle.ConstructAttributesInOneBuffer(AttributeType::POSITION | AttributeType::TEXTURE_UV);

    m_rectangle_vbo.Fill(rectangle_data,
    {
        {"input_pos",AttributeType::POSITION},
        {"input_uv",AttributeType::TEXTURE_UV}
    });
    m_rectangle_ebo.Fill(Mesh::rectangle.m_indecies);
    m_rectangle_vao.AddLayout(m_rectangle_vbo);
    m_rectangle_vao.SetIndexBuffer(m_rectangle_ebo);

    if( !m_default_texture01.Create("data/textures/awesomeface.png") )
        CORE_LOG_ERROR("could not create default texture01!\n");

    if( m_shader.Create("data/shaders/vertex.vert","data/shaders/fragment.frag") )
    {
        m_shader.PrintAttributes();
        m_shader.PrintUnifroms();

        return true;
    }

    return false;
}

std::ostream& operator<<( std::ostream& out, const glm::mat4& matrix )
{
    auto matrix_data = glm::value_ptr(matrix);
    for( int i = 0; i < 16; ++i )
    {
        out << matrix_data[i];
        if( ( (i + 1) % 4 ) == 0 )
            out << std::endl;

        else
            out << ' ' << std::flush;
    }

    out << std::endl;

    return out;
}

void Renderer::DrawTriangle( float pos_x, float pos_y, float scale_x, float scale_y,
                             float rotate, const Vec4& color )
{    
    Transform2D transform( {pos_x,pos_y}, {scale_x, scale_y}, rotate );
    DrawTriangle(transform,color);
}

void Renderer::DrawTriangle( const Transform2D& transform, const Vec4& color )
{
    DrawTriangle(transform,m_default_texture01,color);
}

void Renderer::DrawTriangle( const Transform2D& transform, Texture& texture,
                             const Vec4& color )
{
    Prepare(m_triangle_vao,transform,texture,color);

    DrawIndexedCommand(m_triangle_ebo);
}

void Renderer::DrawRectangle( float pos_x, float pos_y, float scale_x, float scale_y,
                              float rotate, const Vec4& color )
{
    Transform2D transform( {pos_x,pos_y}, {scale_x, scale_y}, rotate );
    DrawRectangle(transform,color);
}

void Renderer::DrawRectangle( const Transform2D& transform, const Vec4& color )
{
    DrawRectangle(transform,m_default_texture01,color);
}

void Renderer::DrawRectangle( const Transform2D& transform, Texture& texture,
                             const Vec4& color )
{
    Prepare(m_rectangle_vao,transform,texture,color);

    DrawIndexedCommand(m_rectangle_ebo);
}

void Renderer::DrawSprite( const Sprite& sprite )
{
    auto texture = const_cast<Texture*>(sprite.m_texture);
    DrawRectangle(sprite.m_transform,*texture,sprite.m_color);
}

void Renderer::ClearColor( float red, float green, float blue, float alpha ) const
{
    ClearColorCommand(red,green,blue,alpha);
}

void Renderer::Prepare( VertexArray& va, const Transform2D& transform, Texture& texture,
                        const Vec4& color )
{
    m_shader.Use();

    va.Bind();

    TextureManager::Get().UseTexture(texture);
    texture.Bind();

    m_shader.SetUniform("transform_matrix",transform.GetModelMatrix());
    m_shader.SetUniform("texture_image01",TextureManager::Get().GetTextureUnitLocation(texture).value()); 
    m_shader.SetUniform("blend_color",color);
}

void Renderer::DrawCommand() const
{
    glDrawArrays(GL_TRIANGLES,0,3);
}

void Renderer::DrawIndexedCommand( const IndexBuffer& ib ) const
{
    glDrawElements(GL_TRIANGLES,ib.m_data.size(),GL_UNSIGNED_INT,nullptr);
}

void Renderer::ClearColorCommand( float red, float green, float blue, float alpha ) const
{
    glClearColor(red,green,blue,alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}