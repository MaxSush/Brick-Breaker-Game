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
	}

}

bool KeyListner::isKeyPressed(int keycode) 
{
	return get().Keys[keycode];
}

bool KeyListner::isKeyReleased(int keycode)
{
	return get().Keys[keycode];
}
