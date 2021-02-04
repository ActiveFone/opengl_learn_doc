#include "KeyFrameAnimTest.h"
//#include <iostream>
#include <sstream>
using namespace std;

FrameData animConfig[] = {
	FrameData(1, glm::vec3(-0.4f, 0, 0), 0.0f, glm::vec3(1.0f)),
	FrameData(90, glm::vec3(0.2f, 0, 0), 90.0f, glm::vec3(0.4f)),
	FrameData(150, glm::vec3(0.6f, 0, 0), 10.0f, glm::vec3(0.7f)),
};

KeyFrameAnimTest::KeyFrameAnimTest(const unsigned int width, const unsigned int height)
{
	nWidth = width;
	nHeight = height;
}

bool KeyFrameAnimTest::init()
{	
	nFrameIdx = 0;

	int length = sizeof(animConfig) / sizeof(animConfig[0]);
	FrameData lastData = animConfig[length -1];
	nMaxFrameIdx = lastData.keyIndex;

	cubeTexture = loadTexture("res/img/smile.png");

	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVerts), &quadVerts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);

	shader.init("res/shader/DefaultShader.vs", "res/shader/DefaultShader.fs");
	shader.use();
	shader.setInt("texture1", 0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	return true;
}

void KeyFrameAnimTest::update()
{
	glClearColor(0.1f, 0.6f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glBindVertexArray(quadVAO);
	shader.use();

	if (nFrameIdx > nMaxFrameIdx)
		nFrameIdx = 0;
	
	nFrameIdx++;

	FrameData curData = getFrameDataByIndex(nFrameIdx);

	std::cout << "KeyFrame index:" << nFrameIdx << " posX:" << curData.Position.r << std::endl;

	glm::mat4 Position(1.0);
	glm::mat4 Rotate(1.0);
	glm::mat4 Scale(1.0);
	Position = glm::translate(Position, curData.Position);

	Scale = glm::scale(Scale, curData.Scale);

	Rotate = glm::rotate(Rotate, glm::radians(curData.Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

	shader.setMat4("Position", Position);
	shader.setMat4("Rotate", Rotate);
	shader.setMat4("Scale", Scale);

	glBindTexture(GL_TEXTURE_2D, cubeTexture);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void KeyFrameAnimTest::clean()
{
	glDeleteVertexArrays(1, &quadVAO);
	glDeleteBuffers(1, &quadVBO);
}

FrameData KeyFrameAnimTest::getFrameDataByIndex(int idx)
{	
	int length = sizeof(animConfig) / sizeof(animConfig[0]);
	FrameData lastData = animConfig[length - 1];

	FrameData retData(idx, lastData.Position, lastData.Rotation, lastData.Scale);

	for (int i = 0; i < length - 1; i++)
	{
		FrameData curData = animConfig[i];

		if (animConfig[i].keyIndex == idx)
		{
			retData = curData;
			break;
		} 
		else if(animConfig[i].keyIndex < idx && animConfig[i+1].keyIndex > idx)
		{	
			FrameData preData = animConfig[i];
			FrameData nextData = animConfig[i+1];
			float offset = nextData.keyIndex - preData.keyIndex;
			float curOffset = idx - preData.keyIndex;
			float delta = curOffset / offset;
			
			retData.Position = preData.Position + (nextData.Position - preData.Position) * glm::vec3(delta);

			retData.Rotation = preData.Rotation + (nextData.Rotation - preData.Rotation) * delta;
			retData.Scale = preData.Scale + (nextData.Scale - preData.Scale) * glm::vec3(delta);

			break;
		}
		
	}

	return retData;
}

