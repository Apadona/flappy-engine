#include "application.hpp"

extern Application* RegisterApplication();

#include <graphics/renderer.hpp>
#include <stb_image/stb_image.h>
#include <graphics/texture_manager.hpp>

const std::string texture_path = "data/textures/";

int main( int argc, char** argv, char** env )
{
    if( !Logger::Init() )
    {
        std::cerr << "could not initialize Logger!\n";
        return -1;
    }

    InitializeLoggers();
    
    if( !glfwInit() )
    {
        CORE_LOG_ERROR("cannot init glfw!");
        glfwTerminate();
        return 0;
    }

    stbi_set_flip_vertically_on_load(true);

    Application* app = RegisterApplication();
    
    if( !app->Init(argc,argv,env) )
    {
        CORE_LOG_ERROR("application initialization failed.\n");
        return -1;
    }

    app->m_window = new Window(app->m_width,app->m_height,app->m_title,3,1);
    if( !app->m_window->IsOpen() )
    {
        CORE_LOG_ERROR("cannot create the glfw window!\n");
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    if( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) )
    {
        CORE_LOG_ERROR("cannot get OpenGL functions!\n");
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    TextureManager::Init();

    app->OnCreate();
    
    while( app->OnUpdate(1.0f) )
    {
    }

    app->OnClose();

    return 0;
}
