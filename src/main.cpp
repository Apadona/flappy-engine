#include <flappy_app.hpp>
#include <utils/logger.hpp>

int main()
{
    /*
    Application* app = new FlappyApp("flappy_game",800,600);
    app->Init();

    app->OnCreate();
    
    while( app->OnUpdate(1) );
        
    app->OnClose();
    */

    Logger::Init();
    Logger logger(SinkType::CONSOLE,LogType::APPLICATION,nullptr,nullptr);
    logger.Log(std::string("message!"));
    logger.Log(std::string("printed!"));

    std::cin.get();

    return 0;
}
