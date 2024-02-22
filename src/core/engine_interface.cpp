#include "engine_interface.hpp"

void EngineInterface::ShouldDisplayFpsOnWindowTitle( bool should )
{
    m_should_display_fps_on_window = should;
}

void EngineInterface::SetRefreshRate( double fps )
{
    if( fps > 0 )
    {
        m_refresh_rate = fps;
    }
}

double EngineInterface::GetRefreshRate()
{
    return m_refresh_rate;
}

bool EngineInterface::isDisplayingFpsOnWindowTitle()
{
    return m_should_display_fps_on_window;
}

bool EngineInterface::StartEngine( int argc, char** argv, char** env )
{
    if( InitializeModules() )
    {
        Application* app = RegisterApplication();
        if( StartApplication(app,argc,argv,env) )
        {
            EngineInterface::ShouldDisplayFpsOnWindowTitle(true);
            HandleApplicationUpdateLogic(app);
            PrepareForExit(app);
            CORE_LOG_HINT("Engine Application run successfully!");
            return true;
        }

        CORE_LOG_ERROR("could not start the application! exiting.");
        return false;
    }

    std::cerr << "Could not Initialize one or more modules! exiting.\n";
    return false;
}

bool EngineInterface::InitializeModules()
{
    if( Logger::Init() )
        InitializeLoggers();

    else
    {
        std::cerr << "could not initialize Logger!\n";
        return false;
    }
            
    if( !glfwInit() )
    {
        CORE_LOG_ERROR("cannot initialize glfw!");
        glfwTerminate();
        return false;
    }

    if( !FontLoader::Init() )
    {
        CORE_LOG_ERROR("cannot initalize freetype!");
        return false;
    }

    if( IMGUI_CHECKVERSION() &&  ImGui::CreateContext() )
    {
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.IniFilename = NULL; // disable constantly saving imgui widgets states into the imgui.ini file, saving performance.

        // Setup Dear ImGui style
        // ImGui::StyleColorsDark();
        ImGui::StyleColorsClassic();
    }

    else
    {
        CORE_LOG_ERROR("cannot initialize imgui!");
        return false;
    }

    stbi_set_flip_vertically_on_load(true);

    return true;
}

bool EngineInterface::StartApplication( Application* app, int argc, char** argv, char** env )
{
    if( !app->Init({argc,argv,env}) )
    {
        CORE_LOG_ERROR("application initialization failed.\n");
        return false;
    }

    app->m_window = new Window(app->m_width,app->m_height,app->m_title,400,250,4,6);

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(app->m_window->GetGLFWWindowHandle(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::LoadIniSettingsFromDisk("imgui.ini");

    if( !app->m_window->IsOpen() )
    {
        CORE_LOG_ERROR("cannot create the glfw window!\n");
        glfwTerminate();
        return false;
    }

    if( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) )
    {
        CORE_LOG_ERROR("application initialization failed.\n");
        return false;
    }

    TextureManager::Init();

    if( !app->OnCreate() )
        return false;

    return true;
}

void EngineInterface::HandleApplicationUpdateLogic( Application* app )
{
    Timer timer;
    TickType application_update_time = 0;
    double passed_time = 0.0;

    while( !app->m_should_exit && app->OnUpdate( passed_time ) )
    {
        application_update_time = timer.GetElapsedTime<MicroSeconds>();
        passed_time = application_update_time / 1000000.0;
        timer.Reset();

        double refresh_rate = 1.0 / m_refresh_rate;

        // TODO:this should be analyzed and if necessary, be changed later.
        // if( application_update_time / 1000000.0 <= refresh_rate )
        // {
        //     application_update_time = refresh_rate - (static_cast<double>(application_update_time) / 1000000);
        //     std::this_thread::sleep_for(std::chrono::duration<double>(application_update_time));
        // }

        if( m_should_display_fps_on_window )
        {
            app->m_window->SetTitle("framerate:" + std::to_string(1.0 / passed_time));
        }
    }
}

void EngineInterface::PrepareForExit( Application* app )
{
    app->OnClose();

    ImGui::SaveIniSettingsToDisk("imgui.ini");

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext();

    glfwTerminate();

    FontLoader::Terminate();
}