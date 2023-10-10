#include "window.hpp"

Window::Window( std::int16_t size_x, std::int16_t size_y, const std::string& title,
                std::int16_t pos_x, std::int16_t pos_y,
                int8_t gl_major_version, int8_t gl_minor_version ) :

                m_width(size_x), m_height(size_y), m_pos_x(pos_x), m_pos_y(pos_y), m_title(title),
                m_is_vsync_on(false)
{
    HandleCreation();
}

Window::Window( const Window& other ) : m_width(other.m_width), m_height( other.m_height ),
                 m_pos_x(other.m_pos_x), m_pos_y(other.m_pos_y), m_title(other.m_title)
{
    HandleCreation();
}

Window::~Window()
{
    glfwDestroyWindow(m_glfw_window);
}

void Window::SetSize( std::int16_t size_x, std::int16_t size_y )
{
    m_width = size_x, m_height = size_y;
    glfwSetWindowSize(m_glfw_window,m_width,m_height);
}

void Window::SetPosition( std::int16_t pos_x, std::int16_t pos_y )
{
    m_pos_x = pos_x, m_pos_y = pos_y;
    glfwSetWindowPos(m_glfw_window,m_pos_x,m_pos_y);
}

void Window::SetTitle( const std::string& title )
{
    m_title = title;
    glfwSetWindowTitle(m_glfw_window,m_title.data());
}

void Window::SetIcon( int width, int height, unsigned char* image_pixels )
{
    GLFWimage image;
    image.width = width;
    image.height = height;
    image.pixels = image_pixels;

    glfwSetWindowIcon(m_glfw_window,1,&image);
}

void Window::Maximize()
{
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if( monitor )
    {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
        
        // GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "My Title", monitor, NULL);
        SetSize(mode->width,mode->height);
    }
}

void Window::Minimize()
{
    glfwIconifyWindow(m_glfw_window);
}

void Window::Hide( bool hide )
{
    if( hide )
        glfwShowWindow(m_glfw_window);

    else
        glfwHideWindow(m_glfw_window);
}

void Window::Close()
{
    glfwSetWindowShouldClose(m_glfw_window,true);
}

bool Window::IsOpen() const
{
    return !glfwWindowShouldClose(m_glfw_window);
}

bool Window::IsVSyncOn() const
{
    return m_is_vsync_on;
}

void Window::EnableVsync( bool enable )
{
    if( enable && !m_is_vsync_on )
    {
        glfwSwapInterval(1); // TODO: i don't know if this value is correct.
        m_is_vsync_on = true;
    }

    else if( !enable && m_is_vsync_on )
    {
        glfwSwapInterval(0);
        m_is_vsync_on = false;
    }
}

void Window::MakeGLContext( std::int8_t major_version, std::int8_t minor_version )
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,major_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,minor_version);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Event Window::PollEvent()
{
    if( !m_event_queue.empty() )
    {
        auto event = m_event_queue.front();
        m_event_queue.pop_front();
        return event;
    }

    PollGLFWEvents();

   return {};
}

bool Window::Update() const
{
    if( IsOpen() )
    {
        PollGLFWEvents();
        
        return true;
    }

    return false;
}

void Window::ReDraw() const
{
    glfwSwapBuffers(m_glfw_window);
}

GLFWwindow* Window::GetGLFWWindowHandle()
{
    return m_glfw_window;
}

void Window::HandleCreation()
{
    MakeGLContext(3,3);

    m_glfw_window = glfwCreateWindow(m_width,m_height,m_title.data(),nullptr,nullptr);

    glfwMakeContextCurrent(m_glfw_window);

    glfwSetWindowUserPointer(m_glfw_window,this);

    glfwGetWindowPos(m_glfw_window,(int*)&m_pos_x,(int*)&m_pos_y);

    glfwSetErrorCallback(OnError);
    glfwSetCursorEnterCallback(m_glfw_window,OnMouseEnter);
    glfwSetMouseButtonCallback(m_glfw_window,OnMouseClick);
    glfwSetCursorPosCallback(m_glfw_window,OnMouseMove);
    glfwSetKeyCallback(m_glfw_window,OnKeyPressed);
    glfwSetCharCallback(m_glfw_window,OnCharKeyPressed);
    glfwSetFramebufferSizeCallback(m_glfw_window,OnWindowResize);
    glfwSetWindowCloseCallback(m_glfw_window,OnWindowClose);

    glfwSwapInterval(0);
}

void Window::PushEvent( const Event& event )
{
    m_event_queue.push_back(event);
}

void Window::PollGLFWEvents() const
{
    glfwPollEvents();
}

Window* Window::GetWindowfromGLFWPtr( GLFWwindow* m_glfw_window )
{
    auto _window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(m_glfw_window));
    return _window;
}

void Window::OnError( int code, const char* error )
{
    CORE_LOG_ERROR("glfw error code occured!\ncode: ",code,"\n error message:",error);
}

void Window::OnKeyPressed( GLFWwindow* window, int key, int scan_code, int action, int modes )
{
    auto _window = reinterpret_cast<Window*>(GetWindowfromGLFWPtr(window));

    Event event;
    event.m_category = EventCategory::KEYBOARD;
    event.m_type = EventType::KEYBOARD_BUTTON;

    auto key_state = ButtonState::NONE;

    if( action == GLFW_PRESS )
        key_state = ButtonState::PRESSED;

    else if( action == GLFW_REPEAT )
        key_state = ButtonState::REPEAT;

    else if( action == GLFW_RELEASE )
        key_state = ButtonState::RELEASED;

    event.m_data.key_event.state = key_state;
    event.m_data.key_event.key = static_cast<KeyboardKey>(key);
    event.m_data.key_event.special_key = static_cast<SpecialKey>(modes);

    _window->PushEvent(event);
}

void Window::OnCharKeyPressed( GLFWwindow* window, unsigned int key )
{
}

void Window::OnMouseEnter( GLFWwindow* window, int is_entered )
{
    auto _window = GetWindowfromGLFWPtr( window );

    Event event;
    event.m_category = EventCategory::MOUSE;
    event.m_type = EventType::WINDOW_MOUSE_ENTER;

    if( is_entered )
    {
        event.m_data.window_mouse_event.enter = true;
        event.m_data.window_mouse_event.leave = false;
    }

    else
    {
        event.m_data.window_mouse_event.enter = false;
        event.m_data.window_mouse_event.leave = true;
    }

    return _window->PushEvent(event);
}

void Window::OnMouseClick( GLFWwindow* window, int button, int action, int mode )
{
    auto _window = GetWindowfromGLFWPtr( window );
    
    Event event;
    event.m_category = EventCategory::MOUSE;
    event.m_type = EventType::MOUSE_CLICK;

    if( action == GLFW_PRESS )
        event.m_data.mouse_button_event.state = ButtonState::PRESSED;

    if( action == GLFW_RELEASE )
        event.m_data.mouse_button_event.state = ButtonState::RELEASED;

    event.m_data.mouse_button_event.button = static_cast<MouseButton>(button);

    _window->PushEvent(event);
}

void Window::OnMouseMove( GLFWwindow* window, double x, double y )
{
    auto _window = GetWindowfromGLFWPtr(window);

    Event event;
    event.m_category = EventCategory::MOUSE;
    event.m_type = EventType::MOUSE_MOVED;
    event.m_data.mouse_move_event.move_x = x;
    event.m_data.mouse_move_event.move_y = y;

    _window->PushEvent(event);
}

void Window::OnWindowResize( GLFWwindow* window, int width, int height )
{
    auto _window = GetWindowfromGLFWPtr( window );
    _window->m_width = width, _window->m_height = height;

    Event event;
    event.m_category = EventCategory::WINDOW;
    event.m_type = EventType::WINDOW_RESIZE;
    event.m_data.window_resize_event.width = _window->m_width;
    event.m_data.window_resize_event.height = _window->m_height;
    event.m_data.window_resize_event.maximized = false;

    _window->PushEvent(event);

    glViewport(0,0,width,height);
}

void Window::OnWindowMove( GLFWwindow* window, int pos_x, int pos_y )
{
    auto _window = GetWindowfromGLFWPtr( window );
    _window->m_pos_x = pos_x, _window->m_pos_y = pos_y;

    Event event;
    event.m_category = EventCategory::WINDOW;
    event.m_type = EventType::WINDOW_MOVE;
    event.m_data.window_move_event.x = _window->m_pos_x;
    event.m_data.window_move_event.y = _window->m_pos_y;

    _window->PushEvent(event);
}

void Window::OnWindowClose( GLFWwindow* window )
{
    auto _window = GetWindowfromGLFWPtr( window );

    Event event;
    event.m_category = EventCategory::WINDOW;
    event.m_type = EventType::WINDOW_CLOSE;

    _window->PushEvent(event);
}