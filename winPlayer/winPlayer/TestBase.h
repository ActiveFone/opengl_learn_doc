#pragma once
#include "camera.h"
#include "shader_m.h"

#include "CommonBase.h"

class TestBase:public CommonBase
{
public:
	TestBase();
	TestBase(const unsigned int width, const unsigned int height);
	~TestBase();

	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void processInput(GLFWwindow *window);
	//unsigned int loadTexture(const char* path);

	void showTest(GLFWwindow *window);

	//初始化
	bool init() {
		std::cout << "function init() must be overload" << std::endl;
	};

	//每帧刷新
	void update() {
		std::cout << "function update() must be overload" << std::endl;
	};

	//退出清理
	void clean() {
		std::cout << "function update() must be overload" << std::endl;
	};

	unsigned int nWidth;
	unsigned int nHeight;
	// timing
	float deltaTime;
	float lastFrame;

	GLFWwindow* mWindow;
	Camera camera;

private:
	float lastX;
	float lastY;
	bool firstMouse;
};