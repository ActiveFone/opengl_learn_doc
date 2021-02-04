#pragma once
#include "TestBase.h"
using namespace std;

struct FrameData {
	unsigned int keyIndex;
	glm::vec3 Position;
	float Rotation;
	glm::vec3 Scale;

	FrameData(unsigned int idx, glm::vec3 pos, float rote, glm::vec3 scale)
		: keyIndex(idx), Position(pos), Rotation(rote), Scale(scale) { }

	FrameData()
		: keyIndex(0), Position(0), Rotation(0), Scale(0) { }
};

class KeyFrameAnimTest :public TestBase
{
public:
	KeyFrameAnimTest() {
		std::cout << "KeyFrameAnimTest.ctor()" << std::endl;
	};
	KeyFrameAnimTest(const unsigned int width, const unsigned int height);
	~KeyFrameAnimTest() {};

	//vector<KeyData> animConfig;

	bool init();

	void update();

	void clean();

private:
	unsigned int quadVAO, quadVBO;
	unsigned int cubeTexture;
	unsigned int nFrameIdx = 0;
	unsigned int nMaxFrameIdx = 0;

	Shader shader;

	float quadVerts[30] = {
		// positions   // texture Coords
		-0.5f, -0.5f, 0.5f,  1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,  0.0f, 0.0f,
		0.5f, 0.5f, 0.5f,  0.0f, 1.0f,

		-0.5f, -0.5f, 0.5f,  1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, 0.5f,  1.0f, 1.0f,
	};

	FrameData getFrameDataByIndex(int idx);
};