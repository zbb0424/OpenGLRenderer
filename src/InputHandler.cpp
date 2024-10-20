#include "InputHandler.h"

InputHandler* InputHandler::s_Instance = nullptr;

InputHandler::InputHandler(float lastx, float lasty, Camera* camera)
	: lastX(lastx), lastY(lasty), firstMouse(true), m_Camera(camera)
{
	s_Instance = this;
}

InputHandler::~InputHandler()
{
	s_Instance = nullptr;
}

void InputHandler::GLFWFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	if (s_Instance)
	{
		s_Instance->framebuffer_size_callback(window, width, height);
	}
}

void InputHandler::GLFWMouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (s_Instance)
	{
		s_Instance->mouse_callback(window, xpos, ypos);
	}
}

void InputHandler::GLFWScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (s_Instance)
	{
		s_Instance->scroll_callback(window, xoffset, yoffset);
	}
}

void InputHandler::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void InputHandler::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	float x = static_cast<float>(xpos);
	float y = static_cast<float>(ypos);

	if (firstMouse)
	{
		lastX = x;
		lastY = y;
		firstMouse = false;
	}

	float xoffset = x - lastX;
	float yoffset = lastY - y;

	lastX = x;
	lastY = y;

	m_Camera->ProcessMouseMovement(xoffset, yoffset);
}

void InputHandler::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	m_Camera->ProcessMouseScroll(static_cast<float>(yoffset));
}

void InputHandler::processInput(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_Camera->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_Camera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m_Camera->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m_Camera->ProcessKeyboard(RIGHT, deltaTime);
}
