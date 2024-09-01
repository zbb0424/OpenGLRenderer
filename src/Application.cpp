#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <fstream>
#include <string>

#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];

float x = 0.0f;
float inc = 0.01f;

GLuint createShaderProgram();
void init(GLFWwindow* window);
void display(GLFWwindow* window, double currentTime);
void printShaderLog(GLuint shader);
void printProgramLog(int prog);
bool checkOpenGLError();
std::string readShaderSource(const std::string& filePath);

int main(void)
{
	//init glfw
	if (!glfwInit()) return -1;

	//set version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//create window
	GLFWwindow* window = glfwCreateWindow(600, 600, "SpikeOpenGLRenderer", NULL, NULL);
	glfwMakeContextCurrent(window);
	//init glew
	if (glewInit() != GLEW_OK) return -1;

	glfwSwapInterval(1);

	init(window);

	while (!glfwWindowShouldClose(window)) {
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

GLuint createShaderProgram()
{
	GLint vertCompiled;
	GLint fragCompiled;
	GLint linked;

	std::string vertexShaderStr   = readShaderSource("res/shaders/vertexShader.glsl");
	std::string fragmentShaderStr = readShaderSource("res/shaders/fragmentShader.glsl");

	const char* vertexShaderSrc = vertexShaderStr.c_str();
	const char* fragmentShaderSrc = fragmentShaderStr.c_str();

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint vfprogram = glCreateProgram();

	glShaderSource(vShader, 1, &vertexShaderSrc, NULL);
	glShaderSource(fShader, 1, &fragmentShaderSrc, NULL);

	glCompileShader(vShader);
	checkOpenGLError();
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
	if (vertCompiled != 1)
	{
		std::cout << "vertex compilation failed" << std::endl;
		printShaderLog(vShader);
	}

	glCompileShader(fShader);
	checkOpenGLError();
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
	if (fragCompiled != 1)
	{
		std::cout << "fragment compilation failed" << std::endl;
		printShaderLog(fShader);
	}

	glAttachShader(vfprogram, vShader);
	glAttachShader(vfprogram, fShader);

	glLinkProgram(vfprogram);
	checkOpenGLError();
	glGetProgramiv(vfprogram, GL_LINK_STATUS, &linked);
	if (linked != 1)
	{
		std::cout << "linking failed" << std::endl;
		printProgramLog(vfprogram);
	}
	return vfprogram;
}

void init(GLFWwindow* window)
{
	renderingProgram = createShaderProgram();
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
}

void display(GLFWwindow* window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	x += inc;
	if (x > 1.0f) inc = -0.01f;
	if (x < -1.0f) inc = 0.01f;
	GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset");
	glProgramUniform1f(renderingProgram, offsetLoc, x);


	//glPointSize(300.0f);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void printShaderLog(GLuint shader)
{
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0)
	{
		log = (char*)malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		std::cout << "Shader Info Log: " << log << std::endl;
		free(log);
	}
}

void printProgramLog(int prog)
{
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0)
	{
		log = (char*)malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		std::cout << "Program Info Log: " << log << std::endl;
		free(log);
	}
}

bool checkOpenGLError()
{
	bool foundError = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR)
	{
		std::cout << "glError: " << glErr << std::endl;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}

std::string readShaderSource(const std::string& filePath)
{

	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);
	std::string line = "";
	while (!fileStream.eof())
	{
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

