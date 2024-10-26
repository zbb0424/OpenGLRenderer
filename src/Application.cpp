#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "InputHandler.h"

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main(void)
{
#pragma region INIT GLFW AND GLEW
	//glfw glew:initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (!glfwInit()) return -1;

	//glfw window creation
	GLFWwindow* window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "GLEW Error!" << std::endl;
#pragma endregion

#pragma region BLEND AND DEPTH
	//GLCall(glEnable(GL_BLEND));
	//GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glEnable(GL_DEPTH_TEST));
#pragma endregion
	{
#pragma region BUFFER SETTING
		float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
		};
		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};
		VertexArray VAO;
		VertexBuffer VBO(vertices, sizeof(vertices));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		VAO.AddBuffer(VBO, layout);
		VAO.Unbind();

		VertexArray lightVAO;
		lightVAO.AddBuffer(VBO, layout);
		lightVAO.Unbind();
#pragma endregion

#pragma region CAMERA AND INPUTHANDLER
		Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
		InputHandler inputHandler(SCR_WIDTH / 2.0f, SCR_HEIGHT / 2.0f, &camera);
		GLCall(glfwSetFramebufferSizeCallback(window, InputHandler::GLFWFramebufferSizeCallback));
		GLCall(glfwSetCursorPosCallback(window, InputHandler::GLFWMouseCallback));
		GLCall(glfwSetScrollCallback(window, InputHandler::GLFWScrollCallback));
		GLCall(glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED));
#pragma endregion

#pragma region SHADER AND TEXTURE
		Shader shader("res/shaders/vertexShader.glsl", "res/shaders/fragmentShader.glsl");
		shader.Bind();

		shader.SetUniformVec3f("viewPos", camera.Position);

		shader.SetUniform1i("material.diffuse", 0);
		shader.SetUniform1i("material.specular", 1);
		shader.SetUniform1f("material.shininess", 32.0f);

		shader.SetUniform1f("light.cutOff", glm::cos(glm::radians(12.5)));
		shader.SetUniform1f("light.outerCutOff", glm::cos(glm::radians(17.5f)));
		shader.SetUniformVec3f("light.ambient", 0.2f, 0.2f, 0.2f);
		shader.SetUniformVec3f("light.diffuse", 0.5f, 0.5f, 0.5f);
		shader.SetUniformVec3f("light.specular", 1.0f, 1.0f, 1.0f);
		shader.SetUniform1f("light.constant", 1.0f);
		shader.SetUniform1f("light.linear", 0.09f);
		shader.SetUniform1f("light.quadratic", 0.032f);

		Texture texture("res/textures/container2.png");
		Texture texture_specular("res/textures/container2.png");
		texture.Bind(0);
		texture_specular.Bind(1);
		shader.Unbind();

		Shader lightShader("res/shaders/vertexShader_light.glsl", "res/shaders/fragmentShader_light.glsl");
		lightShader.Bind();
		lightShader.Unbind();
#pragma endregion

		Renderer renderer;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			inputHandler.processInput(window, deltaTime);

			GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
			renderer.Clear();

			{
				lightVAO.Bind();
				lightShader.Bind();

				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, lightPos);
				model = glm::scale(model, glm::vec3(0.2f));
				glm::mat4 view = camera.GetViewMatrix();
				glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
				glm::mat4 mvp = projection * view * model;
				lightShader.SetUniformMat4f("u_MVP", mvp);

				renderer.DrawWithoutIBO(lightVAO, lightShader);

				lightVAO.Unbind();
				lightShader.Unbind();
			}

			{
				VAO.Bind();
				shader.Bind();

				glm::mat4 view = camera.GetViewMatrix();
				glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
				shader.SetUniformMat4f("view", view);
				shader.SetUniformMat4f("projection", projection);
				shader.SetUniformVec3f("light.position", camera.Position);
				shader.SetUniformVec3f("light.direction", camera.Front);
				for (unsigned int i = 0; i < 10; i++)
				{
					glm::mat4 model = glm::mat4(1.0f);
					model = glm::translate(model, cubePositions[i]);
					float angle = 20.0f * i;
					model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
					shader.SetUniformMat4f("model", model);

					renderer.DrawWithoutIBO(VAO, shader);
				}

				VAO.Unbind();
				shader.Unbind();
			}

			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}



