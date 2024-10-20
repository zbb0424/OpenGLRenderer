#pragma once

#include <GLFW/glfw3.h>
#include "Camera.h"

class InputHandler
{
private:
	float lastX;
	float lastY;
	bool firstMouse;
	Camera* m_Camera;

	static InputHandler* s_Instance;

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
public:
	InputHandler(float lastx, float lasty, Camera* camera = nullptr);
	~InputHandler();

	static void GLFWFramebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void GLFWMouseCallback(GLFWwindow* window, double xpos, double ypos);
	static void GLFWScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void processInput(GLFWwindow* window, float deltaTime);
};
