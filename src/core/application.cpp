#include "application.hpp"

ProgramArguments::ProgramArguments( int argc, char** argv, char** env )
{
    this->argc = argc;
    this->argv = argv;
    this->env = env;
}

ProgramArguments::ProgramArguments( const ProgramArguments& other )
{
    argc = other.argc;
    argv = other.argv;
    env = other.env;
}

CommandLineArguments::CommandLineArguments( int argc, char** argv, char** env ) :
                                            m_count(static_cast<uint32_t>(argc)),
                                            standard_arguments(argc,argv,env)
{
    for( std::uint32_t i = 0; i < m_count; ++i )
        m_arguments.emplace_back(argv[i]);

    char** env_ptr = env;

    while( *env_ptr )
    {
        char* str_ptr = *env_ptr;
        auto str_length = std::strlen(str_ptr);
        char* str_start = *env_ptr;

        while( *str_ptr )
        {
            if( *str_ptr == '=' )
            {
                m_enviroment_variables.emplace(
                    std::pair<std::string,std::string>(
                    {str_start,str_ptr},{str_ptr + 1,str_ptr + str_length})
                );

                break;
            }

            ++str_ptr;
            --str_length;
        }

        ++env_ptr;
    }
}

std::optional<std::string> CommandLineArguments::operator[]( uint32_t index )
{
    if( index <= m_count )
        return m_arguments[index];

    else
    {
        CORE_LOG_WARNING("attempted to accesss a non existence argument in command line arguments!");
        return {};
    }
}

std::optional<std::string> CommandLineArguments::operator[]( const std::string& ev )
{
    return m_enviroment_variables[ev];
}

void Application::Exit()
{
    m_should_exit = true;
}