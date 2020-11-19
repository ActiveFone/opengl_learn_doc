#pragma once
#include "TestBase.h"

class ParticleTest :public TestBase
{
public:
	ParticleTest() {
		std::cout << "ParticleTest.ctor()" << std::endl;
	};
	ParticleTest(const unsigned int width, const unsigned int height);
	~ParticleTest() {};

	void showTest(GLFWwindow *window);
private:

};