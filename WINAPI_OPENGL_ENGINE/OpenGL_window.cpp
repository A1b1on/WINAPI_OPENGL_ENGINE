#include "OpenGL_window.h"
#include "Tech.h"

HDC alb::OpenGL_window::Device_context() {
    return this->device_context;
}
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
	this->Create_abstract_window(dwExStyle, WS_CLIPSIBLINGS | WS_CLIPCHILDREN |  dwStyle, NULL, NULL);
	
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
        return FALSE;
    }
    if (!(pixel_format = ChoosePixelFormat(this->device_context, &pfd))) {
        this->Destroy_GL_window();
        alb::Tech::Show_Err_Message("PFD Err", "Couldnt find a suitable pixelformat");
        return FALSE;
    }
    if (!SetPixelFormat(this->device_context, pixel_format, &pfd)) {
        this->Destroy_GL_window();
        alb::Tech::Show_Err_Message("PFD Err", "Couldnt activate the GL render context");
        return FALSE;
    }
    if (!(this->render_context = wglCreateContext(this->device_context))) {
        this->Destroy_GL_window();
        alb::Tech::Show_Err_Message("HRC Err", "Couldnt create GL render context");
        return FALSE;
    }
    if (!wglMakeCurrent(this->device_context, this->render_context)) {
        this->Destroy_GL_window();
        alb::Tech::Show_Err_Message("HRC Err", "Couldnt activate the GL render context");
        return FALSE;
    }
    ShowWindow(this->Window_handle(), SW_SHOW);
    SetForegroundWindow(this->Window_handle());
    SetFocus(this->Window_handle());
    alb::ResizeGLScene(this->Width(), this->Height());
    if (!alb::Tech::InitGL()) {
        this->Destroy_GL_window();
        alb::Tech::Show_Err_Message("Init Err", "GL initialize error");
        return FALSE;
    }
	return TRUE;
}

GLint alb::DrawScene() {
    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0, 0.7f, 0);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-0.8f, -0.7f, 0);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.8f, -0.7f, 0);
    glEnd();
    glLoadIdentity();
    return 1;
}
void alb::ResizeGLScene(std::uint16_t w, std::uint16_t h) {
    if (!h)
        h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
