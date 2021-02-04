#pragma once
#include "TestBase.h"

class FrameBufferTest :public TestBase
{
public:
	FrameBufferTest() {
		std::cout << "IlluminationTest.ctor()" << std::endl;
	};
	FrameBufferTest(const unsigned int width, const unsigned int height) :TestBase(width, height) {};
	~FrameBufferTest() {};

	bool init();

	void update();

	void clean();

private:
	unsigned int cubeVAO, cubeVBO, planeVAO, planeVBO;
	unsigned int cubeTexture;
	unsigned int floorTexture;

	unsigned int framebuffer;
	unsigned int texColorBuffer;
	unsigned int quadVAO;
	unsigned int quadVBO;
	unsigned int fbo;
	Shader shader;
	Shader screenShader;

	void initObject();
	void drawObject(Shader shader);
	void initFrameBuffer();
	void drawScreenBuffer(Shader shader);
};