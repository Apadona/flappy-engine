#include "application.hpp"

extern Application* RegisterApplication();

#include <graphics/renderer.hpp>
#include <stb_image/stb_image.h>

const std::string texture_path = "data/textures/";

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
        return 0;
    }

    Logger::Get().SetFlags(LoggerFlags::MENTION_LOG_LEVEL);
    Logger::Get().SetType(LogType::CORE);
    Logger::Get().SetFlags(LoggerFlags::MENTION_TYPE);

    Application* app = RegisterApplication();
    
    //Application* app = new FlappyApp();
    if( !app->Init(argc,argv,env) )
    {
        LOG_ERROR("application initialization failed.\n");
        return -1;
    }

    //std::uint16_t app_width = app->m_width, app_height = app->m_height;
    //std::string app_title = app->m_title;

    app->m_window = new Window(app->m_width,app->m_height,app->m_title,3,1);
    if( !app->m_window->IsOpen() )
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

    Renderer renderer;
    if( !renderer.Init() )
    {
        LOG_ERROR("could not initialize Renderer!");
        return -1;
    }

    app->OnCreate();

    glEnable(GL_BLEND);
    //Texture wood_texture(texture_path + "awesomeface.bmp");
    //Sprite sprite(&wood_texture,{{0.0f,0.0f},{1.0f,1.0f},0.0f},{0.4f,0.2f,0.8f,1.0f});

    /*int width, height, bpp;
    unsigned char* data = stbi_load("Data/Textures/white.bmp",&width,&height,&bpp,0);

    if( data )
    {
        //memset(data,255,width * height);

        glActiveTexture(GL_TEXTURE1);

        GLuint texture_id;
        glGenTextures(1,&texture_id);
        glBindTexture(GL_TEXTURE_2D,texture_id);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
    }

    else
    {
        LOG_ERROR("unable to load the texture!\n");
        std::cin.get();
        return -1;
    }

    float color_r = static_cast<float>(std::sin(glfwGetTime()));
    float color_g = static_cast<float>(std::cos(glfwGetTime()));
    float color_b = static_cast<float>(std::sin(glfwGetTime()) * cos(glfwGetTime()));*/
    
    while( app->OnUpdate(1.0f) )
    {
        renderer.ClearColor(0.1f,0.2f,0.3f,1.0f);
        renderer.DrawRectangle(0.0f,0.0f,1.0f,1.0f,0.0f,{0.7f,0.4f,0.5f,1.0f});
        
        //renderer.DrawSprite(sprite);

        app->m_window->ReDraw();
    }

    app->OnClose();

    //std::cin.get();

    return 0;
}
