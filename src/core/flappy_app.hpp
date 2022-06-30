#pragma once

#include "application.hpp"

#include "window.hpp"

class FlappyApp : public Application
{
    public:
        FlappyApp();

        bool Init( int argc, char** argv, char** env ) override;

        void OnCreate() override;
        bool OnUpdate( float dt ) override;
        void OnClose() override;

        void UpdateScreen() const override;
    
    private:
        std::string name;

        Window* game_window;
        int16_t m_width,m_height;
};