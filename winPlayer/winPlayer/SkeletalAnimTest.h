#pragma once
#include "TestBase.h"
using namespace std;

struct SkeletalFrameData {
	unsigned int keyIndex; //֡����

	glm::vec3 Position; //λ��

	float Rotation; //��ת�Ƕ�

	glm::vec3 Scale; //���ű���

	SkeletalFrameData(unsigned int idx, glm::vec3 pos, float rote, glm::vec3 scale)
		: keyIndex(idx), Position(pos), Rotation(rote), Scale(scale) { }

	SkeletalFrameData()
		: keyIndex(0), Position(0), Rotation(0), Scale(0) { }
};

//�ؽ�
struct Joint {
	glm::mat4 mInverseBindPose;

	string sName; //�ؽ���

	int nParentIdx; //���ؽ�����

	Joint(glm::mat4 pose, string name, int idx)
		: mInverseBindPose(pose), sName(name), nParentIdx(idx) { };

	Joint()
		: nParentIdx(0) { };
};

//�Ǽ�
struct Skeleton {
	
	int nJointCount; //�ؽ���

	Joint tJoint[2];  // �ؽ�����

	Skeleton()
		: nJointCount(0) { };
};

//�ؽ�����
struct JointPose
{
	float nRotate; // ��Ը��ؽڳ���
	glm::vec3 vTrans;  // �ڸ��ؽ��е�����
	float nScale;  // ��Ը��ؽڵ�����

	JointPose()
		: nRotate(0.0f), vTrans(0), nScale(1.0f){ };
};

// ��Ƥ����
struct SkinnedVertex
{
	float tPosition[9]; // ����λ�ã�x,y,z��
	int nJointIndex;  // �ؽڵ�����

	//float m_normal[3];   // ���㷨���� ��Nx,Ny,Nz��
	//float u, v;      // ��������
	//float nJointWeight; // �ؽ�Ȩ��

	SkinnedVertex(float *p, int index)
	{
		for (int i = 0; i < 9; i++)
		{
			tPosition[i] = p[i];
		};

		nJointIndex = index;
	}

	SkinnedVertex()
		: nJointIndex(0) { }
};

class SkeletalAnimTest :public TestBase
{
public:
	SkeletalAnimTest() {
		std::cout << "SkeletalAnimTest.ctor()" << std::endl;
	};
	SkeletalAnimTest(const unsigned int width, const unsigned int height);
	~SkeletalAnimTest() {};

	//vector<KeyData> animConfig;

	bool init();

	void initVertex();

	void initSkeleton();

	void initJointPose();

	void bindBuffers();

	void initShader();

	void update();

	void drawTriangle();

	void clean();

private:
	unsigned int VAO[2], VBO[2];
	unsigned int cubeTexture;
	unsigned int nFrameIdx = 0;
	unsigned int nMaxFrameIdx = 60;

	Shader shader;

	float boneVerts1[9] = {
		// positions   
		0.0f, 0.0f, 0.0f,
		0.2f, 0.1f, 0.0f,
		0.4f, 0.0f, 0.0f,
	};

	float boneVerts2[9] = {
		// positions   
		0.4f, 0.0f, 0.0f,
		0.6f, 0.1f, 0.0f,
		0.8f, 0.0f, 0.0f,
	};

	float boneVerts3[9] = {
		// positions   
		0.4f, 0.0f, 0.0f,
		0.6f, 0.1f, 0.0f,
		0.8f, 0.0f, 0.0f,
	};

	SkeletalFrameData getFrameDataByIndex(int idx);

	glm::mat4 getCurParentMat(int idx);
	glm::mat4 getCurSubMat(int idx);
	glm::mat4 getFinalTransform(int idx);
	glm::mat4 getGlobalTransform(int idx);
	glm::mat4 getBindPose(int idx);
	glm::mat4 getAnimPose(int idx);

	SkinnedVertex tVertex[2];

	JointPose tBindPose[2];

	JointPose tAnimPose[2];

	Skeleton mSkeleton;
};