#pragma once
#include "TestBase.h"
//#include <glad/glad.h> 
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

class LightingMapTest :public TestBase
{
public:
	LightingMapTest() {
		std::cout << "LightingMapTest.ctor()" << std::endl;
	};
	LightingMapTest(const unsigned int width, const unsigned int height);
	~LightingMapTest() {};

	void showTest(GLFWwindow *window);
	//void showRockTest(GLFWwindow *window);
private:

};