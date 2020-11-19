#include "ParticleTest.h"
//#include <iostream>
#include <sstream>
using namespace std;

float particleVerts[] = {
	// positions   // texture Coords
	-0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, 0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, 0.5f, 0.5f,  0.0f, 1.0f,

	-0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, 0.5f, 0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, 0.5f,  1.0f, 1.0f
};

struct Particle {
	glm::vec2 Position, Velocity;
	glm::vec4 Color;
	GLfloat Life;
	GLfloat Angle;

	Particle()
		: Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f), Angle(0.0f) { }
};

ParticleTest::ParticleTest(const unsigned int width, const unsigned int height)
{
	nWidth = width;
	nHeight = height;
}

void ParticleTest::showTest(GLFWwindow *window)
{

	GLuint nr_particles = 100;
	std::vector<Particle> particles;

	for (GLuint i = 0; i < nr_particles; ++i)
		particles.push_back(Particle());
	
	unsigned int quadVAO, quadVBO;
	unsigned int cubeTexture = loadTexture("res/img/smile.png");

	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particleVerts), &particleVerts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);

	Shader shader("res/shader/ParticleTestShader.vs", "res/shader/ParticleTestShader.fs");
	shader.use();
	shader.setInt("texture1", 0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float startTime = glfwGetTime();
	float deltaTime = 0;
	srand(glfwGetTime()); // 初始化随机种子

	int num = 0;
	for (auto &particle : particles)
	{
		particle.Life = -1 * GLfloat(rand() % 50) / 100;
		particle.Angle = (rand() % 60);
		num++;
	}

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		
		deltaTime = glfwGetTime() - startTime;

		float offsetX = deltaTime / 2;

		if (offsetX > 1)
			startTime = glfwGetTime();

		// input
		// -----
		processInput(window);

		// render
		// ------
		//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glEnable(GL_DEPTH_TEST);

		glClearColor(0.1f, 0.6f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glBindVertexArray(quadVAO);

		for (auto &particle : particles)
		{			
			particle.Life += 0.0005;

			if (particle.Life > 1)
				particle.Life = -1 * GLfloat(rand() % 50) / 100;
			else if (particle.Life > 0)
			{
				shader.use();

				//glm::vec2 coord = glm::vec2(sin(currentFrame), cos(currentFrame));
				float rad = 0.0175 * particle.Angle;
				
				float y = particle.Life * sin(rad);
				float x = particle.Life * cos(rad);

				glm::vec2 coord = glm::vec2(x, y);
				shader.setVec2("coord", coord);
				shader.setFloat("opacity", (1 - particle.Life) * 0.8);

				glBindTexture(GL_TEXTURE_2D, cubeTexture);
				glDrawArrays(GL_TRIANGLES, 0, 6);

			}
		}
		
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &quadVAO);
	glDeleteBuffers(1, &quadVBO);

}