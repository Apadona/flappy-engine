#pragma once

#include <glad/glad.h>

#include "window.hpp"

class CommandLineArguments
{
    public:
        CommandLineArguments( uint32_t argc, char** argv );

        uint32_t GetCount() const { return m_count; }
        std::optional<std::string> operator[]( std::uint32_t index );

    private:
        uint32_t m_count;
        std::vector<std::string> arguments;
};

class Application
{
    friend int main( int argc, char** argv, char** env );

    public:

/*      
        Called before anything else by the engine. use this to check variables passed to
        your program and to initialize the window title and it's width and height.
        Do not create the window here, as the engine will create it for you.
*/
        virtual bool Init( int argc, char** argv, char** env ) = 0;

        virtual void OnCreate() = 0;
        virtual bool OnUpdate( float dt ) = 0;
        virtual void OnClose() = 0;

        //virtual void UpdateScreen() const = 0; // HACK. will change later.

    protected:
        std::string m_title = "engine";
        std::uint16_t m_width = 800, m_height = 600;
        Window* m_window = nullptr;
};

#define REGISTER_APP(app) \
Application* RegisterApplication() \
{\
    return new app; \
}\

/*
class WindowApplication : public Application
{
    public:
        WindowApplication();
        WindowApplication( std::int16_t width, std::int16_t height, const std::string& title,
                           std::int16_t pos_x, std::int16_t pos_y );

        const Window& GetWindow() const { return m_window; }
        const std::string& GetName() const { return m_title; }

    private:
        std::string m_title;
        Window m_window;
};*/
