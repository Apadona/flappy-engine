#include "flappy_app.hpp"
#include <utils/logger.hpp>
#include <utils/file_loader.hpp>
#include <utils/lerp.hpp>
#include <graphics/renderer.hpp>

int main()
{
    if( !Logger::Init() )
    {
        std::cerr << "could not initialize Logger!\n";
        return -1;
    }

    Logger::Get().SetFlags(LoggerFlags::MENTION_LOG_LEVEL);
    Logger::Get().SetType(LogType::CORE);
    Logger::Get().SetFlags(LoggerFlags::MENTION_TYPE);
    
    Application* app = new FlappyApp("flappy_game",800,600);
    app->Init();

    app->OnCreate();

    Renderer renderer;
    if( !renderer.Init() )
    {
        LOG_ERROR("could not initialize Renderer!");
        return -1;
    }

    Lerp lerp1(0,1,0.001f), lerp2(0,1,0.005f), lerp3(0,1,0.01f);

    while( app->OnUpdate(1.0f) )
    {
        auto color_r = lerp1.GetValue();
        auto color_g = lerp2.GetValue();
        auto color_b = lerp3.GetValue();

        lerp1.Update(), lerp2.Update(), lerp3.Update();

        renderer.ClearColor(0.2f,0.6f,0.4f,1.0f);
        renderer.DrawTriangle(0.0f,0.0f,1.0f,1.0f,0.0f,{color_r,color_g,color_b,1.0f});

        app->UpdateScreen();
    }

    std::cin.get();

    return 0;
}
