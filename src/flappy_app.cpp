#include "flappy_app.hpp"

#include <iostream>
#include <cstdlib>

FlappyApp::FlappyApp( std::string_view title, int16_t width, int16_t height ) :
                      game_window(nullptr), name(title), m_width(width), m_height(height) {}

bool FlappyApp::Init()
{
    if( !glfwInit() )
    {
        std::cerr << "cannot init glfw!" << std::endl;
        glfwTerminate();
        return -1;
    }
}

void FlappyApp::OnCreate()
{
    game_window = new Window(m_width,m_height,name,3,1);
    if( !game_window->IsOpen() )
    {
        std::cerr << "cannot create the glfw window!\n";
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    if( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) )
    {
        std::cerr << "cannot glue glad and glfw!\n";
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