#pragma once

#include <Windows.h>
#include <cstdint>
#include <string>

namespace alb {
	using std::string;
	class AbstractWindow
	{
	public:
		AbstractWindow(){}
		AbstractWindow(HINSTANCE hInstance, HWND parent_window, std::string title, std::uint16_t w, std::uint16_t h) :
			app_handle(hInstance), parent_window(parent_window), window_title(title), width(w), height(h) { }

		UINT Width();
		UINT Height();
		UINT X_coo();
		UINT Y_coo();
		BOOL Change_size(UINT w, UINT h);
		BOOL Change_coo(UINT x, UINT y);
		
		HWND Parent_handle();
		HWND Window_handle();
		HINSTANCE Application_handle();

		virtual BOOL Change_window_class(const WNDCLASS&);
	    BOOL Register_window_class();
		
		BOOL Destroy_abstract_window();
		BOOL Create_abstract_window(DWORD dwExStyle = 0, DWORD dwStyle = 0, HMENU hMenu = NULL, LPVOID lpParam = NULL);

		MSG			msg = { };
		WNDCLASS	window_class = { };
		
		
	private:
		string window_title = "Abstract title";
		LPCWSTR class_name = L"Abstract class";
		UINT width = 1;
		UINT height = 1;
		UINT pos_x = CW_DEFAULT;
		UINT pos_y = CW_DEFAULT;

		HINSTANCE	app_handle = GetModuleHandle(NULL);
		HWND		window_handle = NULL;
		HWND		parent_window = NULL;

		LRESULT(*WndProc)(HWND, UINT, WPARAM, LPARAM);
	};
}

