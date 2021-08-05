#pragma once

#include <maths/vector2D.hpp>
#include <maths/vector3D.hpp>
#include <maths/vector4D.hpp>

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <map>

// represends an OpenGL shader.
class Shader
{
    public:
        Shader() = default;
        Shader( const std::string& vs_path, const std::string& fs_path );
        // Shader( const std::fstream& vs_file_path, const std::fstream& fs_file_path );

        ~Shader();

        bool Create( const std::string& vs_path, const std::string& fs_path );
        bool IsMade() const { return m_is_made; }
        bool Use( bool use = true ) const;

        GLint GetAttribLocation( const std::string& attrib_name );
        GLint GetUniformLocation( const std::string& uniform_name );

        bool SetAttribLocation( GLint attrib_location );

        bool SetUniform2f( const std::string& uniform_name, const Vec2& value );
        bool SetUniform3f( const std::string& uniform_name, const Vec3& value );
        bool SetUniform4f( const std::string& uniform_name, const Vec4& value );

    public:
        bool CompileShader( const std::string& vs_source, const std::string& fs_source );
        void GetAllAttribs();
        void GetAllUniforms();

    private:
        std::string m_vertex_source;
        std::string m_fragment_source;
        
        GLuint m_program_id;
        GLuint m_vs_id;
        GLuint m_fs_id;
        bool m_is_made = false;

        std::map<GLint,std::string> uniforms;
        std::map<GLint,std::string> attribs;
};