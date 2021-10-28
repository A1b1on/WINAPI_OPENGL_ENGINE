#include "MainWindow.h"
#include "InputSystem.h"


alb::MainWindow::~MainWindow() {
    delete scene;
}

BOOL alb::MainWindow::Create_window() {
    //�������� ����� ����
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
    //������� ����� ���� �� ����������/���������� ����/�������/�����/������������������/���������
    DWORD dwStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;
    this->Create_abstract_window(0, dwStyle, NULL, NULL);
    //������������� � �������� ������� �������
    RECT sizes;
    GetWindowRect(this->Window_handle(), &sizes);
    this->Change_size(sizes.right, sizes.bottom);
    //������� ���� �����
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
    //������� ���� ������������
    this->explorer = new alb::ExplorerWindow(
        this->Application_handle(),
        this->Window_handle(),
        this->Width() / 5 * 4,
        this->Height() / 5,
        0,
        this->Height()/5 * 4);
    this->explorer->Change_window_class(
        WNDCLASS{
            0,
            alb::ExplorerProc,
            0, 0,
            this->Application_handle(),
            0, 0,
            (HBRUSH)CreateSolidBrush(RGB(134, 136, 142)),
            NULL,
            L"Explorer window"
        } );
    this->explorer->Create_Explorer();
    return 1;
}
BOOL alb::MainWindow::Start_main_loop() {
    BOOL done = FALSE;
    while (!done) {
        if (PeekMessage(&this->msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                done = TRUE;
            } else {
                TranslateMessage(&this->msg);
                DispatchMessage(&this->msg);
                DispatchMessage(&this->scene->msg);
                if (alb::InputSystem::resize_event) {
                    this->Change_size(alb::InputSystem::NewWidth(), alb::InputSystem::NewHeight());
                    //opengl
                    SetWindowPos(this->scene->Window_handle(), HWND_TOP, this->Height() / 5, 0, this->Width() / 5 * 3, this->Height() / 5 * 4, SWP_SHOWWINDOW);
                    //explorer
                    this->explorer->Change_size(this->Width() / 5 * 4, this->Height() / 5);
                    this->explorer->Change_coo(0, this->Height() / 5 * 4);
                    SetWindowPos(this->explorer->Window_handle(), HWND_TOP, 0, this->Height()/5*4, this->explorer->Width() , this->explorer->Height(), SWP_SHOWWINDOW);
                    
                    alb::InputSystem::resize_event = false;
                }

            }
        } else {
            if (alb::InputSystem::Is_active()) {
                if (alb::InputSystem::Key(VK_ESCAPE)) {
                    done = TRUE;
                } else {
                    alb::DrawScene();
                    SwapBuffers(this->scene->Device_context());
                }
            }
        }
    }
	/*while (GetMessage(&this->msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

       
	}*/
	return 1;
}

LRESULT CALLBACK alb::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_ACTIVATE:
            if (!HIWORD(wParam))
                alb::InputSystem::Activate();
            else
                alb::InputSystem::DisActivate();
            return 0;
        case WM_SIZE:
            alb::InputSystem::SetNewSize(LOWORD(lParam), HIWORD(lParam));
            return 0;
        case WM_KEYDOWN:
            alb::InputSystem::SetKey(wParam, TRUE);
            return 0;
        case WM_KEYUP:
            alb::InputSystem::SetKey(wParam, FALSE);
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
        case WM_SIZE:
            alb::ResizeGLScene(LOWORD(lParam), HIWORD(lParam));
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
LRESULT CALLBACK alb::ExplorerProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_SIZE:
        
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}