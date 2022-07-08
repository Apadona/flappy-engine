#include <engine.hpp>

class SandBoxApp : public Application
{
    public:
        SandBoxApp()
        {
            m_title = "sandbox";
            m_width = 400, m_height = 300;
        }

        bool Init( int argc, char** argv, char** env ) override
        {
            CommandLineArguments _args(argc,argv);

            if( _args.GetCount() >= 3 )
            {
                // casting done to avoid compiler warning.
                m_width = static_cast<uint32_t>(std::stoi(_args[1].value()));
                m_height = static_cast<uint32_t>(std::stoi(_args[2].value()));
            }

            LOG_NORMAL("application is initialized succesfully!\n");
            return true;
        }

        void OnCreate() override
        {
            Random::Init(1000);

            if( !renderer.Init() )
            {
                LOG_ERROR("could not initialize Renderer!");
                return;
            }
        }

        bool OnUpdate( float dt ) override
        {
            if( m_window->Update() )
            {
                renderer.ClearColor(0.1f,0.2f,0.3f,1.0f);
                renderer.DrawRectangle(0.0f,0.0f,1.0f,1.0f,0.0f,{0.7f,0.4f,0.5f,1.0f});
                //renderer.DrawSprite(sprite);

                m_window->ReDraw();

                std::cout << Random::NextDouble() << std::endl;

                return true;
            }

            return false;
        }

        void OnClose() override
        {
        }

    private:
        Renderer renderer;
};

REGISTER_APP(SandBoxApp)