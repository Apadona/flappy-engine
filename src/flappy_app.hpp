#pragma once

#include <application.hpp>
#include <glad/glad.h> // must be included here because it should be included before glfw3.h and window.hpp includes that!
#include <window.hpp>

class FlappyApp : public Application
{
    public:
        FlappyApp( std::string_view title, int16_t width, int16_t height );

        bool Init() override;

        void OnCreate() override;
        bool OnUpdate( float dt ) override;
        void OnClose() override;

        void UpdateScreen() const override;
    
    private:
        std::string name;

        Window* game_window;
        int16_t m_width,m_height;
};