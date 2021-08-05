#include "shader.hpp"

#include <utils/logger.hpp>
#include <utils/file_loader.hpp>

namespace
{
    inline bool StringEmpty( const std::string& str )
    {
        return str.empty();
    }
}

Shader::Shader( const std::string& vs_path, const std::string& fs_path )
{
    Create(vs_path,fs_path);
}

Shader::~Shader()
{
    glUseProgram(0);
    glDetachShader(m_program_id,m_vs_id);
    glDetachShader(m_program_id,m_fs_id);
    glDeleteShader(m_vs_id);
    glDeleteShader(m_fs_id);
    glDeleteProgram(m_program_id);
}

bool Shader::Create( const std::string& vs_path, const std::string& fs_path )
{
    bool file_path_not_empty = true;

    if( StringEmpty(vs_path) )
    {
        LOG_ERROR("vertex shader path is invalid!\n");
        file_path_not_empty = false;
    }

    if( StringEmpty(fs_path) )
    {
        LOG_ERROR("fragment shader path is invalid!\n");
        file_path_not_empty = false;
    }

    if( file_path_not_empty )
    {
        bool file_sources_not_empty = true;

        std::string vs_source = LoadFile(vs_path);

        if( StringEmpty(vs_source) )
        {
            LOG_ERROR("vertex shader source is empty!");
            file_sources_not_empty = false;
        }

        std::string fs_source = LoadFile(fs_path);

        if( StringEmpty(fs_source) )
        {
            LOG_ERROR("fragment shader source is empty!");
            file_sources_not_empty = false;
        }

        if( file_sources_not_empty )
        {
            m_vertex_source = std::move(vs_source);
            m_fragment_source = std::move(fs_source);

            CompileShader(m_vertex_source,m_fragment_source);
        }
    }
}

bool Shader::Use( bool use ) const
{
    if( m_is_made )
    {
        if( use )
            glUseProgram(m_program_id);
        else
            glUseProgram(0);
    }

    return false;    
}

GLint Shader::GetAttribLocation( const std::string& attrib_name )
{
    if( StringEmpty(attrib_name) )
        return glGetAttribLocation(m_program_id,attrib_name.c_str());
}

GLint Shader::GetUniformLocation( const std::string& uniform_name )
{
    if( StringEmpty(uniform_name) )
        return glGetUniformLocation(m_program_id,uniform_name.c_str());
}

bool Shader::SetUniform2f( const std::string& uniform_name, const Vec2& _data )
{
    glUniform2f(GetUniformLocation(uniform_name),_data.x,_data.y);
}

bool Shader::SetUniform3f( const std::string& uniform_name, const Vec3& _data )
{
    glUniform3f(GetUniformLocation(uniform_name),_data.x,_data.y,_data.z);
}

bool Shader::SetUniform4f( const std::string& uniform_name, const Vec4& _data )
{
    glUniform4f(GetUniformLocation(uniform_name),_data.x,_data.y,_data.z,_data.w);
}

bool Shader::CompileShader( const std::string& vertex_source, const std::string& fragment_source )
{
    // to indicate wheather the compile process was successful.
    bool compile_phase_passed = true;

    auto compile_action = [&]( const char* shader_source, GLenum type )
    {
        GLuint& _ref = (type == GL_VERTEX_SHADER)? m_vs_id : m_fs_id;
        _ref = glCreateShader(type);
        glShaderSource(_ref,1,&shader_source,nullptr);
        glCompileShader(_ref);

        GLint compile_status;
        glGetShaderiv(_ref,GL_COMPILE_STATUS,&compile_status);

        if( compile_status == GL_FALSE )
        {
            char compile_error_message[1024] = {0};
            glGetShaderInfoLog(_ref,1024,nullptr,compile_error_message);

            LOG_ERROR("failed to compile shader!");
            LOG_NORMAL(compile_error_message);

            compile_phase_passed = false;
        }

        else
            LOG_NORMAL("shader compiled successfully!\n");
    };

    LOG_NORMAL("compiling vertex shader.");
    compile_action(vertex_source.c_str(),GL_VERTEX_SHADER);
    LOG_NORMAL("compiling fragment shader.");
    compile_action(fragment_source.c_str(),GL_FRAGMENT_SHADER);

    // if we passed the compile phase successfully, now we can proceed to link phase.
    if( compile_phase_passed )
    {
        m_program_id = glCreateProgram();
        glAttachShader(m_program_id,m_vs_id);
        glAttachShader(m_program_id,m_fs_id);
        glLinkProgram(m_program_id);

        GLint link_status;
        glGetProgramiv(m_program_id,GL_LINK_STATUS,&link_status);

        if( link_status == GL_FALSE )
        {
            char link_error_message[1024] = {0};
            glGetProgramInfoLog(m_program_id,1024,nullptr,link_error_message);

            LOG_ERROR("failed to link shader!");
            LOG_NORMAL(link_error_message);

            return false;
        }
    }

    // if we have reached here, that means compiling and linking was successful.
    m_is_made = true;
}

void Shader::GetAllAttribs()
{
    GLint count = 0;
    glGetProgramiv(m_program_id, GL_ACTIVE_ATTRIBUTES, &count);

    GLint size;
    GLenum type;
    char buffer[2048] = {0};
    for ( GLint i = 0; i < count; i++ )
    {
        glGetActiveAttrib(m_program_id, (GLuint)i, 2048, nullptr, &size, &type, buffer);
        std::cout << "size:" << size << ' ' << buffer << std::endl;
    }
}

void Shader::GetAllUniforms()
{
    GLint count = 0;
    glGetProgramiv(m_program_id, GL_ACTIVE_ATTRIBUTES, &count);

    GLint size;
    GLenum type;
    char buffer[2048] = {0};
    for ( GLint i = 0; i < count; i++ )
    {
        glGetActiveUniform(m_program_id, (GLuint)i, 2048, nullptr, &size, &type, buffer);
        std::cout << "size:" << size << ' ' << buffer << std::endl;
    }
}