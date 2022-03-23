#include "../main.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int advancedLightingMain()
{
	spl::RenderWindow window({ 1000, 600 }, "SPL Example");

	spl::Shader shader("examples/advancedLighting/resources/shaders/firstPass.vert", "examples/advancedLighting/resources/shaders/firstPass.frag");

	spl::PerspectiveCamera camera({ 1000, 600 }, 0.1f, 100.f, 1.f);
	camera.setTranslation({ 0.f, 0.f, 2.f });

	spl::Mesh<> mesh("examples/advancedLighting/resources/meshes/teapot.obj");
	spl::Transformable3D meshTransform;
	meshTransform.scale(0.01f);

	spl::vec3 lightDir = -spl::normalize(spl::vec3{ 1.0, 0.0, 1.0 });

	spl::Framebuffer framebuffer;

	framebuffer.createNewTextureAttachment<spl::Texture2D>(spl::FramebufferAttachment::ColorAttachment0, spl::uvec2{ 1000, 600 });
	framebuffer.createNewRenderBufferAttachment(spl::FramebufferAttachment::DepthAttachment, spl::TextureInternalFormat::Depth24_Stencil8, spl::uvec2{ 1000, 600 });

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

	spl::Shader shader2("examples/advancedLighting/resources/shaders/secondPass.vert", "examples/advancedLighting/resources/shaders/secondPass.frag");

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

					framebuffer.createNewTextureAttachment<spl::Texture2D>(spl::FramebufferAttachment::ColorAttachment0, event.size);
					framebuffer.createNewRenderBufferAttachment(spl::FramebufferAttachment::DepthAttachment, spl::TextureInternalFormat::Depth24_Stencil8, event.size);

					break;
				}
			}
		}

		spl::Framebuffer::bind(framebuffer, spl::FramebufferTarget::DrawFramebuffer);
		spl::Framebuffer::clearColor({ 0.2f, 0.3f, 0.3f, 1.f });
		spl::Framebuffer::clearDepth(1.f);

		meshTransform.rotate({ -0.5f, 1.f, 0.3f }, 0.01f);

		shader.use();
		shader.setUniform("cameraPos", camera.getTranslation());
		shader.setUniform("lightDir", lightDir);

		shader.setUniform("projection", camera.getProjectionMatrix());
		shader.setUniform("view", camera.getViewMatrix());
		shader.setUniform("model", meshTransform.getTransformMatrix());

		mesh.draw();

		spl::Framebuffer::bind(window.getFramebuffer(), spl::FramebufferTarget::DrawFramebuffer);
		spl::Framebuffer::clearColor({ 0.f, 0.f, 0.f, 1.f });
		spl::Framebuffer::clearDepth(1.f);

		shader2.use();
		shader2.setUniform("scene", *framebuffer.getTextureAttachment(spl::FramebufferAttachment::ColorAttachment0));

		screen.draw();

		window.display();
	}

	return 0;
}
