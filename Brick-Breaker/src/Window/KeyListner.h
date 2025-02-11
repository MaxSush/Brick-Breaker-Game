#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>

class KeyListner
{
public:
	static KeyListner& get();

	KeyListner(const KeyListner&) = delete;
	KeyListner& operator=(const KeyListner&) = delete;

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	static bool IsKeyPressed(int keycode);

	static bool IsKeyPressedOnce(int keycode);

private:
	KeyListner() { }

	std::unordered_map<int, bool> Keys;
	std::unordered_map<int, bool> keyConsumed;
};