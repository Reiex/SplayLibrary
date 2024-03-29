#include "../main.hpp"

int basicPhongMain()
{
	spl::Window window(1000, 600, "SPL Example", true);
	spl::Context* context = window.getContext();
	spl::Context::setCurrentContext(context);
	context->setClearColor(0.2f, 0.3f, 0.3f, 1.f);
	
	spl::ShaderProgram shader("examples/basicPhong/resources/shaders/main.vert", "examples/basicPhong/resources/shaders/main.frag");
	spl::ShaderProgram::bind(&shader);
	
	// spl::PerspectiveCamera camera({ 1000, 600 }, 0.1f, 100.f, 1.f);
	// camera.setTranslation({ 0.f, 0.f, 2.f });
	// 
	// spl::Mesh<> mesh("examples/basicPhong/resources/meshes/suzanne.obj");
	// spl::Transformable3D meshTransform;
	// meshTransform.scale(0.5);
	
	scp::f32vec3 lightDir = -scp::normalize(scp::f32vec3{ 1.0, 1.0, 1.0 });
	
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
					context->setViewport(0, 0, event.size.x, event.size.y);
					// camera.setAspect(event.size);
					break;
				}
			}
		}
	
		spl::DebugMessage* message = nullptr;
		while (context->pollDebugMessage(message))
		{
			std::cout << "#======== START OF DEBUG MESSAGE ==========================#" << std::endl;
			std::cout << message->descr << std::endl;
			std::cout << "#======== END OF DEBUG MESSAGE ============================#" << std::endl;
		}
	
		// if (window.isKeyPressed(spl::KeyboardKey::W)) camera.move(camera.getUpVector() * 0.01f);
		// if (window.isKeyPressed(spl::KeyboardKey::S)) camera.move(camera.getUpVector() * -0.01f);
		// if (window.isKeyPressed(spl::KeyboardKey::A)) camera.move(camera.getLeftVector() * 0.01f);
		// if (window.isKeyPressed(spl::KeyboardKey::D)) camera.move(camera.getLeftVector() * -0.01f);
		// if (window.isKeyPressed(spl::KeyboardKey::Space)) camera.move(camera.getFrontVector() * 0.01f);
		// if (window.isKeyPressed(spl::KeyboardKey::LeftShift)) camera.move(camera.getFrontVector() * -0.01f);
		// 
		// camera.lookAt({ 0.f, 0.f, 0.f });
		// 
		// shader.setUniform("cameraPos", camera.getTranslation());
		// shader.setUniform("lightDir", lightDir);
		// 
		// shader.setUniform("projection", camera.getProjectionMatrix());
		// shader.setUniform("view", camera.getViewMatrix());
		// shader.setUniform("model", meshTransform.getTransformMatrix());
		// 
		// mesh.draw(spl::PrimitiveType::Triangles);
	
		window.display();
		spl::Framebuffer::clear();
	}

	return 0;
}
