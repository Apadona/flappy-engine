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
    public:        
        virtual bool Init( int argc, char** argv, char** env ) = 0;

        virtual void OnCreate() = 0;
        virtual bool OnUpdate( float dt ) = 0;
        virtual void OnClose() = 0;

        virtual void UpdateScreen() const = 0; // HACK. will change later.
};

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
};
