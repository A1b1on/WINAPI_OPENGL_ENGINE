#include "OpenGL_window.h"
#include "Tech.h"

BOOL alb::OpenGL_window::Destroy_GL_window() {
    if (this->render_context) {
        if (!wglMakeCurrent(NULL, NULL)) {
            alb::Tech::Show_Err_Message("Shutdown Err", "Realease of DC & RC failed");
            alb::Tech::Show_last_Err();
        }
        if (!wglDeleteContext(this->render_context)) {
            alb::Tech::Show_Err_Message("Shutdown Err", "Realease of render context failed");
            alb::Tech::Show_last_Err();
        }
        this->render_context = NULL;
    }
    if (this->device_context && !ReleaseDC(this->Window_handle(), this->device_context)) {
        alb::Tech::Show_Err_Message("Shutdown Err", "Realease device context failed");
        alb::Tech::Show_last_Err();
    }
    this->Destroy_abstract_window();
    return 1;
}
BOOL alb::OpenGL_window::Create_GL_window() {
	
	GLuint		pixel_format;
	DWORD		dwExStyle = WS_EX_WINDOWEDGE;
	DWORD		dwStyle = WS_CHILDWINDOW;
	RECT		window_rect = { (LONG)0, (LONG)0, (LONG)this->Width(), (LONG)this->Height() };
	//add change wc
	this->window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	AdjustWindowRectEx(&window_rect, dwStyle, FALSE, dwExStyle);
	this->Create_abstract_window(dwExStyle,WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN |  dwStyle, NULL, NULL);
	
    static PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),    // Size Of This Pixel Format Descriptor
            1,                           // Version Number
            PFD_DRAW_TO_WINDOW |        // Format Must Support Window
            PFD_SUPPORT_OPENGL |       // Format Must Support OpenGL
            PFD_DOUBLEBUFFER,         // Must Support Double Buffering
            PFD_TYPE_RGBA,           // Request An RGBA Format
            32,                     // Select Our Color Depth
            0, 0, 0, 0, 0, 0,      // Color Bits Ignored
            0,                    // No Alpha Buffer
            0,                   // Shift Bit Ignored
            0,                  // No Accumulation Buffer
            0, 0, 0, 0,        // Accumulation Bits Ignored
            16,               // 16Bit Z-Buffer (Depth Buffer)
            0,               // No Stencil Buffer
            0,              // No Auxiliary Buffer
            PFD_MAIN_PLANE,// Main Drawing Layer
            0,            // Reserved
            0, 0, 0      // Layer Masks Ignored

    };
    if (!(this->device_context = GetDC(this->Window_handle()))) {
        this->Destroy_GL_window();
        alb::Tech::Show_Err_Message("Device Context Err", "Couldnt create a GL device context");
        return 0;
    }
    if (!(pixel_format = ChoosePixelFormat(this->device_context, &pfd))) {
        this->Destroy_GL_window();
        alb::Tech::Show_Err_Message("PFD Err", "Couldnt find a suitable pixelformat");
        return 0;
    }
    if (!SetPixelFormat(this->device_context, pixel_format, &pfd)) {
        this->Destroy_GL_window();
        alb::Tech::Show_Err_Message("PFD Err", "Couldnt activate the GL render context");
    }
    alb::ResizeGLScene(this->Width(), this->Height());
    if (!alb::Tech::InitGL()) {
        this->Destroy_GL_window();
        alb::Tech::Show_Err_Message("Init Err", "GL initialize error");
        return 0;
    }
	return 1;
}

void alb::ResizeGLScene(std::uint16_t w, std::uint16_t h) {
    if (!h)
        h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//BOOL alb::OpenGL_window::Change_window_class(const WNDCLASS& wnd)  {
//    this->window_class.style = wnd.style;
//    this->window_class.lpfnWndProc = wnd.lpfnWndProc;
//    this->window_class.cbClsExtra = wnd.cbClsExtra;
//    this->window_class.cbWndExtra = wnd.cbWndExtra;
//    this->window_class.hInstance = wnd.hInstance;
//    this->window_class.hIcon = wnd.hIcon;
//    this->window_class.hbrBackground = wnd.hbrBackground;
//    this->window_class.lpszMenuName = wnd.lpszMenuName;
//    this->window_class.lpszClassName = wnd.lpszClassName;
//    return 1;
//}