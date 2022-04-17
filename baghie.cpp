using WindowID = HWND;

enum class EventCategury
{

};

enum class EventType
{
    NONE
};

class Event
{

};

class Window
{
    public:
        Window( const std::string& name = "test window", uint16_t pos_x = 800, uint16_t pos_y = 600, 
                uint16_t width = 400, uint16_t height = 300 );

        ~Window();

        void SetTitle( const std::string& name );
        void SetPosition( uint16_t pos_x, uint16_t pos_y );
        void SetSize( uint16_t width, uint16_t height );

        void Update();
        void SwapBuffers() const;

        void SetMousePosition( uint16_t pos_x, uint16_t pos_y );
        Vec2i GetMousePosition() const {  }

        const std::string& GetTitle() const { return title; }
        Vec2i GetPosition() const { return { pos_x,pos_y }; }
        Vec2i GetSize() const { return { width,height }; }
        WindowID GetID() const { return id; }

    private:
        void Initialize();
        void ValidateParameters();

    private:
        uint16_t pos_x,pos_y;
        uint16_t width,height;
        std::string title;

        // WINAPI related properties.
        WNDCLASS window_class;
        HWND id;
        friend LRESULT CALLBACK MessageFunction( HWND hwnd, UINT message, LPARAM parameter, LPARAM paramete );

        bool capture_mouse = false;
        bool hide_mouse = false;
};

void Window::Update()
{
    MSG message;
    while( PeekMessage(&message,id,0,0,PM_NOREMOVE) )
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}

LRESULT CALLBACK MessageFunction( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam )
{
    if ( message == WM_CREATE )
    {
        // Get WindowImplWin32 instance (it was passed as the last argument of CreateWindow)
        LONG_PTR window = (LONG_PTR)reinterpret_cast<CREATESTRUCT*>(lparam)->lpCreateParams;

        // Set as the "user data" parameter of the window
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, window);
    }

    // Get the WindowImpl instance corresponding to the window handle
    Window* window = hwnd ? reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA)) : nullptr;
}
