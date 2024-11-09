#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class KeyListner
{
public:
	static KeyListner& get();

	KeyListner(const KeyListner&) = delete;
	KeyListner& operator=(const KeyListner&) = delete;

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	static bool isKeyPressed(int keycode);
	static bool isKeyReleased(int keycode);

private:
	KeyListner() { }

	bool Keys[350] = { false };
};