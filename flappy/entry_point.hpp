#include "application.hpp"

#pragma once

extern Application* app;

int main( int argc, char** argv, char** env )
{
    if( !Logger::Init() )
    {
        std::cerr << "could not initialize Logger!\n";
        return -1;
    }

    if( !glfwInit() )
    {
        LOG_ERROR("cannot init glfw!");
        glfwTerminate();
        return -1;
    }

    Logger::Get().SetFlags(LoggerFlags::MENTION_LOG_LEVEL);
    Logger::Get().SetType(LogType::CORE);
    Logger::Get().SetFlags(LoggerFlags::MENTION_TYPE);
    
    app = new FlappyApp();
    app->Init(argc,argv,env);

    app->OnCreate();

    Renderer renderer;
    if( !renderer.Init() )
    {
        LOG_ERROR("could not initialize Renderer!");
        return -1;
    }

    return 0;
}