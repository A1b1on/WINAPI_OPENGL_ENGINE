#pragma once

#include <Windows.h>
#include <cstdint>
#include <string>

namespace alb {
	class AbstractWindow
	{
	public:
		AbstractWindow(){}
		AbstractWindow(HINSTANCE hInstance, HWND parent_window, std::string title, std::uint16_t w, std::uint16_t h) :
			app_handle(hInstance), parent_window(parent_window), title(title), width(w), height(h) { }

		std::uint8_t Change_window_class(const WNDCLASS&);
		std::uint8_t Change_window_class(UINT style, WNDPROC, LPCTSTR class_name);
		std::uint8_t Register_window_class();
		
		std::uint8_t Destroy_abstract_window();
		std::uint8_t Create_abstract_window(DWORD dwExStyle = 0, DWORD dwStyle = 0, std::uint16_t x = CW_USEDEFAULT, std::uint16_t y = CW_USEDEFAULT, HMENU hMenu = NULL, LPVOID lpParam = NULL);

		MSG			msg = { };
		WNDCLASS	window_class = { };
		HINSTANCE	app_handle = GetModuleHandle(NULL);
		HWND		window_handle = NULL;
		HWND		parent_window = NULL;

		std::string title = "Abstract window";
		std::uint16_t width = 1;
		std::uint16_t height = 1;
		std::uint16_t pos_x = CW_DEFAULT;
		std::uint16_t pos_y = CW_DEFAULT;
	};
}

