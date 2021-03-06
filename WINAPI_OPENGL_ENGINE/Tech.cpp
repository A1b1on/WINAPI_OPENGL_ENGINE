#include "Tech.h"
#include <sstream>
#include <GL/GL.h>
#include <codecvt>

#define MAX_PATH 100


int alb::Tech::Show_Err_Message(const char* title, const char* message) {
	return MessageBox(NULL, alb::Tech::ConvertChar(message), alb::Tech::ConvertChar(title), MB_OK | MB_ICONERROR);
}
int alb::Tech::Show_Err_Message(LPCWSTR title, LPCWSTR message) {
	return MessageBox(NULL, message, title, MB_OK | MB_ICONERROR);
}
int alb::Tech::Show_last_Err() {
	std::string str = "Last ERROR code: ";
	std::stringstream strs;
	strs << GetLastError();
	str += strs.str();
	return MessageBox(NULL, alb::Tech::ConvertChar(str.c_str()) , L"Last Err", MB_OK | MB_ICONERROR);
}

LPCWSTR alb::Tech::ConvertChar(const char* str) {
	const WCHAR* pwcsName; //LPCWSTR

	// required size
	int size = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	// allocate it
	pwcsName = new WCHAR[size];
	MultiByteToWideChar(CP_ACP, 0, str, -1, (LPWSTR)pwcsName, size);
	// use it....
	return pwcsName;
}

size_t alb::Tech::Const_char_size(const char* str) {
	size_t size = 0;
	while (str[size] != '\0')
		size++;
	return size;
}

int alb::Tech::InitGL() {
	glShadeModel(GL_SMOOTH);
	glClearColor(0.4f, 0.1f, 1.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	return 1;
}

std::wstring alb::Tech::Get_current_directory() {
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	return std::wstring(buffer).substr(0, pos);
}

std::string alb::Tech::Convert_WSTR_to_STR(const std::wstring& str) {
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(str);
}