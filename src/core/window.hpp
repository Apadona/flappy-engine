#pragma once

#include <GLFW/glfw3.h>

#include <engine_pch.hpp>

#include <maths/vector2D.hpp>

class Window
{
    public:
        Window( std::int16_t size_x, std::int16_t size_y, const std::string_view& title,
                std::int16_t pos_x, std::int16_t pos_y,
                int8_t gl_major_version = 1, int8_t gl_minor_version = 2 );
        Window( const Window& other );
        
        void SetSize( std::int16_t size_x, std::int16_t size_y );
        void SetPosition( std::int16_t pos_x, std::int16_t pos_y );
        void SetTitle( const std::string_view& title );

        Vec2i GetSize() const { return { m_x, m_y }; }
        Vec2i GetPosition() const { return { m_width, m_height }; }
        const std::string_view& GetTitle() const { return m_title; }

        void Hide( bool hide );
        void Close();

        bool IsOpen() const;

        bool Update() const;
        void ReDraw() const;
        
        static void MakeGLContext( std::int8_t major_version, std::int8_t minor_version );

    private:
        std::int16_t m_width, m_height, m_x, m_y;
        std::string_view m_title;
        
        /*struct GLContext
        {
            GLContext() : major(1), minor(2) {}
            GLContext( int8_t _major, int8_t _minor ) : major(_major), minor(_minor) {}

            int8_t major;
            int8_t minor;
        } m_gl_context;*/

        GLFWwindow* m_window;

        void HandleCreation();

        static void OnError( int code, const char* error );
        static void OnKeyPressed( GLFWwindow* window, int key, int scan_code, int action, int modes );
        static void OnCharKeyPressed( GLFWwindow* window, unsigned int key );
        static void OnMouseClick( GLFWwindow* window, int button, int action, int mode );
        static void OnMouseMove( GLFWwindow* window, double x, double y );
        static void OnWindowResize( GLFWwindow* window, int width, int height );
        static void OnWindowMove( GLFWwindow* window, int pos_x, int pos_y );
        static void OnWindowClose( GLFWwindow* window );
};
