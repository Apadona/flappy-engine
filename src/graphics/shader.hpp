#pragma once

#include <maths/vector2D.hpp>
#include <maths/vector3D.hpp>
#include <maths/vector4D.hpp>

#include <glad/glad.h>

#include <string>
#include <fstream>

class Shader
{
    public:
        Shader() = default;
        Shader( const std::string& vs_source, const std::string& fs_source );
        Shader( const std::fstream& vs_file_path, const std::fstream& fs_file_path );

        bool Create( const std::string& vs_source, const std::string& fs_source );

        GLint GetAttribLocation( const std::string& attrib_name );
        GLint GetUniformLocation( const std::string& uniform_name );

        bool SetAttribLocation( GLint attrib_location );

        bool SetUniform2f( const Vec2& value );
        bool SetUniform3f( const Vec3& value );
        bool SetUniform4f( const Vec4& value );

    private:
        std::string vertex_source;
        std::string fragment_source;

        void CompileShader( const std::string& vs_source, const std::string& fs_source );
        
        GLuint program_id;
        GLuint vs_id;
        GLuint fs_id;
        bool is_made;
};