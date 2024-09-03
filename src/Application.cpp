#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <string>

#include "Renderer.h"

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include "Cube.h"

int main(void)
{
	//glfw glew:initialize and configure
	//-------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (!glfwInit()) return -1;

	//glfw window creation
	GLFWwindow* window = glfwCreateWindow(600, 600, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "GLEW Error!" << std::endl;

	{
		// set up vertex data (and buffer(s)) and configure vertex attributes
		// ------------------------------------------------------------------
		Cube cube;
		const float* data = cube.GetCubeData();
		float positions[108];

		std::copy(data, data + 108, positions);
		//float positions[] = {
		//	0.5f,  0.5f, 0.0f,
		//	0.5f, -0.5f, 0.0f,
		//	-0.5f, -0.5f, 0.0f,
		//	-0.5f,  0.5f, 0.0f
		//};

		////unsigned int indices[] = {
		////	0, 1, 3,
		////	1, 2, 3
		////};

		VertexArray VAO;
		VAO.Bind();
		VertexBuffer VBO(positions, 108 * sizeof(float));
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
		glEnableVertexAttribArray(0);
		////VertexBufferLayout layout;
		////layout.Push<float>(3);
		////VAO.AddBuffer(VBO, layout);

		////IndexBuffer IBO(indices, sizeof(indices) / sizeof(indices[0]));

		////VAO.AddBuffer(VBO, layout);

		//build and compile shader program
		// ------------------------------------
		Shader shader("res/shaders/vertexShader.glsl", "res/shaders/fragmentShader.glsl");
		shader.Bind();

		////VAO.Unbind();
		////VBO.Unbind();
		////IBO.Unbind();
		////shader.Unbind();

		float cameraX = 0.0f; float cameraY = 0.0f; float cameraZ = 8.0f;
		float cubeLocX = 0.0f; float cubeLocY = -2.0f; float cubeLocZ = 0.0f;

		unsigned int mvloc, projloc;
		int width, height;
		float aspect;
		glm::mat4 pMat, vMat, mMat, tMat, rMat, mvpMat;

		Renderer renderer;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			renderer.Clear();

			tMat = glm::translate(glm::mat4(1.0f), glm::vec3(sin(0.35f * glfwGetTime()) * 2.0f, cos(0.52f * glfwGetTime()) * 2.0f, sin(0.7f * glfwGetTime()) * 2.0f));

			rMat = glm::rotate(glm::mat4(1.0f), 1.75f * (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
			rMat = glm::rotate(rMat, 1.75f * (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));
			rMat = glm::rotate(rMat, 1.75f * (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

			mMat = tMat * rMat;

			//mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ));
			vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));

			glfwGetFramebufferSize(window, &width, &height);
			aspect = (float)width / (float)height;
			pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);

			mvpMat = pMat * vMat * mMat;

			shader.SetUniformMat4f("mvp_matrix", mvpMat);

			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			////renderer.Draw(VAO, IBO, shader);
			renderer.Draw(VAO, shader);
			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

