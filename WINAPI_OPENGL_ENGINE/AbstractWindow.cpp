#include "AbstractWindow.h"
#include "Tech.h"

BOOL alb::AbstractWindow::Change_window_class(const WNDCLASS& wnd) {
	this->window_class = wnd;
	this->WndProc = wnd.lpfnWndProc;
	this->class_name = wnd.lpszClassName;
	return 1;
}
BOOL alb::AbstractWindow::Register_window_class() {
	if (!RegisterClass(&this->window_class)) {
		alb::Tech::Show_Err_Message("Window class ERR", "Window class could register");
		alb::Tech::Show_last_Err();
		return 0;
	}
	return 1;
}

BOOL alb::AbstractWindow::Destroy_abstract_window() {
	if (this->window_handle && !DestroyWindow(this->window_handle)) {
		alb::Tech::Show_Err_Message("Shutdown ERR", "Release of HWND failed");
		this->window_handle = NULL;
	}
	if (!UnregisterClass(this->window_class.lpszClassName, this->app_handle)) {
		alb::Tech::Show_Err_Message("Shutdown ERR", "Couldnt unregister class");
	}
	return 1;
}
BOOL alb::AbstractWindow::Create_abstract_window(DWORD dwExStyle, DWORD dwStyle, HMENU hMenu, LPVOID lpParam) {
	if (!this->Register_window_class()) {
		alb::Tech::Show_Err_Message("Register window err", "Couldntt register window class");
		alb::Tech::Show_last_Err();
		return 0;
	}
	this->window_handle = CreateWindowEx(
		dwExStyle,												  // Optional window styles.
		this->window_class.lpszClassName,                // Window class
		alb::Tech::ConvertChar(this->window_title.c_str()),    // Window text
		dwStyle,											   // Window style
		// Size and position
		this->pos_x, this->pos_y,
		this->width, this->height,
		this->parent_window, // Parent window    
		hMenu,				// Menu
		this->app_handle,  // Instance handle
		lpParam			  // Additional application data
	);
	if (this->window_handle == NULL) {
		this->Destroy_abstract_window();
		alb::Tech::Show_Err_Message("Window create ERR", "MainWindow couldnt create");
		alb::Tech::Show_last_Err();
		return 0;
	}
	ShowWindow(this->window_handle, SW_SHOW);
	return 1;
}

UINT alb::AbstractWindow::Width() { return this->width; }
UINT alb::AbstractWindow::Height() { return this->height; }
BOOL alb::AbstractWindow::Change_size(UINT w, UINT h) {
	if (w && h) {
		this->width = w;
		this->height = h;
		return TRUE;
	}
	return FALSE;
}
UINT alb::AbstractWindow::X_coo() { return pos_x; }
UINT alb::AbstractWindow::Y_coo() { return pos_y; }
BOOL alb::AbstractWindow::Change_coo(UINT x, UINT y) {
	this->pos_x = x;
	this->pos_y = y;
	return TRUE;
}
HWND alb::AbstractWindow::Parent_handle() { return this->parent_window; }
HWND alb::AbstractWindow::Window_handle() { return this->window_handle; }
HINSTANCE alb::AbstractWindow::Application_handle() { return this->app_handle; }