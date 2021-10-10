#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include "AbstractWindow.h"

#include <Windows.h>
#include <string>
#include <cstdint>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <gl/glut.h>

namespace alb {
	class MainWindow : private AbstractWindow
	{
	public:
		MainWindow() {}
		MainWindow(HINSTANCE hInstance, std::string title, std::uint16_t w, std::uint16_t h):AbstractWindow(hInstance, NULL, title, w, h) {}
		
		std::uint8_t Create_window();
		std::uint8_t Start_main_loop();


		std::string Title();
		std::uint16_t Width();
		std::uint16_t Height();
	private:
	};

	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}

