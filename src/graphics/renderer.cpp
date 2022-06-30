#include "renderer.hpp"
#include "shapes.hpp"
#include "texture_manager.hpp"
#include <maths/matrix_operations.hpp>

#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image/stb_image.h>

bool Renderer::Init()
{
    TextureManager::Init();
    //TextureManager::Get().PrintStatus();

    m_triangle_vao.AddLayout(triangle.vertex_pos,GLDataType::VEC3);
    m_triangle_vao.AddLayout(triangle.texture_uv,GLDataType::VEC2);
    m_triangle_vao.SetIndexBuffer(triangle.indecies);

    m_rectangle_vao.AddLayout(rectangle.vertex_pos,GLDataType::VEC3);
    m_rectangle_vao.AddLayout(rectangle.texture_uv,GLDataType::VEC2);
    m_rectangle_vao.SetIndexBuffer(rectangle.indecies);

    stbi_set_flip_vertically_on_load(true);

    if( !m_default_texture.Create("data/textures/white.bmp") )
        LOG_ERROR("could not create default white texture!\n");

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

void Renderer::DrawTriangle( float pos_x, float pos_y, float scale_x, float scale_y, float rotate, const Vec4& color )
{    
    Transform2D transform( {pos_x,pos_y}, {scale_x, scale_y}, rotate );
    DrawTriangle(transform,color);
}

void Renderer::DrawRectangle( float pos_x, float pos_y, float scale_x, float scale_y, float rotate, const Vec4& color )
{
    Transform2D transform( {pos_x,pos_y}, {scale_x, scale_y}, rotate );
    DrawRectangle(transform,color);
}

void Renderer::DrawTriangle( const Transform2D& transform, const Vec4& color )
{
    Prepare();

    m_triangle_vao.Bind();
    //glActiveTexture(0);

    m_shader.SetUniform("transform_matrix",transform.GetModelMatrix());
    m_shader.SetUniform("texture_image",0);
    m_shader.SetUniform("blend_color",color);

    glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,nullptr);
}

void Renderer::DrawRectangle( const Transform2D& transform, const Vec4& color )
{
    Prepare();

    m_rectangle_vao.Bind();
    m_default_texture.Bind();
    glActiveTexture(GL_TEXTURE0);
    
    m_shader.SetUniform("transform_matrix",transform.GetModelMatrix());
    m_shader.SetUniform("texture_image",0); 
    m_shader.SetUniform("blend_color",color);
    
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr);
}

void Renderer::DrawSprite( const Sprite& sprite )
{
    //TextureManager::Get().UseTexture(sprite.texture->m_id);
    
    //sprite.GetTexture().Bind();

    Prepare();

    m_rectangle_vao.Bind();
    
    m_shader.SetUniform("input_color",sprite.GetColor());
    m_shader.SetUniform("transform_matrix",sprite.GetTransform().GetModelMatrix());
    m_shader.SetUniform("texture_image",0);
    
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr);
}

void Renderer::ClearColor( float red, float green, float blue, float alpha )
{
    glClearColor(red,green,blue,alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Prepare()
{
    m_shader.Use();
}