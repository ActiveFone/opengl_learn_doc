#include "GeometryTest.h"
//#include <iostream>
#include <sstream>
#include "camera.h"

using namespace std;
bool bModelTest = true;

float points[] = {
	-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // 左上
	0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // 右上
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // 右下
	-0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // 左下
};

GeometryTest::GeometryTest(const unsigned int width, const unsigned int height)
{
	nWidth = width;
	nHeight = height;
}

bool GeometryTest::init()
{
	if (bModelTest)
		return initModel();
	else
		return initNormal();
}

bool GeometryTest::initNormal()
{
	// VAO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glBindVertexArray(0);

	// SHADER
	shader.init("res/shader/geometryTestShader.vs", "res/shader/geometryTestShader.fs",
		"res/shader/geometryTestShader.gs");

	return true;
}

bool GeometryTest::initModel()
{
	shader0.init("res/shader/modelLoadingShader.vs",
		"res/shader/modelLoadingShader.fs");

	shader1.init("res/shader/geometryModelTestShader.vs",
		"res/shader/geometryModelTestShader.fs", "res/shader/geometryModelTestShader.gs");

	shader2.init("res/shader/geometryTestNormalShader.vs",
		"res/shader/geometryTestNormalShader.fs", "res/shader/geometryTestNormalShader.gs");

	// load models
	// -----------
	nanosuit.loadModel("res/objects/nanosuit/nanosuit.obj");

	return true;
}

void GeometryTest::update() {
	if (bModelTest)
		return updateModel();
	else
		return updateNormal();
}

void GeometryTest::updateNormal() {
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader.use();
	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, 4);
}

void GeometryTest::updateModel() {
	glClearColor(0.0f, 0.4f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// configure transformation matrices
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)nWidth / (float)nHeight, 1.0f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 model = glm::mat4(1.0f);
	//projection = glm::translate(projection, glm::vec3(-1.0f, -8.0f, -23.0f));
	model = glm::translate(model, glm::vec3(2.0f, -1.45f, -0.5f));
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

	shader1.use();
	shader1.setMat4("projection", projection);
	shader1.setMat4("view", view);
	shader1.setMat4("model", model);

	// add time component to geometry shader in the form of a uniform
	shader1.setFloat("time", glfwGetTime());

	// draw model
	nanosuit.Draw(shader1);

	// then draw model with normal visualizing geometry shader
	/*shader2.use();
	shader2.setMat4("projection", projection);
	shader2.setMat4("view", view);
	shader2.setMat4("model", model);
	shader2.setFloat("time", glfwGetTime());*/

	//nanosuit.Draw(shader2);

	int error = glGetError();
	//glGetShaderInfoLog(shader1.ID);
	//glGetProgramInfoLog();
}

void GeometryTest::clean()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &VBO);
}