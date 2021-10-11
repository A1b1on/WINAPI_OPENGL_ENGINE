#include "MainWindow.h"

std::uint8_t alb::MainWindow::Create_window() {
	this->Change_window_class(0, alb::WindowProc, L"Main window class");
    //Создаем стиль окна из Перекрытия/системного меню/надписи/рамки/свернутьразвернуть/расширить
    DWORD dwStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;
    this->Create_abstract_window(0, dwStyle, CW_DEFAULT, CW_DEFAULT, NULL, NULL);
    //Прямоугольник с которого замерем размеры
    RECT sizes;
    GetWindowRect(this->window_handle, &sizes);
    this->width = sizes.right;
    this->height = sizes.bottom;

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
            //Красим фон
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH)CreateSolidBrush(RGB(114, 116, 122)));
            EndPaint(hwnd, &ps);
        }
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}