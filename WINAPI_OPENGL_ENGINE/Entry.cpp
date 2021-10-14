#include "MainWindow.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//”казание компил€тору что параметры не используютс€
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	alb::MainWindow* main_window = new alb::MainWindow(hInstance, "Engine", 640, 480);
	main_window->Create_window();
	main_window->Start_main_loop();
	return 0;
}