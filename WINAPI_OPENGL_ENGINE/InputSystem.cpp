#include "InputSystem.h"

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