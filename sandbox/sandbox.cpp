#include <engine.hpp>

class SandBoxApp : public Application
{
    public:
        SandBoxApp()
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

            font = FontLoader::Load("data/fonts/arial.ttf",10,10);
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
                    auto x = event.m_data.mouse_move_event.move_x;
                    auto y = event.m_data.mouse_move_event.move_y;

                    //LOG_NORMAL("mouse moved at positions:",x,",",y);
                }

                else if( event.m_type == EventType::WINDOW_MOUSE_ENTER )
                {
                    auto enter = event.m_data.window_mouse_event.enter;
                    //LOG_NORMAL("mouse ", (enter)? "entered" : "left", " window.");
                }

                else if( event.m_type == EventType::KEYBOARD_BUTTON )
                {
                    auto key = event.m_data.key_event.key;
                    auto state = event.m_data.key_event.state;
                    auto special = event.m_data.key_event.special_key;

                    if( key == KeyboardKey::SPACE && ( state == ButtonState::REPEAT || state == ButtonState::PRESSED ) )
                        bird_atlas.Next();
                }

                renderer.ClearColor(0.2f,0.3f,0.4f,1.0f);
                renderer.DrawRectangle(0.0f,0.0f,0.2f,0.2f,0.0f,{0.7f,0.4f,0.5f,1.0f},bird_animations);
                //renderer.DrawText(text);
                
                m_window->ReDraw();

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

        Font font;
        Text text;
};

REGISTER_APP(SandBoxApp)