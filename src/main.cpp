#include <flappy_app.hpp>
#include <utils/logger.hpp>
#include <utils/file_loader.hpp>
#include <graphics/shader.hpp>

int main()
{
    if( !Logger::Init() )
    {
        std::cerr << "could not initialize Logger!\n";
        return -1;
    }
    
    Application* app = new FlappyApp("flappy_game",800,600);
    app->Init();

    app->OnCreate();
    
    app->OnUpdate(1);

    const float triangle[6] = 
    {
        0.0f,0.5f,
        0.5f,-0.5f,
        -0.5f,-0.5f
    };

    GLuint vao;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

    GLuint buffer;
    glGenBuffers(1,&buffer);
    glBindBuffer(GL_ARRAY_BUFFER,buffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(triangle),triangle,GL_STATIC_DRAW);

    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    const char *vertex_shader_source = "#version 130\n"
    "layout (location = 0) in vec2 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
    "}\0";

    const char *fragment_shader_source = "#version 130\n"
    "out vec4 final_color;\n"
    "void main()\n"
    "{\n"
    "   final_color = vec4(1.0, 0.0, 0.0f, 1.0);\n"
    "}\0";

    //Shader shader("shaders/vertex.vert","shaders/fragment.frag");
    Shader shader;
    shader.CompileShader(vertex_shader_source,fragment_shader_source);
    if( shader.IsMade() )
        shader.Use();

    while(app->OnUpdate(1.0f))
    {
        glDrawArrays(GL_TRIANGLES,0,3);
    }

    std::cin.get();

    return 0;
}
