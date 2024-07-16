#include <engine.hpp>

class SandBoxApp : public Application
{
    public:
        SandBoxApp()
        {
            m_title = "sandbox";
            m_width = 1200, m_height = 800;
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

            m_window->Maximize();

            font = FontLoader::Load("data/fonts/arial.ttf",12,12);
            text.SetFont(font);
            text.SetText("testing the text rendering system!\n");
            text.SetSize(10,10);
            text.SetPosition(10,10);
            text.SetColor({1.0f,1.0f,1.0f,1.0f});

            m_particle_system.SetWholeTime(10);
            m_particle_system.SetParticleLifeTime(2.5f);
            m_particle_system.SetEmitionRate(2.5);
            m_particle_system.SetStartParticleCount(0);
            m_particle_system.SetMaxAllowedParticles(100);
            m_particle_system.SetRepeating(true);
            m_particle_system.SetTexture("data/textures/fire_4.png");
            // m_particle_system.SetTextureChangeRate(5.0 / 15);
            // m_particle_system.SetTextureSampleParameters(5,3,183,168,0,0);
            // m_particle_system.SetSpriteSheetEnable(true);
            m_particle_system.SetVelocityOverLifeTimeBehaviour(std::vector<double>{1.0,1.0});
            m_particle_system.SetSizeOverLifeTimeBehaviour(std::vector<double>{1.0,0.5});
            m_particle_system.SetStartColor({1.0f,1.0f,1.0f,1.0f});
            m_particle_system.SetEndColor({1.0f,1.0f,1.0f,0.0f});
            m_particle_system.SetStartVelocity({0.0f,0.5f,0.0f});
            m_particle_system.SetStartSize({1.0f,1.0f,1.0f});
            
            Random::Init(1000);

            bird_animations.Create("data/textures/bird_atlas.png");
            bird_atlas.SetTexture(bird_animations,5,3,183,168,14,0,0);
            std::vector<uint8_t> filters = { 1,0,1,1,1,1,1,1,1,1,1,1,1,1,1 };   
            bird_atlas.SetFilter(filters);
            sprite.SetTexture(bird_animations);
            sprite.SetColor({0.7f,0.4f,0.5f,0.5f});

            int bpp = 3;
            int width = 16;
            int height = 16;
            unsigned char* image_icon = stbi_load("data/images/mouse_icon.png",&width,&height,&bpp,4);
            m_window->SetIcon(16,16,image_icon);

            fps = 0.0;
            rotate_value = 0.0f;

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

                // else if( event.m_type == EventType::MOUSE_MOVED )
                // {
                    //LOG_NORMAL("mouse moved at positions:",x,",",y);
                // }

                // else if( event.m_type == EventType::WINDOW_MOUSE_ENTER )
                // {
                    //LOG_NORMAL("mouse ", (enter)? "entered" : "left", " window.");
                // }

                else if( event.m_type == EventType::KEYBOARD_BUTTON )
                {
                    if( event.m_data.key_event.key == KeyboardKey::ESCAPE )
                    {
                        Application::Exit();
                    }

                    else if( event.m_data.key_event.key == KeyboardKey::SPACE )
                    {
                        bird_atlas.Next();
                        rotate_value += 6;
                    }
                }

                renderer.ClearColor(0.2f,0.3f,0.4f,1.0f);
                renderer.DrawRectangle(2.0f,2.0f,0.2f,0.2f,0.0f,{0.7f,0.4f,0.5f,1.0f},bird_animations);
                // renderer.DrawText(text);

                // m_particle_system.Update(dt);
                // renderer.DrawParticles(m_particle_system);

                DrawImguiLayer();

                m_window->ReDraw();

                // std::this_thread::sleep_for(std::chrono::duration<double>(0.001));

                return true;
            }

            return false;
        }

        bool OnClose() override { return true; }

        inline void DrawImguiLayer()
        {
            ImGui::NewFrame();

            ImGui::Begin("Particle System");

            ImGui::Text("Properties:");

            ImGui::InputDouble("Life Time",&m_particle_system.GetWholeTime());
            ImGui::InputDouble("Particle Life Time",&m_particle_system.GetLifeTimeLimit());
            ImGui::InputDouble("Emition Rate",&m_particle_system.GetEmitionRate());

            ImGui::InputInt("Max Count",reinterpret_cast<int*>(&m_particle_system.GetMaxCount()));
            ImGui::InputInt("Start Count",reinterpret_cast<int*>(&m_particle_system.GetStartCount()));
            ImGui::InputInt("Current Count",reinterpret_cast<int*>(&m_particle_system.GetCurrentCount()));

            ImGui::InputFloat3("Start Velocity",reinterpret_cast<float*>(&m_particle_system.GetStartVelocity()));

            ImGui::InputFloat3("Start Size",reinterpret_cast<float*>(&m_particle_system.GetStartSize()));

            ImGui::ColorPicker4("Start Color",reinterpret_cast<float*>(&m_particle_system.GetStartColor()));
            ImGui::ColorPicker4("End Color",reinterpret_cast<float*>(&m_particle_system.GetEndColor()));

            ImGui::Checkbox("Repeat", &m_particle_system.Repeat());
            ImGui::Checkbox("Active", &m_particle_system.Active());

            if ( ImGui::IsItemClicked(ImGui::Button("Reset")) )
            {
                m_particle_system.Reset();
            }

            ImGui::End();

            ImGui::Render();

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

    private:
        Renderer renderer;

        Sprite sprite;
        Texture bird_animations;
        TextureAtlas bird_atlas;

        ParticleSystem m_particle_system;

        Font font;
        Text text;

        double fps;
        float rotate_value;
};

REGISTER_APP(SandBoxApp)
