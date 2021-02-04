#pragma once
#include "TestBase.h"
#include "Model.h"

class GeometryTest :public TestBase
{
public:
	GeometryTest() {
		std::cout << "IlluminationTest.ctor()" << std::endl;
	};
	GeometryTest(const unsigned int width, const unsigned int height);
	~GeometryTest() {};

	bool init();
	bool initNormal();
	bool initModel();

	void update();
	void updateNormal();
	void updateModel();

	void clean();

	void showTest(GLFWwindow *window);

	void showModelTest(GLFWwindow *window);
private:
	unsigned int VAO, VBO;
	Shader shader, shader0, shader1, shader2;
	Model nanosuit;
};