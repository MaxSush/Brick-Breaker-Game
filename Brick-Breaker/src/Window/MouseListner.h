#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include "Rect.h"
#include <unordered_map>

namespace Breaker
{
	struct WinProps;
};

class MouseListner
{
public:
	static MouseListner& get();

	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


	MouseListner(const MouseListner&) = delete;
	MouseListner& operator=(const MouseListner&) = delete;

	static bool IsButtonClicked(int button);
	static bool IsButtonClickedOnce(int button);
	static int WheelScrolledDirection();
	static bool IsWheelScrolled();
	static glm::vec2 GetLastClickedMousePos();
	static bool IsHoverOverRect(Rect rect);

	void CreateCursor(const char* filename);
	void CheckCursorInactivity(struct Breaker::WinProps* props);

	GLFWcursor* cursor;
private:
	MouseListner() {}
	static MouseListner& mouse;

	std::chrono::steady_clock::time_point lastMouseMoveTime;
	bool cursorHidden = false;
	bool scrolled = false;

	double xpos, ypos;
	double xoffset, yoffset;
	glm::vec2 lastpos{};
	std::unordered_map<int, bool> mouse_button;
	std::unordered_map<int, bool> mouse_consumed;
};