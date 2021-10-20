#pragma once
#include "AbstractWindow.h"

#include <GL/GL.h>
#include <GL/GLU.h>

namespace alb {
	class OpenGL_window : public AbstractWindow
	{
	public:
		OpenGL_window() {}
		OpenGL_window(HINSTANCE hInstance, HWND parent_window, std::uint16_t w, std::uint16_t h, std::uint16_t x, std::uint16_t y) :
			AbstractWindow(hInstance, parent_window, "opengl window", w, h) {
			this->Change_coo(x, y);
		}

		BOOL Create_GL_window();
		BOOL Destroy_GL_window();
		HDC	 Device_context();
		//BOOL Change_window_class(const WNDCLASS&) override;
	private:
		HGLRC	render_context = NULL;
		HDC		device_context = NULL;
	};
	void ResizeGLScene(std::uint16_t w, std::uint16_t h);
	GLint DrawScene();
}

