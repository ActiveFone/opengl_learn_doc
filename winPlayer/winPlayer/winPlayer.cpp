#pragma once
#include <iostream>

#include "IlluminationTest.h"
#include "InstancingTest.h"
#include "FrameBufferTest.h"
#include "GeometryTest.h"
#include "ModelLoadTest.h"
#include "LightingMapTest.h"
#include "LuaBindTest.h"
#include "ParticleTest.h"
#include "KeyFrameAnimTest.h"
#include "SkeletalAnimTest.h"

// settings
const unsigned int SCR_WIDTH = 400;
const unsigned int SCR_HEIGHT = 400;

//IlluminationTest testHandler(SCR_WIDTH, SCR_HEIGHT);
//InstancingTest testHandler(SCR_WIDTH, SCR_HEIGHT);
//FrameBufferTest testHandler(SCR_WIDTH, SCR_HEIGHT);
//ModelLoadTest testHandler(SCR_WIDTH, SCR_HEIGHT);
//GeometryTest testHandler(SCR_WIDTH, SCR_HEIGHT);
//LightingMapTest testHandler(SCR_WIDTH, SCR_HEIGHT);
//LuaBindTest testHandler(SCR_WIDTH, SCR_HEIGHT);
//ParticleTest testHandler(SCR_WIDTH, SCR_HEIGHT);
//KeyFrameAnimTest testHandler(SCR_WIDTH, SCR_HEIGHT);
SkeletalAnimTest testHandler(SCR_WIDTH, SCR_HEIGHT);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow *window);

GLFWwindow * createWindow();

int main()
{
	GLFWwindow* window = createWindow();
	if (window == NULL)
		return -1;
	
	// init test
	testHandler.init();

	float startTime = glfwGetTime();
	float deltaTime = 1.0/30; // ÿ��30֡

	while (!glfwWindowShouldClose(window))
	{
		if ((glfwGetTime() - startTime) > deltaTime) {

			std::cout << glfwGetTime() << std::endl;

			// input
			// -----
			testHandler.processInput(window);

			// update test everyFrame
			testHandler.update();

			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(window);
			glfwPollEvents();

			startTime = glfwGetTime();
		}
	}

	testHandler.clean();

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

GLFWwindow *createWindow()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return NULL;
	}

	return window;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow *window)
//{
//	testInstance.processInput(window);
//}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	testHandler.mouse_callback(window, xpos, ypos);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	testHandler.scroll_callback(window, xoffset, yoffset);
}
