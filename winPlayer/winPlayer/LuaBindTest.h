#pragma once
#include "TestBase.h"

class LuaBindTest :public TestBase
{
public:
	LuaBindTest() {
		std::cout << "LuaBindTest.ctor()" << std::endl;
	};
	LuaBindTest(const unsigned int width, const unsigned int height) {};
	~LuaBindTest() {};

	void showTest(GLFWwindow *window);
private:
	int luaAdd(int x, int y);
};