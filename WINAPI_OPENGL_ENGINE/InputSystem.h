#pragma once
#include <Windows.h>
namespace alb {
	class InputSystem
	{
		static bool keys[256];
		static bool active;
		static UINT new_width;
		static UINT new_height;
	public:
		static bool Is_active();
		static bool Activate();
		static bool DisActivate();

		static void SetNewSize(UINT w, UINT h);
		static UINT NewWidth();
		static UINT NewHeight();

		static void  SetKey(size_t index, bool value);
		static bool Key(size_t index);
		static bool resize_event;
	};
}

