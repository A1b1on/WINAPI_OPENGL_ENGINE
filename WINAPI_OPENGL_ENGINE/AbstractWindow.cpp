#include "AbstractWindow.h"
#include "Tech.h"

std::uint8_t alb::AbstractWindow::Change_window_class(const WNDCLASS& wnd) {
	this->window_class.style = wnd.style;
	this->window_class.lpfnWndProc = wnd.lpfnWndProc;
	this->window_class.cbClsExtra = wnd.cbClsExtra;
	this->window_class.cbWndExtra = wnd.cbWndExtra;
	this->window_class.hInstance = wnd.hInstance;
	this->window_class.hIcon = wnd.hIcon;
	this->window_class.hbrBackground = wnd.hbrBackground;
	this->window_class.lpszMenuName = wnd.lpszMenuName;
	this->window_class.lpszClassName = wnd.lpszClassName;
	return 1;
}
std::uint8_t alb::AbstractWindow::Change_window_class(UINT style, WNDPROC proc, LPCTSTR class_name) {
	this->window_class.lpszClassName = class_name;
	this->window_class.style = style;
	this->window_class.lpfnWndProc = proc;
	return 1;
}
std::uint8_t alb::AbstractWindow::Register_window_class() {
	if (!RegisterClass(&this->window_class)) {
		alb::Tech::Show_Err_Message("Window class ERR", "Window class could register");
		alb::Tech::Show_last_Err();
		return 0;
	}
	return 1;
}

std::uint8_t alb::AbstractWindow::Destroy_abstract_window() {
	if (this->window_handle && !DestroyWindow(this->window_handle)) {
		alb::Tech::Show_Err_Message("Shutdown ERR", "Release of HWND failed");
		this->window_handle = NULL;
	}
	if (!UnregisterClass(this->window_class.lpszClassName, this->app_handle)) {
		alb::Tech::Show_Err_Message("Shutdown ERR", "Couldnt unregister class");
	}
	return 1;
}
std::uint8_t alb::AbstractWindow::Create_abstract_window(DWORD dwExStyle, DWORD dwStyle, std::uint16_t x, std::uint16_t y, HMENU hMenu, LPVOID lpParam) {
	if (!this->Register_window_class()) {
		alb::Tech::Show_Err_Message("Register window err", "Couldntt register window class");
		alb::Tech::Show_last_Err();
		return 0;
	}
	this->window_handle = CreateWindowEx(
		dwExStyle,												  // Optional window styles.
		this->window_class.lpszClassName,                // Window class
		alb::Tech::ConvertChar(this->title.c_str()),    // Window text
		dwStyle,											   // Window style
		// Size and position
		x, y,
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

