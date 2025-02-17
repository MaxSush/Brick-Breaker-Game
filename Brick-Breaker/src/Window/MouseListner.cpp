#include "MouseListner.h"
#include <iostream>
#include "stb_image.h"
#include "glfw_window.h"

MouseListner& MouseListner::get()
{
	static MouseListner instance;
	return instance;
}

MouseListner& MouseListner::mouse = MouseListner::get();

void MouseListner::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	mouse.lastMouseMoveTime = std::chrono::steady_clock::now();
	
	if (mouse.cursorHidden) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		mouse.cursorHidden = false;
	}

	mouse.xpos = xpos;
	mouse.ypos = ypos;
}

void MouseListner::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		mouse.mouse_button[button] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		mouse.mouse_button[button] = false;
		mouse.mouse_consumed[button] = false;
	}
}

void MouseListner::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	mouse.xoffset = xoffset;
	mouse.yoffset = yoffset;
	mouse.scrolled = true;
}

bool MouseListner::IsButtonClicked(int button)
{
	return mouse.mouse_button[button];
}

bool MouseListner::IsButtonClickedOnce(int button)
{
	if (mouse.mouse_button[button] && !mouse.mouse_consumed[button]) {
		mouse.mouse_consumed[button] = true;
		mouse.lastpos = { mouse.xpos,mouse.ypos };
		return true;
	}
	return false;
}

int MouseListner::WheelScrolledDirection()
{
	/*
	* -1 ==> scrolled downwards
	*  0 ==> not scrolled
	*  1 ==> scrolled upwards
	*/
	if (mouse.scrolled)
	{
		mouse.scrolled = false;
		return mouse.yoffset;
	}
	return 0;
}

bool MouseListner::IsWheelScrolled()
{
	return !(mouse.yoffset == 0);
}

void MouseListner::CreateCursor(const char* filename)
{
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filename, &width, &height,
		&nrChannels, 0);
	if (!data)
	{
		std::cout << "Failed to Load Png: " << filename << "\n";
	}
	GLFWimage image;
	image.width = width;
	image.height = height;
	image.pixels = data;
	cursor = glfwCreateCursor(&image, 0, 0);
	if (cursor == NULL)
	{
		std::cout << "Failed to create cursor\n";
	}
	stbi_image_free(data);
}

void MouseListner::CheckCursorInactivity(Breaker::WinProps* props)
{
	auto now = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - lastMouseMoveTime).count();

	if (elapsed >= 1 && !cursorHidden) { // 3 seconds of inactivity
		glfwSetInputMode(props->window , GLFW_CURSOR, GLFW_CURSOR_HIDDEN); // Hide cursor
		cursorHidden = true;
	}
}

glm::vec2 MouseListner::GetLastClickedMousePos()
{
	return mouse.lastpos;
}

bool MouseListner::IsHoverOverRect(Rect rect)
{
	return rect.PointInRect({mouse.xpos, mouse.ypos});
}
