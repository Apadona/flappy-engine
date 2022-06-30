#include "flappy_app.hpp"

#include <engine_pch.hpp>

FlappyApp::FlappyApp() : name("flappy_game"), game_window(nullptr), m_width(800), m_height(600) {}

bool FlappyApp::Init( int argc, char** argv, char** env )
{
    CommandLineArguments _args(argc,argv);

    if( !glfwInit() )
    {
        LOG_ERROR("cannot init glfw!");
        glfwTerminate();
        return 0;
    }

    if( _args.GetCount() >= 3 )
    {
        // casting done to avoid compiler warning.
        m_width = static_cast<uint32_t>(std::stoi(_args[1].value()));
        m_height = static_cast<uint32_t>(std::stoi(_args[2].value()));
    }

    return true;
}

void FlappyApp::OnCreate()
{
    game_window = new Window(m_width,m_height,name,3,1);
    if( !game_window->IsOpen() )
    {
        LOG_ERROR("cannot create the glfw window!\n");
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    if( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) )
    {
        LOG_ERROR("cannot get OpenGL functions!\n");
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }
}

bool FlappyApp::OnUpdate( float dt )
{
    if( game_window->Update() )
        return true;

    return false;
}

void FlappyApp::OnClose()
{
    game_window->Close();
    glfwTerminate();
}

void FlappyApp::UpdateScreen() const
{
    game_window->ReDraw();
}