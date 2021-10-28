#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>
#include <string>

namespace alb {
	class Tech {
		
		static size_t Const_char_size(const char* str);
	public:
		static int Show_Err_Message(const char* title, const char* message);
		static int Show_Err_Message(LPCWSTR title, LPCWSTR message);
		static int Show_last_Err();

		static LPCWSTR ConvertChar(const char* str);
		static std::string Convert_WSTR_to_STR(const std::wstring& str);
		static std::wstring Get_current_directory();

		static int InitGL();
	};
}

