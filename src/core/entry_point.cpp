#include "application.hpp"

extern Application* RegisterApplication();

#include <stb_image/stb_image.h>

#include <graphics/renderer.hpp>
#include <graphics/texture_manager.hpp>

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
        CORE_LOG_ERROR("cannot initialize glfw!");
        glfwTerminate();
        return -1;
    }

    if( !FontLoader::Init() )
    {
        CORE_LOG_ERROR("cannot initalize freetype!");
        return -1;
    }

    stbi_set_flip_vertically_on_load(true);

    Application* app = RegisterApplication();
    
    if( !app->Init({argc,argv,env}) )
    {
        CORE_LOG_ERROR("application initialization failed.\n");
        return -1;
    }

    app->m_window = new Window(app->m_width,app->m_height,app->m_title,3,1);
    if( !app->m_window->IsOpen() )
    {
        CORE_LOG_ERROR("cannot create the glfw window!\n");
        glfwTerminate();
        return -1;
    }

    if( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) )
    {
        CORE_LOG_ERROR("cannot get OpenGL functions!\n");
        glfwTerminate();
        return -1;
    }

    TextureManager::Init();

    app->OnCreate();
    
    Timer timer;
    TickType application_update_time = 0;

    while( app->OnUpdate( static_cast<double>(application_update_time) / 1000000 ) )
    {
        application_update_time = timer.GetElapsedTime<MicroSeconds>();
        timer.Reset();
    }

    app->OnClose();

    glfwTerminate();

    FontLoader::Terminate();

    CORE_LOG_HINT("Engine Application run successfully!");

    return 0;
}
