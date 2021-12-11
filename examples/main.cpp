#include "main.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main()
{
	/*int success = 0;

	success &= basicPhongMain();

	return success;*/

	spl::RenderWindow window({ 1000, 600 }, "SPL Example");

	spl::Shader shader("examples/basicPhong/resources/shaders/main.vert", "examples/basicPhong/resources/shaders/main.frag");

	spl::PerspectiveCamera camera({ 1000, 600 }, 0.1f, 100.f, 1.f);
	camera.setTranslation({ 0.f, 0.f, 2.f });

	spl::Mesh<> mesh("examples/basicPhong/resources/meshes/teapot.obj");
	spl::Transformable3D meshTransform;
	meshTransform.scale(0.01f);

	spl::vec3 lightDir = -spl::normalize(spl::vec3{ 1.0, 0.0, 1.0 });




	unsigned int fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	spl::Texture2D texture(spl::uvec2{ 1000, 600 });

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.getRawTexture().getHandle(), 0);

	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1000, 600);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Nope" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	spl::Mesh<> screen(
		{
			{ {-1.f,  1.f, 0.f}, {0.f, 0.f, 1.f}, {0.f, 1.f} },
			{ {-1.f, -1.f, 0.f}, {0.f, 0.f, 1.f}, {0.f, 0.f} },
			{ { 1.f, -1.f, 0.f}, {0.f, 0.f, 1.f}, {1.f, 0.f} },
			{ { 1.f,  1.f, 0.f}, {0.f, 0.f, 1.f}, {1.f, 1.f} }
		},
		{
			0, 1, 3, 1, 2, 3
		}
	);

	spl::Shader shader2("examples/advancedLighting/resources/shaders/main.vert", "examples/advancedLighting/resources/shaders/main.frag");




	while (!window.shouldClose())
	{
		spl::Event* rawEvent = nullptr;
		while (window.pollEvent(rawEvent))
		{
			switch (rawEvent->type)
			{
				case spl::EventType::ResizeEvent:
				{
					spl::ResizeEvent event = rawEvent->specialize<spl::EventType::ResizeEvent>();
					camera.setAspect(event.size);
					break;
				}
			}
		}

		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		window.clear({ 0.2f, 0.3f, 0.3f });

		meshTransform.rotate({ -0.5f, 1.f, 0.3f }, 0.01f);

		shader.use();
		shader.setUniform("cameraPos", camera.getTranslation());
		shader.setUniform("lightDir", lightDir);

		shader.setUniform("projection", camera.getProjectionMatrix());
		shader.setUniform("view", camera.getViewMatrix());
		shader.setUniform("model", meshTransform.getTransformMatrix());

		window.draw(mesh);

		// window.display();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		window.clear({ 0.f, 0.f, 0.f });

		shader2.use();
		shader2.setUniform("scene", texture);

		window.draw(screen);

		window.display();
	}

	glDeleteFramebuffers(1, &fbo);

	return 0;
}
