#include "KeyListner.h"

KeyListner& KeyListner::get()
{
	static KeyListner instance;
	return instance;
}

void KeyListner::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		get().Keys[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		get().Keys[key] = false;
		get().keyConsumed[key] = false;
	}
}

bool KeyListner::IsKeyPressed(int keycode)
{
	return get().Keys[keycode];
}

bool KeyListner::IsKeyPressedOnce(int keycode) {
	if (get().Keys[keycode] && !get().keyConsumed[keycode]) {
		get().keyConsumed[keycode] = true;
		return true;
	}
	return false;
}