#pragma once

#include "gl_data_types.hpp"
#include <maths/vector2D.hpp>
#include <maths/vector3D.hpp>
#include <maths/vector4D.hpp>
#include <maths/matrix.hpp>

#include <glad/glad.h>
#include <glm/matrix.hpp>

// represends an OpenGL shader.
class Shader
{
    public:
        Shader() = default;
        Shader( const std::string& vs_path, const std::string& fs_path );
        // Shader( const std::fstream& vs_file_path, const std::fstream& fs_file_path );

        ~Shader();

        bool Create( const std::string& vs_path, const std::string& fs_path );
        bool CompileShader( const std::string& vs_source, const std::string& fs_source );

        bool Use( bool use = true ) const;

        void SetAttributeLocation( const std::string& attrib_name, GLint attrib_location );
        bool HasAttribute( const std::string& name ) const;
        // recives the location from OpenGL dirver.
        GLint GetAttributeLocation( const std::string& attrib_name );
        // recives the location from the cached location( std::vector ).
        GLint GetAttributeCachedLocation( const std::string& uniform_name ) const;

        template<typename T>
        bool SetUniform( const std::string& uniform_name, const T& data )
        {
            if( !HasUniform(uniform_name) )
            {
                CORE_LOG_ERROR("attempted to set a non existing uniform.");
                return false;
            }

            if constexpr( std::is_same<T,bool>::value )
                return SetUniformBool(uniform_name,data);

            if constexpr( std::is_same<T,int>::value || std::is_same<T,unsigned int>::value )
                return SetUniformInt(uniform_name,data);

            if constexpr( std::is_same<T,int16_t>::value || std::is_same<T,uint16_t>::value )
                return SetUniformInt(uniform_name,data);

            if constexpr( std::is_same<T,float>::value )
                return SetUniformFloat(uniform_name,data);

            if constexpr( std::is_same<T,double>::value )
                return SetUniformFloat(uniform_name,static_cast<float>(data));

            if constexpr( std::is_same<T,Vec2>::value )
                return SetUniformVec2f(uniform_name,data);

            if constexpr( std::is_same<T,Vec3>::value )
                return SetUniformVec3f(uniform_name,data);

            if constexpr( std::is_same<T,Vec4>::value )
                return SetUniformVec4f(uniform_name,data);

            if constexpr( std::is_same<T,Mat2f>::value )
                return SetUniformMatrix2f(uniform_name,data);

            if constexpr( std::is_same<T,Mat3f>::value )
                return SetUniformMatrix3f(uniform_name,data);

            if constexpr( std::is_same<T,Mat4f>::value )
                return SetUniformMatrix4f(uniform_name,data);

            if constexpr( std::is_same<T,glm::mat4>::value )
                return SetUniformMatrix4f(uniform_name,data);

            // if constexpr( std::is_same<T,Mat44d>::value )
            // {
            //     Mat4f temp;
            //     for( int i = 0; i < data.Length(); ++i )
            //     {
            //         // temp[i] = data[i];
            //     }
            //     return SetUniformMatrix4f(uniform_name,temp);
            // }

            CORE_LOG_ERROR("the data passed to shader uniform is not supported!\n");

            return false;
        }

        bool HasUniform( const std::string& name ) const;
        // recives the location from OpenGL dirver.
        GLint GetUniformLocation( const std::string& uniform_name ) const;
        // recives the location from the cached location( std::vector ).
        GLint GetUniformCachedLocation( const std::string& uniform_name ) const;

        void PrintAttributes() const;
        void PrintUnifroms() const;

        bool SetUniformBool( const std::string& uniform_name, bool value );
        bool SetUniformInt( const std::string& uniform_name, int value );
        bool SetUniformFloat( const std::string& uniform_name, float value );
        //bool SetUniformDouble( const std::string& uniform_name, double value ); not supported yet.

        bool SetUniformVec2f( const std::string& uniform_name, const Vec2& value );
        bool SetUniformVec3f( const std::string& uniform_name, const Vec3& value );
        bool SetUniformVec4f( const std::string& uniform_name, const Vec4& value );

        bool SetUniformMatrix2f( const std::string& uniform_name, const Mat2f& value );
        bool SetUniformMatrix3f( const std::string& uniform_name, const Mat3f& value );
        bool SetUniformMatrix4f( const std::string& uniform_name, const Mat4f& value );
        bool SetUniformMatrix4f( const std::string& uniform_name, const glm::mat4& value );

        bool IsMade() const { return m_is_made; }

    private:
        void GetAllAttribs();
        void GetAllUniforms();

        /*
        template<typename GLFunction,typename... Args>
        bool SetUniformImplemention( const std::string& uniform_name, GLFunction function, 
                                                            Args&&... value) const;*/

    private:
        std::string m_vertex_source;
        std::string m_fragment_source;
        
        GLuint m_program_id;
        GLuint m_vs_id;
        GLuint m_fs_id;
        bool m_is_made = false;

        // represends an Uniform or an attrib.
        class GLData
        {
            // Only shader class Should be able to modify the Data in GLData.
            friend class Shader;
            
            public:
                GLData( const std::string& name, GLDataType type, GLint location );
                GLData( GLData&& other );

                GLData() = delete;
                GLData( const GLData& other ) = delete;

                const std::string& GetName() const { return m_name; }
                GLDataType GetType() const { return m_type; }
                GLuint GetSize() const { return m_size; }
                GLuint GetLocation() const { return m_location; }

            private:
                std::string m_name;
                GLDataType m_type;
                GLuint m_size;
                GLint m_location;
        };

        using UniformSet = std::vector<GLData>;
        using AttributeSet = std::vector<GLData>;

        UniformSet m_uniforms;
        AttributeSet m_attributes;
};