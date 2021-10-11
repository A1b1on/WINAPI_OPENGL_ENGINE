#pragma once
#include "AbstractWindow.h"

#include <GL/GL.h>
#include <GL/GLU.h>

namespace alb {
	class OpenGL_window : private AbstractWindow
	{
	public:
		OpenGL_window() {}
		OpenGL_window(HINSTANCE hInstance, HWND parent_window, std::uint16_t w, std::uint16_t h, std::uint16_t x, std::uint16_t y) :
			AbstractWindow(hInstance, parent_window, "opengl window", w, h) {
			this->pos_x = x; this->pos_y = y;
		}

		std::uint8_t Create_GL_window();
		std::uint8_t Destroy_GL_window();
	private:
		HGLRC	render_context = NULL;
		HDC		device_context = NULL;
	};
	void ResizeGLScene(std::uint16_t w, std::uint16_t h);
}

