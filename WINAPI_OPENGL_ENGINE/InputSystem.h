#pragma once
namespace alb {
	class InputSystem
	{
		static bool keys[256];
		static bool active;
	public:
		static bool Is_active();
		static bool Activate();
		static bool DisActivate();

		static void  SetKey(size_t index, bool value);
		static bool Key(size_t index);
	};
}

