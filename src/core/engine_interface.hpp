#pragma once

#include "application.hpp"

#include <stb_image/stb_image.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <graphics/renderer.hpp>
#include <graphics/texture_manager.hpp>

extern Application* RegisterApplication();

class EngineInterface
{
    friend int main(int argc, char** argv, char** env);
    
    public:
        static void ShouldDisplayFpsOnWindowTitle( bool should );

        static void SetRefreshRate( double fps );

        static double GetRefreshRate();

        static bool isDisplayingFpsOnWindowTitle();

    private:
        static bool StartEngine( int argc, char** argv, char** env );
        
    private:
        static bool InitializeModules();

        static bool StartApplication( Application* app, int argc, char** argv, char** env );

        static void HandleApplicationUpdateLogic( Application* app );

        static void PrepareForExit( Application* app );

        private:
            inline static double m_refresh_rate = 60.0;
            inline static bool m_should_display_fps_on_window = true;
};