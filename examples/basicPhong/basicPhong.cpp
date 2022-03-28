#include "../main.hpp"

int basicPhongMain()
{
	spl::Window window({ 1000, 600 }, "SPL Example");
	spl::Context* context = window.getContext();
	spl::ContextManager::setCurrentContext(context);
	context->setIsDepthTestEnabled(true);
	context->setClearColor({ 0.2f, 0.3f, 0.3f, 1.f });

	spl::Shader shader("examples/basicPhong/resources/shaders/main.vert", "examples/basicPhong/resources/shaders/main.frag");
	spl::Shader::bind(shader);

	spl::PerspectiveCamera camera({ 1000, 600 }, 0.1f, 100.f, 1.f);
	camera.setTranslation({ 0.f, 0.f, 2.f });

	spl::Mesh<> mesh("examples/basicPhong/resources/meshes/teapot.obj");
	spl::Transformable3D meshTransform;
	meshTransform.scale(0.01f);

	spl::vec3 lightDir = -spl::normalize(spl::vec3{ 1.0, 1.0, 1.0 });

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
					context->setViewport({ 0, 0 }, event.size);
					camera.setAspect(event.size);
					break;
				}
			}
		}

		if (window.isKeyPressed(spl::KeyboardKey::W)) camera.move(camera.getUpVector() * 0.01f);
		if (window.isKeyPressed(spl::KeyboardKey::S)) camera.move(camera.getUpVector() * -0.01f);
		if (window.isKeyPressed(spl::KeyboardKey::A)) camera.move(camera.getLeftVector() * 0.01f);
		if (window.isKeyPressed(spl::KeyboardKey::D)) camera.move(camera.getLeftVector() * -0.01f);
		if (window.isKeyPressed(spl::KeyboardKey::Space)) camera.move(camera.getFrontVector() * 0.01f);
		if (window.isKeyPressed(spl::KeyboardKey::LeftShift)) camera.move(camera.getFrontVector() * -0.01f);

		camera.lookAt({ 0.f, 0.f, 0.f });

		shader.setUniform("cameraPos", camera.getTranslation());
		shader.setUniform("lightDir", lightDir);

		shader.setUniform("projection", camera.getProjectionMatrix());
		shader.setUniform("view", camera.getViewMatrix());
		shader.setUniform("model", meshTransform.getTransformMatrix());

		mesh.draw();

		window.display();
		spl::Framebuffer::clear();
	}

	return 0;
}
