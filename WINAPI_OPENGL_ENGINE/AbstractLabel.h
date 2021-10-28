#pragma once
#include "AbstractWindow.h"

namespace alb {
	class AbstractLabel : public AbstractWindow
	{
		std::string text = NULL;
	public:
		AbstractLabel() { }
		AbstractLabel(HINSTANCE hInstance, HWND parent_window, std::uint16_t w, std::uint16_t h, std::uint16_t x, std::uint16_t y, std::string text) :
			AbstractWindow(hInstance, parent_window, "explorer window", w, h), text(text) {
			this->Change_coo(x, y);
		}

		BOOL CreateLabel();
		std::string Text();
	};

	LRESULT CALLBACK NothingLabelProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}

