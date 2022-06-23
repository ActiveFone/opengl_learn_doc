#pragma once
#include "TestBase.h"
using namespace std;

struct FrameData {
	unsigned int keyIndex; //帧索引

	glm::vec3 Position; //位置

	float Rotation; //旋转角度

	glm::vec3 Scale; //缩放比例

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
		0.25f, 0.25f, 0.0f,  1.0f, 0.0f,
		0.25f, 0.75f, 0.0f,  0.0f, 0.0f,
		0.75f, 0.75f, 0.0f,  0.0f, 1.0f,

		0.25f, 0.25f, 0.0f,  1.0f, 0.0f,
		0.75f, 0.75f, 0.0f,  0.0f, 1.0f,
		0.75f, 0.25f, 0.0f,  1.0f, 1.0f,
	};

	FrameData getFrameDataByIndex(int idx);
};