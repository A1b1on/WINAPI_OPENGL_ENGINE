#include "AbstractLabel.h"
#include "Tech.h"

BOOL alb::AbstractLabel::CreateLabel() {
	DWORD dwExStyle = WS_EX_WINDOWEDGE;
	DWORD dwStyle =  WS_CHILDWINDOW;

	this->Create_abstract_window(dwExStyle, dwStyle, NULL, NULL);
	return TRUE;
}

std::string alb::AbstractLabel::Text() { return this->text; }

LRESULT CALLBACK alb::NothingLabelProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
