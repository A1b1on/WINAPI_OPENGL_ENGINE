#include "InputSystem.h"

UINT alb::InputSystem::new_height = 0;
UINT alb::InputSystem::new_width = 0;

bool alb::InputSystem::resize_event = false;
bool alb::InputSystem::active = true;
bool alb::InputSystem::keys[256];


bool alb::InputSystem::Is_active() {
	return alb::InputSystem::active;
}

bool alb::InputSystem::Activate() {
	return alb::InputSystem::active = true;		
}
bool alb::InputSystem::DisActivate() {
	return alb::InputSystem::active = false;
}

void alb::InputSystem::SetKey(size_t index, bool value) {
	alb::InputSystem::keys[index] = value;
}
bool alb::InputSystem::Key(size_t index) {
	return alb::InputSystem::keys[index];
}

void alb::InputSystem::SetNewSize(UINT w, UINT h) {
	if (w && h) {
		alb::InputSystem::new_width = w;
		alb::InputSystem::new_height = h;
	}
	alb::InputSystem::resize_event = true;
}

UINT alb::InputSystem::NewWidth() {
	return alb::InputSystem::new_width;
}
UINT alb::InputSystem::NewHeight() {
	return alb::InputSystem::new_height;
}