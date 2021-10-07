#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <SplayLibrary/SplayLibrary.hpp>

#include <iostream>

int main()
{
	spl::RenderWindow window({ 800, 600 }, "SPL Example");

	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	uint32_t VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	spl::Shader shader("examples/shaders/main.vert", "examples/shaders/main.frag");
	shader.use();

	uint32_t i = 0;
	while (!window.shouldClose())
	{
		spl::Event* event = nullptr;
		while (window.pollEvent(event)) {}

		window.clear({ 0.2f, 0.3f, 0.3f });

		shader.setUniform("t", (float)(2.f * scp::pi * ++i / 144 ));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		window.display();

	}

	return 0;
}
