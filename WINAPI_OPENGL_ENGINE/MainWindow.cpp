#include "MainWindow.h"

std::uint8_t alb::MainWindow::Create_window() {
	this->Change_window_class(0, alb::WindowProc, L"Main window class");
	this->Create_abstract_window();

	return 1;
}
std::uint8_t alb::MainWindow::Start_main_loop() {
	while (GetMessage(&this->msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 1;
}

std::string alb::MainWindow::Title() { return this->title; }
std::uint16_t alb::MainWindow::Width() { return this->width; }
std::uint16_t alb::MainWindow::Height() { return this->height; }

LRESULT CALLBACK alb::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        EndPaint(hwnd, &ps);
    }
    return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}