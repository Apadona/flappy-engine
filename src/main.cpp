#include <flappy_app.hpp>
#include <utils/logger.hpp>
#include <utils/file_loader.hpp>
#include <graphics/shader.hpp>
#include <graphics/vertex_buffer.hpp>

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

    Shader shader("shaders/vertex.vert","shaders/fragment.frag");
    if( shader.IsMade() )
        shader.Use();

    std::vector<float> triangle =
    {
        0.0f,0.5f,
        -0.5f,-0.5f,
        0.5f,-0.5f
    };

    std::vector<unsigned int> indicies =
    {
        0,1,2
    };

    GLuint vao;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

    VertexBuffer buffer(triangle);
    buffer.Bind();

    IndexBuffer i_buffer(indicies);
    i_buffer.Bind();

    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    while(app->OnUpdate(1.0f))
    {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr);

        app->UpdateScreen();
    }

    std::cin.get();

    return 0;
}
