#include <engine.hpp>

class SandBoxApp : public Application
{
    public:
        SandBoxApp() : m_particle_system(5,0.25,5,false,1000,10)
        {
            m_title = "sandbox";
            m_width = 800, m_height = 600;
        }

        bool Init( CommandLineArguments _args ) override
        {
            if( _args.GetCount() >= 3 )
            {
                // casting done to avoid compiler warning.
                m_width = static_cast<uint32_t>(std::stoi(_args[1].value()));
                m_height = static_cast<uint32_t>(std::stoi(_args[2].value()));
            }

            LOG_NORMAL("application is initialized succesfully!\n");
            return true;
        }

        bool OnCreate() override
        {
            if( !renderer.Init(m_width,m_height) )
            {
                LOG_ERROR("could not initialize Renderer!");
                return false;
            }

            font = FontLoader::Load("data/fonts/arial.ttf",12,12);
            text.SetFont(font);
            text.SetText("testing the text rendering system!\n");
            text.SetSize(10,10);
            text.SetPosition(10,10);
            text.SetColor({1.0f,1.0f,1.0f,1.0f});

            Random::Init(1000);
            bird_animations.Create("data/textures/bird_atlas.png");
            bird_atlas.SetTexture(bird_animations,5,3,183,168,14,0,0);
            std::vector<uint8_t> filters = { 1,0,1,1,1,1,1,1,1,1,1,1,1,1,1 };
            bird_atlas.SetFilter(filters);
            //atlas.Set(1);
            sprite.SetTexture(bird_animations);
            sprite.SetColor({0.7f,0.4f,0.5f,0.5f});

            int bpp = 3;
            int width = 16;
            int height = 16;
            unsigned char* image_icon = stbi_load("data/images/mouse_icon.png",&width,&height,&bpp,4);
            m_window->SetIcon(16,16,image_icon);

            return true;
        }

        bool OnUpdate( double dt ) override
        {
            if( m_window->IsOpen() )
            {
                auto event = m_window->PollEvent();

                if( event.m_type == EventType::WINDOW_CLOSE )
                    m_window->Close();

                else if( event.m_type == EventType::MOUSE_CLICK )
                {
                    if( event.m_data.mouse_button_event.button == MouseButton::LEFT )
                    {
                        if( event.m_data.mouse_button_event.state == ButtonState::PRESSED )
                            LOG_NORMAL("left mouse button is pressed!");
                        else
                            LOG_NORMAL("left mouse button is released!");
                    }

                    else if( event.m_data.mouse_button_event.button == MouseButton::RIGHT )
                    {
                        if( event.m_data.mouse_button_event.state == ButtonState::PRESSED )
                            LOG_NORMAL("right mouse button is pressed!");
                        else
                            LOG_NORMAL("right mouse button is released!");
                    }
                }

                else if( event.m_type == EventType::MOUSE_MOVED )
                {
                    //LOG_NORMAL("mouse moved at positions:",x,",",y);
                }

                else if( event.m_type == EventType::WINDOW_MOUSE_ENTER )
                {
                    //LOG_NORMAL("mouse ", (enter)? "entered" : "left", " window.");
                }

                else if( event.m_type == EventType::KEYBOARD_BUTTON )
                {
                    if( event.m_data.key_event.key == KeyboardKey::ESCAPE )
                    {
                        Application::Exit();
                    }
                }

                renderer.ClearColor(0.2f,0.3f,0.4f,1.0f);
                // renderer.DrawRectangle(0.0f,0.0f,0.2f,0.2f,0.0f,{0.7f,0.4f,0.5f,1.0f},bird_animations);
                // renderer.DrawText(text);

                m_particle_system.update(dt);
                renderer.DrawParticles(m_particle_system);
                
                m_window->ReDraw();

                // TODO:this should change later.
                std::this_thread::sleep_for(std::chrono::duration<double>(0.01));

                return true;
            }

            return false;
        }

        bool OnClose() override { return true; }

    private:
        Renderer renderer;

        Sprite sprite;
        Texture bird_animations;
        TextureAtlas bird_atlas;

        ParticleSystem m_particle_system;

        Font font;
        Text text;
};

REGISTER_APP(SandBoxApp)