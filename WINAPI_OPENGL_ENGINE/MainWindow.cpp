#include "MainWindow.h"
#include "Tech.h"
#include "InputSystem.h"

size_t alb::MainWindow::Width() { return this->width; }
size_t alb::MainWindow::Height() { return this->height; }
const char* alb::MainWindow::Title() { return this->title.c_str(); }

alb::MainWindow::MainWindow(HINSTANCE hInstance) : app_handle(hInstance) {
	
}

int alb::MainWindow::Register_Window_CLass() {
	this->window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	this->window_class.lpszClassName = this->CLASS_NAME;
	this->window_class.hInstance = this->app_handle;
	this->window_class.lpfnWndProc = alb::WindowProc;
	if (!RegisterClass(&this->window_class)) {
		alb::Tech::Show_Err_Message("Window class ERR", "Window class could register");
		alb::Tech::Show_last_Err();
		return 0;
	}
	return 1;
}
int alb::MainWindow::Create_window(){
	GLuint PixelFormat;
	DWORD dwExStyle;
	DWORD dwStyle;
	RECT WindowRect;
	WindowRect.left = 0;
	WindowRect.right = this->width;
	WindowRect.top = 0;
	WindowRect.bottom = this->height;
	if (this->Register_Window_CLass()) {
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPED;

		AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);
		this->window_handle = CreateWindowEx(
			dwExStyle,                              // Optional window styles.
			CLASS_NAME,                     // Window class
			alb::Tech::ConvertChar(title.c_str()),    // Window text
			dwStyle,            // Window style

			// Size and position
			CW_USEDEFAULT, CW_USEDEFAULT,
			this->width, this->height,

			NULL,				 // Parent window    
			NULL,				// Menu
			this->app_handle,  // Instance handle
			NULL			  // Additional application data
		);
		if (this->window_handle == NULL) {
			this->Destroy_window();
			alb::Tech::Show_Err_Message("Window create ERR", "MainWindow couldnt create");
			alb::Tech::Show_last_Err();
			return 0;
		}
		static PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),     // Size Of This Pixel Format Descriptor
			1,                                // Version Number
			PFD_DRAW_TO_WINDOW |             // Format Must Support Window
			PFD_SUPPORT_OPENGL |            // Format Must Support OpenGL
			PFD_DOUBLEBUFFER,              // Must Support Double Buffering
			PFD_TYPE_RGBA,                // Request An RGBA Format
			24,                          // Select Our Color Depth
			0, 0, 0, 0, 0, 0,           // Color Bits Ignored
			0,                         // No Alpha Buffer
			0,                        // Shift Bit Ignored
			0,                       // No Accumulation Buffer
			0, 0, 0, 0,             // Accumulation Bits Ignored
			32,                    // 16Bit Z-Buffer (Depth Buffer)
			0,                    // No Stencil Buffer
			0,                   // No Auxiliary Buffer
			PFD_MAIN_PLANE,     // Main Drawing Layer
			0,                 // Reserved
			0, 0, 0           // Layer Masks Ignored
		};
		if (!(this->device_context = GetDC(this->window_handle))) {
			this->Destroy_window();
			alb::Tech::Show_Err_Message("Device Context ERR", "Cant create a GL Device Context");
			alb::Tech::Show_last_Err();
			return 0;
		}
		if (!(PixelFormat = ChoosePixelFormat(this->device_context, &pfd))) {
			this->Destroy_window();
			alb::Tech::Show_Err_Message("PixelFormat ERR", "Cant find a suitable PixelFormat");
			alb::Tech::Show_last_Err();
			return 0;
		}
		if (!SetPixelFormat(this->device_context, PixelFormat, &pfd)) {
			this->Destroy_window();
			alb::Tech::Show_Err_Message("PixelFormat ERR", "Cant set pixelformat");
			alb::Tech::Show_last_Err();
			return 0;
		}
		this->render_context = wglCreateContext(this->device_context);
		if (!wglMakeCurrent(this->device_context, this->render_context)) {
			this->Destroy_window();
			alb::Tech::Show_Err_Message("GL Render context ERR", "Cant activate the gl rendering context");
			alb::Tech::Show_last_Err();
			return 0;
		}
		ShowWindow(this->window_handle, SW_SHOW);
		SetForegroundWindow(this->window_handle);
		SetFocus(this->window_handle);
		alb::MainWindow::Resize_GL_scene(this->width, this->height);
		if (!alb::Tech::InitGL()) {
			this->Destroy_window();
			alb::Tech::Show_Err_Message("GL init ERR", "GL initialization failed");
			return 0;
		}
		return 1;
	}
	return 0;
}
int alb::MainWindow::Destroy_window() {
	if (this->render_context) {
		if (!wglMakeCurrent(NULL, NULL)) {
			alb::Tech::Show_Err_Message("Shutdown ERR", "Release of DC & RC failed");
		}
		if (!wglDeleteContext(this->render_context)) {
			alb::Tech::Show_Err_Message("Shutdown ERR", "Release RC failed");
		}
		this->render_context = NULL;
	}
	if (this->device_context && !ReleaseDC(this->window_handle, this->device_context)) {
		alb::Tech::Show_Err_Message("Shutdown ERR", "Release DC failed");
		this->device_context = NULL;
	}
	if (this->window_handle && !DestroyWindow(this->window_handle)) {
		alb::Tech::Show_Err_Message("Shutdown ERR", "Release of HWND failed");
		this->window_handle = NULL;
	}
	if (!UnregisterClass(this->CLASS_NAME, this->app_handle)) {
		alb::Tech::Show_Err_Message("Shutdown ERR", "Couldnt unregister class");
	}
	return 1;
}
int alb::MainWindow::Start_main_loop() {
	bool done = false;
	while (!done) {
		if (PeekMessage(&this->msg, NULL, 0, 0, PM_REMOVE))           // Is There A Message Waiting?
		{
			if (this->msg.message == WM_QUIT)               // Have We Received A Quit Message?
			{
				done = TRUE;                  // If So done=TRUE
			}
			else                            // If Not, Deal With Window Messages
			{
				TranslateMessage(&this->msg);             // Translate The Message
				DispatchMessage(&this->msg);              // Dispatch The Message
			}
		}
		else                                // If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if (alb::InputSystem::Is_active())                     // Program Active?
			{
				if (alb::InputSystem::Key(VK_ESCAPE))                // Was ESC Pressed?
					done = TRUE;              // ESC Signalled A Quit
				else                        // Not Time To Quit, Update Screen
				{
					this->Draw_GL_scene();              // Draw The Scene
					SwapBuffers(this->device_context);           // Swap Buffers (Double Buffering)
				}
			}
		}

	}
	
	return 1;
}

void alb::MainWindow::Resize_GL_scene(size_t w, size_t h) {
	if (!h)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void alb::MainWindow::Draw_GL_scene() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(-0.5f, -0.5f);
	glColor3f(0, 1, 0);
	glVertex2f(0.0f, 0.5f);
	glColor3f(0, 0, 1);
	glVertex2f(0.5f, -0.5f);
	glEnd();

}

LRESULT CALLBACK alb::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_ACTIVATE:                          // Watch For Window Activate Message
		{
			if (!HIWORD(wParam))                  // Check Minimization State
				alb::InputSystem::Activate();    // Program Is Active
			else
				alb::InputSystem::DisActivate();// Program Is No Longer Active
		
			return 0;                          // Return To The Message Loop
		}
		case WM_SYSCOMMAND:            // Intercept System Commands
		{
			switch (wParam)           // Check System Calls
			{
				case SC_SCREENSAVE:     // Screensaver Trying To Start?
				case SC_MONITORPOWER:  // Monitor Trying To Enter Powersave?
				return 0;         // Prevent From Happening
			}
			break;               // Exit
		}
		case WM_CLOSE:                          // Did We Receive A Close Message?
		{
			PostQuitMessage(0);                 // Send A Quit Message
			return 0;                       // Jump Back
		}
		case WM_KEYDOWN:                        // Is A Key Being Held Down?
		{
			alb::InputSystem::SetKey(wParam, true);                    // If So, Mark It As TRUE
			return 0;                       // Jump Back
		}
		case WM_KEYUP:                          // Has A Key Been Released?
		{
			alb::InputSystem::SetKey(wParam, false);                    // If So, Mark It As TRUE// If So, Mark It As FALSE
			return 0;                       // Jump Back
		}
		case WM_SIZE:                           // Resize The OpenGL Window
		{
			alb::MainWindow::Resize_GL_scene( LOWORD(lParam), HIWORD(lParam) );       // LoWord=Width, HiWord=Height
			return 0;                       // Jump Back
		}

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}