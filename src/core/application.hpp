#pragma once

#include <glad/glad.h>

#include "window.hpp"

struct ProgramArguments
{
    ProgramArguments( int argc, char** argv, char** env );
    ProgramArguments( const ProgramArguments& other );

    int argc;
    char** argv;
    char** env;
};

class CommandLineArguments
{
    using EnviromentVariables = std::map<std::string,std::string>;

    public:
        CommandLineArguments( int argc, char** argv, char** env );

        uint32_t GetCount() const { return m_count; }
        std::vector<std::string> GetAllArguments() const { return m_arguments; }

        // for those who want to work with the standard way of dealing with arguments.
        ProgramArguments AsStandard_C() const { return standard_arguments; }

        std::optional<std::string> operator[]( std::uint32_t index );
        std::optional<std::string> operator[]( const std::string& ev ); // for enviroment_variables.

    private:
        uint32_t m_count;
        std::vector<std::string> m_arguments;
        EnviromentVariables m_enviroment_variables;

        ProgramArguments standard_arguments;
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
        virtual bool Init( CommandLineArguments _args ) = 0;

        virtual bool OnCreate() = 0;
        virtual bool OnUpdate( double dt ) = 0;
        virtual bool OnClose() = 0;

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
}
