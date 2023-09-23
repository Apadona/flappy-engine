#include "application.hpp"

#include <stb_image/stb_image.h>

#include <graphics/renderer.hpp>
#include <graphics/texture_manager.hpp>

extern Application* RegisterApplication();

class EngineInterface
{
    public:
        static bool Start( int argc, char** argv, char** env )
        {
            if( InitializeModules() )
            {
                Application* app = RegisterApplication();
                if( StartApplication(app,argc,argv,env) )
                {
                    HandleApplication(app);

                    PrepareForExit(app);

                    CORE_LOG_HINT("Engine Application run successfully!");

                    return true;
                }

                CORE_LOG_ERROR("could not start the application! exiting.");
                return false;
            }

                std::cerr << "Could not Initialize one or more modules! exiting.\n";
                return false;
        }
        
    private:
        static bool InitializeModules()
        {
            if( Logger::Init() )
                InitializeLoggers();

            else
            {
                std::cerr << "could not initialize Logger!\n";
                return false;
            }
            
            if( !glfwInit() )
            {
                CORE_LOG_ERROR("cannot initialize glfw!");
                glfwTerminate();
                return false;
            }

            if( !FontLoader::Init() )
            {
                CORE_LOG_ERROR("cannot initalize freetype!");
                return false;
            }

            stbi_set_flip_vertically_on_load(true);

            return true;
        }

        static bool StartApplication( Application* app, int argc, char** argv, char** env )
        {
            if( !app->Init({argc,argv,env}) )
            {
                CORE_LOG_ERROR("application initialization failed.\n");
                return false;
            }

            app->m_window = new Window(app->m_width,app->m_height,app->m_title,400,250,3,1);
            if( !app->m_window->IsOpen() )
            {
                CORE_LOG_ERROR("cannot create the glfw window!\n");
                glfwTerminate();
                return false;
            }

            if( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) )
            {
                CORE_LOG_ERROR("cannot get OpenGL functions!\n");
                glfwTerminate();
                return false;
            }

            TextureManager::Init();

            if( !app->OnCreate() )
                return false;

            return true;
        }

        static void HandleApplication( Application* app )
        {
            Timer timer;
            TickType application_update_time = 0;

            while( !app->m_should_exit && app->OnUpdate( static_cast<double>(application_update_time) / 1000000 ) )
            {
                application_update_time = timer.GetElapsedTime<MicroSeconds>();
                timer.Reset();
            }
        }

        static void PrepareForExit( Application* app )
        {
            app->OnClose();

            glfwTerminate();

            FontLoader::Terminate();
        }
};

int main( int argc, char** argv, char** env )
{
    if( EngineInterface::Start(argc,argv,env) )
        return 0; // in case that everything handled fine.

    return -1; // in case that something went wrong.
}
