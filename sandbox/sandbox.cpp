#include "application.hpp"

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

            return true;
        }

        void OnCreate() override
        {
        }

        bool OnUpdate( float dt ) override
        {
            if( m_window->IsOpen() )
            {
                if( m_window->Update() )
                    return true;

                return false;
            }

            return false;
        }

        void OnClose() override
        {
        }
/*
        void UpdateScreen() const override
        {
            m_window->ReDraw();
        }*/
};

REGISTER_APP(SandBoxApp)