#include "../main.hpp"

int advancedLightingMain()
{
	// spl::Window window({ 1000, 600 }, "SPL Example", false);
	// spl::Context* context = window.getContext();
	// spl::Context::setCurrentContext(context);
	// context->setIsDepthTestEnabled(true);
	// 
	// spl::Framebuffer framebuffer;
	// framebuffer.createNewTextureAttachment<spl::Texture2D>(spl::FramebufferAttachment::ColorAttachment0, scp::u32vec2{ 1000, 600 });
	// framebuffer.createNewRenderbufferAttachment(spl::FramebufferAttachment::DepthAttachment, spl::TextureInternalFormat::Depth_nu24_Stencil_u8, scp::u32vec2{ 1000, 600 });
	// 
	// spl::ShaderProgram shader1("examples/advancedLighting/resources/shaders/firstPass.vert", "examples/advancedLighting/resources/shaders/firstPass.frag");
	// spl::ShaderProgram shader2("examples/advancedLighting/resources/shaders/secondPass.vert", "examples/advancedLighting/resources/shaders/secondPass.frag");
	// 
	// spl::PerspectiveCamera camera({ 1000, 600 }, 0.1f, 100.f, 1.f);
	// camera.setTranslation({ 0.f, 0.f, 2.f });
	// 
	// spl::Mesh<> mesh("examples/advancedLighting/resources/meshes/suzanne.obj");
	// spl::Transformable3D meshTransform;
	// meshTransform.scale(0.5f);
	// 
	// scp::f32vec3 lightDir = -scp::normalize(scp::f32vec3{ 1.0, 0.0, 1.0 });
	// 
	// spl::Mesh<> screen(
	// 	{
	// 		{ {-1.f,  1.f, 0.f}, {0.f, 0.f, 1.f}, {0.f, 1.f} },
	// 		{ {-1.f, -1.f, 0.f}, {0.f, 0.f, 1.f}, {0.f, 0.f} },
	// 		{ { 1.f, -1.f, 0.f}, {0.f, 0.f, 1.f}, {1.f, 0.f} },
	// 		{ { 1.f,  1.f, 0.f}, {0.f, 0.f, 1.f}, {1.f, 1.f} }
	// 	},
	// 	{
	// 		0, 1, 3, 1, 2, 3
	// 	}
	// );
	// 
	// while (!window.shouldClose())
	// {
	// 	spl::Event* rawEvent = nullptr;
	// 	while (window.pollEvent(rawEvent))
	// 	{
	// 		switch (rawEvent->type)
	// 		{
	// 			case spl::EventType::ResizeEvent:
	// 			{
	// 				spl::ResizeEvent event = rawEvent->specialize<spl::EventType::ResizeEvent>();
	// 				context->setViewport({0, 0}, event.size);
	// 				camera.setAspect(event.size);
	// 
	// 				framebuffer.createNewTextureAttachment<spl::Texture2D>(spl::FramebufferAttachment::ColorAttachment0, event.size);
	// 				framebuffer.createNewRenderbufferAttachment(spl::FramebufferAttachment::DepthAttachment, spl::TextureInternalFormat::Depth_nu24_Stencil_u8, event.size);
	// 
	// 				break;
	// 			}
	// 		}
	// 	}
	// 
	// 	spl::Framebuffer::bind(framebuffer, spl::FramebufferTarget::DrawFramebuffer);
	// 	spl::Framebuffer::clear();
	// 
	// 	meshTransform.rotate({ -0.5f, 1.f, 0.3f }, 0.01f);
	// 
	// 	spl::ShaderProgram::bind(shader1);
	// 	shader1.setUniform("cameraPos", camera.getTranslation());
	// 	shader1.setUniform("lightDir", lightDir);
	// 
	// 	shader1.setUniform("projection", camera.getProjectionMatrix());
	// 	shader1.setUniform("view", camera.getViewMatrix());
	// 	shader1.setUniform("model", meshTransform.getTransformMatrix());
	// 
	// 	mesh.draw(spl::PrimitiveType::Triangles);
	// 
	// 	spl::Framebuffer::bind(window.getFramebuffer(), spl::FramebufferTarget::DrawFramebuffer);
	// 	spl::Framebuffer::clear();
	// 
	// 	spl::ShaderProgram::bind(shader2);
	// 	shader2.setUniform("scene", 0, *framebuffer.getTextureAttachment(spl::FramebufferAttachment::ColorAttachment0));
	// 
	// 	screen.draw(spl::PrimitiveType::Triangles);
	// 
	// 	window.display();
	// }

	return 0;
}
