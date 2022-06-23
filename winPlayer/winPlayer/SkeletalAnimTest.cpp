#include "SkeletalAnimTest.h"
//#include <iostream>
#include <sstream>
using namespace std;

SkeletalFrameData animConfig[] = {
	SkeletalFrameData(1, glm::vec3(-0.4f, 0, 0), 0.0f, glm::vec3(1.0f)),
	SkeletalFrameData(50, glm::vec3(0.2f, 0, 0), 90.0f, glm::vec3(0.4f)),
	SkeletalFrameData(110, glm::vec3(0.6f, 0, 0), 10.0f, glm::vec3(0.7f)),
};

SkeletalAnimTest::SkeletalAnimTest(const unsigned int width, const unsigned int height)
{
	nWidth = width;
	nHeight = height;
}

bool SkeletalAnimTest::init()
{	
	initVertex();

	initJointPose();

	initSkeleton();

	bindBuffers();

	initShader();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	return true;
}

void SkeletalAnimTest::update()
{
	glClearColor(0.1f, 0.6f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	if (nFrameIdx > nMaxFrameIdx)
		nFrameIdx = 0;

	nFrameIdx++;

	shader.use();
	glBindTexture(GL_TEXTURE_2D, cubeTexture);

	drawTriangle();

	glBindVertexArray(0);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void SkeletalAnimTest::initVertex()
{
	
	tVertex[0] = SkinnedVertex(boneVerts1, 0);

	tVertex[1] = SkinnedVertex(boneVerts2, 1);
}

void SkeletalAnimTest::initSkeleton()
{
	glm::mat4 p0(1.0);
	glm::mat4 p1(1.0);

	Joint tJoint[] = { Joint(p0, "Root", -1), Joint(p1, "Arm", 0) };
	
	//glm::mat4 P1 = glm::translate(pose, glm::vec3(-0.4f, 0.0f, 0.0f));
	//glm::mat4 P0 = glm::rotate(pose, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	p0 = getBindPose(0);
	p1 = getBindPose(1);

	tJoint[0].mInverseBindPose = glm::inverse(p0);
	tJoint[1].mInverseBindPose = glm::inverse(p0 * p1);

	mSkeleton.nJointCount = 2;
	mSkeleton.tJoint[0] = tJoint[0];
	mSkeleton.tJoint[1] = tJoint[1];
}

void SkeletalAnimTest::initJointPose()
{
	tBindPose[0].nRotate = 0.0f;
	tBindPose[0].vTrans = glm::vec3(0.0f, 0.0f, 0.0f);

	tBindPose[1].nRotate = 0.0f;
	tBindPose[1].vTrans = glm::vec3(0.4f, 0.0f, 0.0f);

	tAnimPose[0].nRotate = 40.0f;
	tAnimPose[0].vTrans = glm::vec3(0.3f, 0.0f, 0.0f);

	tAnimPose[1].nRotate = -100.0f;
	tAnimPose[1].vTrans = glm::vec3(0.0f, 0.0f, 0.0f);
}

void SkeletalAnimTest::initShader()
{
	shader.init("res/shader/skeletalShader.vs", "res/shader/skeletalShader.fs");
	shader.use();
	shader.setInt("texture1", 0);
}

void SkeletalAnimTest::bindBuffers()
{	
	int meshCount = sizeof(tVertex) / sizeof(tVertex[0]);

	for (int i = 0; i < meshCount; i++)
	{
		glGenVertexArrays(1, &VAO[i]);
		glGenBuffers(1, &VBO[i]);
		glBindVertexArray(VAO[i]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tVertex[i].tPosition), &tVertex[i].tPosition, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glBindVertexArray(0);
	};
}

void SkeletalAnimTest::drawTriangle()
{
	int meshCount = sizeof(tVertex) / sizeof(tVertex[0]);

	for (int i = 0; i < meshCount; i++)
	{
		glm::mat4 Position(1.0);

		glm::mat4 F = getFinalTransform(i);

		shader.setMat4("P", F);
		
		glBindVertexArray(VAO[i]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	};
}

glm::mat4 SkeletalAnimTest::getFinalTransform(int index)
{
	glm::mat4 p(1.0);

	glm::mat4 Offset(1.0);
	glm::mat4 Global(1.0);

	int jointIndex = tVertex[index].nJointIndex;
	Joint bindJoint = mSkeleton.tJoint[jointIndex];

	Offset = p * bindJoint.mInverseBindPose;
	
	Global = getGlobalTransform(index);

	return Global * Offset;
	//return Offset;
}

glm::mat4 SkeletalAnimTest::getGlobalTransform(int index)
{	
	glm::mat4 Global(1.0);
		
	for (int i = index; i >= 0; i--)
	{	
		glm::mat4 animPose = getAnimPose(i);

		Global = animPose * Global;
	}

	return Global;
}

glm::mat4 SkeletalAnimTest::getAnimPose(int index)
{
	float rate = (float)nFrameIdx / nMaxFrameIdx;

	JointPose animPose = tAnimPose[index];
	glm::mat4 bindPose = getBindPose(index);

	glm::vec3 vTrans = animPose.vTrans;

	glm::mat4 Translate(1.0);
	glm::mat4 Rotate(1.0);
	glm::mat4 Scale(1.0);

	Translate = glm::translate(Translate, glm::vec3(vTrans.x * rate, vTrans.y * rate, vTrans.z * rate));
	Rotate = glm::rotate(Rotate, glm::radians(animPose.nRotate * rate), glm::vec3(0.0f, 0.0f, 1.0f));

	return bindPose * Translate * Rotate * Scale;
}

glm::mat4 SkeletalAnimTest::getBindPose(int index)
{

	JointPose bindPose = tBindPose[index];

	glm::vec3 vTrans = bindPose.vTrans;

	glm::mat4 Translate(1.0);
	glm::mat4 Rotate(1.0);
	glm::mat4 Scale(1.0);

	Translate = glm::translate(Translate, vTrans);
	Rotate = glm::rotate(Rotate, glm::radians(bindPose.nRotate), glm::vec3(0.0f, 0.0f, 1.0f));

	return Translate * Rotate * Scale;
}

void SkeletalAnimTest::clean()
{
	int meshCount = sizeof(tVertex) / sizeof(tVertex[0]);

	for (int i = 0; i < meshCount; i++)
	{
		glDeleteVertexArrays(1, &VAO[i]);
		glDeleteBuffers(1, &VBO[i]);
	};
}

glm::mat4 SkeletalAnimTest::getCurSubMat(int idx)
{
	glm::mat4 Rotate2(1.0);
	glm::mat4 Position(1.0);
	float curRotate = 40.0f * ((float)idx / nMaxFrameIdx);

	glm::mat4 R2 = glm::rotate(Rotate2, glm::radians(curRotate), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 T2 = glm::translate(Position, glm::vec3(0.4f, 0.0f, 0.0f));

	glm::mat4 P2 = T2 * R2;

	return P2;
}

glm::mat4 SkeletalAnimTest::getCurParentMat(int idx)
{
	glm::mat4 Rotate(1.0);
	glm::mat4 Position(1.0);
	float curTrans = 0.4f * ((float)idx / nMaxFrameIdx);

	glm::mat4 R1 = glm::rotate(Rotate, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 T1 = glm::translate(Position, glm::vec3(curTrans, 0.0f, 0.0f));

	glm::mat4 P1 = T1 * R1;

	return P1;
}

SkeletalFrameData SkeletalAnimTest::getFrameDataByIndex(int idx)
{	
	int length = sizeof(animConfig) / sizeof(animConfig[0]);
	SkeletalFrameData lastData = animConfig[length - 1];

	SkeletalFrameData retData(idx, lastData.Position, lastData.Rotation, lastData.Scale);

	for (int i = 0; i < length - 1; i++)
	{
		SkeletalFrameData curData = animConfig[i];

		if (animConfig[i].keyIndex == idx)
		{
			retData = curData;
			break;
		} 
		else if(animConfig[i].keyIndex < idx && animConfig[i+1].keyIndex > idx)
		{	
			SkeletalFrameData preData = animConfig[i];
			SkeletalFrameData nextData = animConfig[i+1];
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

