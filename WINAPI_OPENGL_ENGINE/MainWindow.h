#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>
#include <string>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <gl/glut.h>

namespace alb {
	class MainWindow
	{
	public:
		MainWindow(HINSTANCE);

		size_t Width();
		size_t Height();
		const char* Title();

		int Change_window_size(size_t w, size_t h);
		int Set_new_window_title(const char* new_title);

		int Create_window();
		int Destroy_window();
		int Start_main_loop();

		static void Resize_GL_scene(size_t w, size_t h);
	private:
		size_t width = 640;
		size_t height = 480;
		std::string title = "Main Window";

		HINSTANCE app_handle; //module descriptor
		WNDCLASS window_class = { };
		HWND window_handle;
		MSG msg = { };
		HGLRC render_context = NULL;
		HDC device_context = NULL;

		const wchar_t* CLASS_NAME = L"Main Window Class";
		
		int Register_Window_CLass();

		
		void Draw_GL_scene();
	};

	LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
}

