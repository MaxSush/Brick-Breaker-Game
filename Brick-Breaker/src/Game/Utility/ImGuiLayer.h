#pragma once

#include "imgui.h"
#include "GLFW/glfw3.h"

class ImGuiLayer
{
public:
	static void Init(GLFWwindow* window);
	static void BeginFrame();
	static void EndFrame();
	static void Shutdown();
};