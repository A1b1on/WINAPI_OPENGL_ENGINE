#include "ExplorerWindow.h"
#include "Tech.h"

alb::ExplorerWindow::ExplorerWindow()  : current_directory(alb::Tech::Convert_WSTR_to_STR(alb::Tech::Get_current_directory())){

}
alb::ExplorerWindow::ExplorerWindow(HINSTANCE hInstance, HWND parent_window, std::uint16_t w, std::uint16_t h, std::uint16_t x, std::uint16_t y) :
	AbstractWindow(hInstance, parent_window, "explorer window", w, h), current_directory(Tech::Convert_WSTR_to_STR(Tech::Get_current_directory())) {
	this->Change_coo(x, y);
	this->Change_size(w, h);
}
BOOL alb::ExplorerWindow::Create_Explorer() {
	DWORD		dwExStyle = WS_EX_WINDOWEDGE;
	DWORD		dwStyle =   WS_CHILDWINDOW;

	this->Create_abstract_window(dwExStyle,  dwStyle, NULL, NULL);

	this->directory_label = new AbstractLabel(this->Application_handle(), this->Window_handle(), this->Width(), this->Height() / 10, 0, 0, this->current_directory);
	this->directory_label->Change_window_class(
		WNDCLASS{
			0,
			alb::NothingLabelProc,
			0, 0,
			this->Application_handle(),
			NULL, NULL,
			(HBRUSH)CreateSolidBrush(RGB(84, 84, 84)),
			NULL,
			L"STATIC"
		}
	);
	this->directory_label->CreateLabel();
	return TRUE;
}
BOOL alb::ExplorerWindow::Change_size(UINT w, UINT h) {
	AbstractWindow::Change_size(w, h);
	if (this->directory_label) {
		this->directory_label->Change_size(this->Width(), this->Height() / 10);
		SetWindowPos(this->directory_label->Window_handle(), HWND_TOP, 0, 0, this->directory_label->Width(), this->directory_label->Height(), SWP_SHOWWINDOW);
	}
	return TRUE;
}

