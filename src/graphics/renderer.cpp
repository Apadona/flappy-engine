#include "renderer.hpp"
#include "shapes.hpp"
#include <maths/matrix_operations.hpp>

#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

bool Renderer::Init()
{
    m_triangle_vao.AddLayout(triangle.vertex_pos,VEC3);
    m_triangle_vao.SetIndexBuffer(triangle.indecies);

    m_rectangle_vao.AddLayout(rectangle.vertex_pos,VEC3);
    m_rectangle_vao.SetIndexBuffer(rectangle.indecies);
    m_rectangle_vao.Bind();

    if( m_shader.Create("shaders/vertex.vert","shaders/fragment.frag") )
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

void Renderer::DrawTriangle( float pos_x, float pos_y, float scale_x, float scale_y, float rotate, Vec4 color )
{    
    static Mat4f transform;
    transform = Translate(pos_x,pos_y,0.0f,transform);
    transform = Scale(scale_x,scale_y,1.0f,transform);
    transform = Rotate(0.0f,0.0f,rotate,transform);

    Prepare();

    m_triangle_vao.Bind();

    m_shader.SetUniform("input_color",color);
    m_shader.SetUniform("transform_matrix",transform);

    glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,nullptr);
}

void Renderer::DrawRectangle( float pos_x, float pos_y, float scale_x, float scale_y, float rotate, Vec4 color )
{
    Mat4f transform;
    transform = Translate(pos_x,pos_y,0.0f,transform);
    transform = Scale(scale_x,scale_y,1.0f,transform);
    transform = Rotate(0.0f,0.0f,rotate,transform);

    Prepare();

    m_rectangle_vao.Bind();
    
    m_shader.SetUniform("input_color",color);
    m_shader.SetUniform("transform_matrix",transform);
    
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr);
}

void Renderer::ClearColor( float red, float green, float blue, float alpha )
{
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Prepare()
{
    m_shader.Use();
}