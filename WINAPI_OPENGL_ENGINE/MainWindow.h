#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include "AbstractWindow.h"
#include "OpenGL_window.h"
#include "ExplorerWindow.h"

#include <Windows.h>
#include <string>
#include <cstdint>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <gl/glut.h>

namespace alb {
	class MainWindow : public AbstractWindow
	{
	public:
		MainWindow() { }
		MainWindow(HINSTANCE hInstance, std::string title, std::uint16_t w, std::uint16_t h):AbstractWindow(hInstance, NULL, title, w, h) {}
		~MainWindow();
		BOOL Create_window();
		BOOL Start_main_loop();

	private:
		OpenGL_window* scene = nullptr;
		ExplorerWindow* explorer = nullptr;
	};

	LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
	LRESULT CALLBACK OpenGLWindowProc(HWND, UINT, WPARAM, LPARAM);
	LRESULT CALLBACK ExplorerProc(HWND, UINT, WPARAM, LPARAM);
}

