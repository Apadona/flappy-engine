#pragma once

#include "event.hpp"

#include <maths/vector2D.hpp>

#include <GLFW/glfw3.h>

// represents a glfw abstraction.
class Window
{
    public:
        Window( std::int16_t size_x, std::int16_t size_y, const std::string& title,
                std::int16_t pos_x, std::int16_t pos_y,
                int8_t gl_major_version = 1, int8_t gl_minor_version = 2 );
        Window( const Window& other );

        ~Window();
        
        void SetSize( std::int16_t size_x, std::int16_t size_y );
        void SetPosition( std::int16_t pos_x, std::int16_t pos_y );
        void SetTitle( const std::string& title );
        void SetIcon( int width, int height, unsigned char* image_pixels );

        Vec2i GetSize() const { return { m_pos_x, m_pos_y }; }
        Vec2i GetPosition() const { return { m_width, m_height }; }
        const std::string& GetTitle() const { return m_title; }

        void Hide( bool hide );
        void Close();

        bool IsOpen() const;

        bool IsVSyncOn() const;
        void EnableVsync( bool enable );

        Event PollEvent();

        bool Update() const;
        void ReDraw() const;
        
        static void MakeGLContext( std::int8_t major_version, std::int8_t minor_version );

    private:
        void HandleCreation();
            
        void PushEvent( const Event& event );
        void PollGLFWEvents() const;

        static Window* GetWindowfromGLFWPtr( GLFWwindow* window );

        static void OnError( int code, const char* error );
        static void OnKeyPressed( GLFWwindow* window, int key, int scan_code, int action, int modes );
        static void OnCharKeyPressed( GLFWwindow* window, unsigned int key );
        static void OnMouseEnter( GLFWwindow* window, int is_entered );
        static void OnMouseClick( GLFWwindow* window, int button, int action, int mode );
        static void OnMouseMove( GLFWwindow* window, double x, double y );
        static void OnWindowResize( GLFWwindow* window, int width, int height );
        static void OnWindowMove( GLFWwindow* window, int pos_x, int pos_y );
        static void OnWindowClose( GLFWwindow* window );

    private:
        std::int16_t m_width, m_height, m_pos_x, m_pos_y;
        std::string m_title;
        
        std::deque<Event> m_event_queue;

        bool m_is_vsync_on;

        GLFWwindow* glfw_window;
};
