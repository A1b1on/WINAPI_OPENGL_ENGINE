#include "MainWindow.h"
#include "InputSystem.h"

alb::MainWindow::~MainWindow() {
    delete scene;
}

BOOL alb::MainWindow::Create_window() {
    //Изменяем класс окна
    this->Change_window_class(
        WNDCLASS{ 
            0,
            alb::WindowProc,
            0, 0,
            this->Application_handle(),
            LoadIcon(NULL,IDI_APPLICATION), LoadCursor(NULL, IDC_ARROW),
            (HBRUSH)CreateSolidBrush(RGB(114, 116, 122)),
            L"mainmenu",
            L"Main window" });
    //Создаем стиль окна из Перекрытия/системного меню/надписи/рамки/свернутьразвернуть/расширить
    DWORD dwStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;
    this->Create_abstract_window(0, dwStyle, NULL, NULL);
    //Прямоугольник с которого замерем размеры
    RECT sizes;
    GetWindowRect(this->Window_handle(), &sizes);
    this->Change_size(sizes.right, sizes.bottom);
    //Создаем окно сцены
    this->scene = new alb::OpenGL_window(
        this->Application_handle(),
        this->Window_handle(),
        this->Width() / 5 * 3,
        this->Height() / 5 * 4,
        this->Width() / 5, 
        0);
    this->scene->Change_window_class(
        WNDCLASS{ 
            0,
            alb::OpenGLWindowProc,
            0, 0,
            this->Application_handle(),
            0, 0,
            (HBRUSH)CreateSolidBrush(RGB(184, 156, 172)),
            NULL,
            L"Opengl window"});
    this->scene->Create_GL_window();
    return 1;
}
BOOL alb::MainWindow::Start_main_loop() {
	while (GetMessage(&this->msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

        if (alb::InputSystem::resize_event) {
            this->Change_size(alb::InputSystem::NewWidth(), alb::InputSystem::NewHeight());
            SetWindowPos(this->scene->Window_handle(), HWND_TOP, this->Height() / 5, 0, this->Width() / 5 * 3, this->Height() / 5 * 4, SWP_SHOWWINDOW);
            alb::InputSystem::resize_event = false;
        }
	}
	return 1;
}

LRESULT CALLBACK alb::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_SIZE:
            alb::InputSystem::SetNewSize(LOWORD(lParam), HIWORD(lParam));
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
LRESULT CALLBACK alb::OpenGLWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
        
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}