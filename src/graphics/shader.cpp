#include "shader.hpp"

#include <utils/logger.hpp>
#include <utils/file_loader.hpp>

#include <glm/gtc/type_ptr.hpp>

#include <type_traits>

namespace
{
    inline bool StringEmpty( const std::string& str )
    {
        return str.empty();
    }
}

Shader::GLData::GLData( const std::string& name, GLDataType type, GLint location ) : m_name(name),
                                                                m_type(type), m_location(location)
{
    m_size = CalculateSize(m_type);
}

Shader::GLData::GLData( Shader::GLData&& other ) : m_name(std::move(other.m_name)),
                m_type(other.m_type), m_size(other.m_size),m_location(other.m_location)
{
    other.m_type = NONE;
    other.m_size = 0;
    other.m_location = -1;
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
    #undef ERROR

    bool file_path_not_empty = true;

    if( StringEmpty(vs_path) )
    {
        LOG_ERROR("vertex shader path is invalid!");
        file_path_not_empty = false;
    }

    if( StringEmpty(fs_path) )
    {
        LOG_ERROR("fragment shader path is invalid!");
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

            if( CompileShader(m_vertex_source,m_fragment_source) )
                return true;

            return false;
        }
    }
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

        GLint compile_status = 0;
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
            LOG_NORMAL("shader compiled successfully!");
    };

    LOG_NORMAL("compiling vertex shader.");
    compile_action(vertex_source.c_str(),GL_VERTEX_SHADER);
    LOG_NORMAL("compiling fragment shader.");
    compile_action(fragment_source.c_str(),GL_FRAGMENT_SHADER);

    // if we passed the compile phase successfully, we can proceed to link phase.
    if( compile_phase_passed )
    {
        m_program_id = glCreateProgram();
        glAttachShader(m_program_id,m_vs_id);
        glAttachShader(m_program_id,m_fs_id);
        glLinkProgram(m_program_id);

        GLint link_status = 0;
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

    GetAllAttribs();
    GetAllUniforms();
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

void Shader::SetAttributeLocation( const std::string& attrib_name, GLint location )
{
    glBindAttribLocation(m_program_id,0,attrib_name.c_str());
}

bool Shader::HasAttribute( const std::string& name ) const
{
    if( StringEmpty(name) )
        return false;

    for( auto& attribute : m_attributes )
    {
        if( name == attribute.m_name )
            return true;
    }

    return false;
}

GLint Shader::GetAttributeLocation( const std::string& attribute_name )
{
    if( StringEmpty(attribute_name) )
    {
        LOG_ERROR("empty string sent for getting Attribute location!\n");
        return -1;
    }

    return glGetAttribLocation(m_program_id,attribute_name.c_str());
}

GLint Shader::GetAttributeCachedLocation( const std::string& attribute_name ) const
{
    if( StringEmpty(attribute_name) )
    {
        LOG_ERROR("empty string sent for getting Attribute location!\n");
        return -1;
    }

    for( auto& attrbute : m_attributes )
        if( attrbute.m_name == attribute_name )
            return attrbute.m_location;

    return -1;
}

void Shader::PrintAttributes() const
{
    LOG_NORMAL("Attributes:");
    for( auto& attribute : m_attributes )
        LOG_NORMAL(attribute.m_name);
}

bool Shader::HasUniform( const std::string& name ) const
{
    if( StringEmpty(name) )
        return false;

    for( auto& uniform : m_uniforms )
    {
        if( name == uniform.m_name )
            return true;
    }

    return false;
}

GLint Shader::GetUniformLocation( const std::string& uniform_name ) const
{
    if( StringEmpty(uniform_name) )
    {
        LOG_ERROR("empty string sent for getting Uniform location!\n");
        return -1;
    }

    return glGetUniformLocation(m_program_id,uniform_name.c_str());
}

GLint Shader::GetUniformCachedLocation( const std::string& uniform_name ) const
{
    if( StringEmpty(uniform_name) )
    {
        LOG_ERROR("empty string sent for getting Uniform location!\n");
        return -1;
    }

    for( auto& uniform : m_uniforms )
        if( uniform.m_name == uniform_name )
            return uniform.m_location;

    return -1;
}

void Shader::PrintUnifroms() const
{
    LOG_NORMAL("Uniforms:");
    for( auto& uniform : m_uniforms )
        LOG_NORMAL(uniform.m_name);
}

// to reduce the duplicate code of setting a uniform.
#define SET_UNIFORM_IMPLEMENTION(uniform_name,gl_function,...) \
    GLint location = GetUniformLocation(uniform_name); \
    gl_function(location,__VA_ARGS__); \
    return true;

bool Shader::SetUniformBool( const std::string& uniform_name, bool value )
{
    SET_UNIFORM_IMPLEMENTION(uniform_name,glUniform1i,value)
}

bool Shader::SetUniformInt( const std::string& uniform_name, int value )
{
    SET_UNIFORM_IMPLEMENTION(uniform_name,glUniform1i,value)
}

bool Shader::SetUniformFloat( const std::string& uniform_name, float value )
{
    SET_UNIFORM_IMPLEMENTION(uniform_name,glUniform1f,value)
}

bool Shader::SetUniformVec2f( const std::string& uniform_name, const Vec2& _data )
{
    SET_UNIFORM_IMPLEMENTION(uniform_name,glUniform2f,_data.x,_data.y)
}

bool Shader::SetUniformVec3f( const std::string& uniform_name, const Vec3& _data )
{
    SET_UNIFORM_IMPLEMENTION(uniform_name,glUniform3f,_data.x,_data.y,_data.z)
}

bool Shader::SetUniformVec4f( const std::string& uniform_name, const Vec4& _data )
{
    SET_UNIFORM_IMPLEMENTION(uniform_name,glUniform4f,_data.x,_data.y,_data.z,_data.w)
}

bool Shader::SetUniformMatrix2f( const std::string& uniform_name, const Mat2f& matrix )
{
    SET_UNIFORM_IMPLEMENTION(uniform_name,glUniformMatrix2fv,1,false,matrix.GetData())
}

bool Shader::SetUniformMatrix3f( const std::string& uniform_name, const Mat3f& matrix )
{
    SET_UNIFORM_IMPLEMENTION(uniform_name,glUniformMatrix3fv,1,false,matrix.GetData())
}

bool Shader::SetUniformMatrix4f( const std::string& uniform_name, const Mat4f& matrix )
{
    SET_UNIFORM_IMPLEMENTION(uniform_name,glUniformMatrix4fv,1,false,matrix.GetData())
}

bool Shader::SetUniformMatrix4f( const std::string& uniform_name, const glm::mat4& glm_matrix )
{
    SET_UNIFORM_IMPLEMENTION(uniform_name,glUniformMatrix4fv,1,false,glm::value_ptr(glm_matrix))
}

void Shader::GetAllAttribs()
{
    GLint size;
    GLenum type;
    char buffer[2048] = {0};

    GLint count = 0;
    glGetProgramiv(m_program_id, GL_ACTIVE_ATTRIBUTES, &count);

    for ( GLint i = 0; i < count; ++i )
    {
        glGetActiveAttrib(m_program_id, (GLuint)i, 2048, nullptr, &size, &type, buffer);

        GLint location = GetUniformLocation(buffer);
        m_attributes.emplace_back(buffer,ConvertType(type),location);
    }
}

void Shader::GetAllUniforms()
{
    GLint size;
    GLenum type;
    char buffer[2048] = {0};

    GLint count = 0;
    glGetProgramiv(m_program_id, GL_ACTIVE_UNIFORMS, &count);

    for ( GLint i = 0; i <= count; ++i )
    {
        glGetActiveUniform(m_program_id, (GLuint)i, 2048, nullptr, &size, &type, buffer);

        GLint location = GetAttributeLocation(buffer);
        m_uniforms.emplace_back(buffer,ConvertType(type),location);
    }
}
/*
template<typename GLFunction,typename... Args>
bool Shader::SetUniformImplemention( const std::string& uniform_name, GLFunction gl_function,
                                                            Args&&... value ) const
{
    if( HasUniform(uniform_name) )
    {
        GLint location = GetUniformCachedLocation(uniform_name);
        gl_function(location,std::forward<Args>(value)...);
        return true;
    }

    return false;
}*/