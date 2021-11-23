#include <SplayLibrary/SplayLibrary.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main()
{
	spl::RenderWindow window({ 1000, 600 }, "SPL Example");

	spl::Shader shader("examples/resources/shaders/main.vert", "examples/resources/shaders/main.frag");
	shader.use();

	spl::PerspectiveCamera camera({ 1000, 600 }, 0.1f, 100.f, 1.f);
	camera.setPosition({ 0.f, 0.f, 2.f });

	spl::Mesh<> mesh("examples/resources/meshes/teapot.obj");
	spl::Transformable3D meshTransform;
	meshTransform.scale(0.01f);

	djv::RGBAImg img("examples/resources/images/texture.jpg", true, true, false);
	float* data = new float[3 * img.width() * img.height()];
	uint64_t k = -1;
	for (uint64_t i = 0; i < img.width(); ++i)
	{
		for (uint64_t j = 0; j < img.height(); ++j)
		{
			data[++k] = img[i][j][0];
			data[++k] = img[i][j][1];
			data[++k] = img[i][j][2];
		}
	}

	spl::RawTexture texture;

	spl::RawTexture::CreationParams creationParams{};
	creationParams.target = spl::TextureTarget::Texture2D;
	creationParams.width = img.width();
	creationParams.height = img.height();
	creationParams.internalFormat = spl::TextureInternalFormat::RGB8;

	texture.createNew(creationParams);

	spl::RawTexture::UpdateParams updateParams{};
	updateParams.dataFormat = spl::TextureFormat::RGB;
	updateParams.dataType = spl::TextureDataType::Float;
	updateParams.width = img.width();
	updateParams.height = img.height();
	updateParams.data = data;

	texture.update(updateParams);

	delete[] data;

	spl::RawTexture::bind(texture, spl::TextureTarget::Texture2D, 0);
	// glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	spl::RawTexture::unbind(spl::TextureTarget::Texture2D);

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

		if (window.isKeyPressed(spl::KeyboardKey::W)) camera.move(camera.getUpVector() * 0.01f);
		if (window.isKeyPressed(spl::KeyboardKey::S)) camera.move(camera.getUpVector() * -0.01f);
		if (window.isKeyPressed(spl::KeyboardKey::A)) camera.move(camera.getLeftVector() * 0.01f);
		if (window.isKeyPressed(spl::KeyboardKey::D)) camera.move(camera.getLeftVector() * -0.01f);
		if (window.isKeyPressed(spl::KeyboardKey::Space)) camera.move(camera.getFrontVector() * 0.01f);
		if (window.isKeyPressed(spl::KeyboardKey::LeftShift)) camera.move(camera.getFrontVector() * -0.01f);

		camera.lookAt({ 0.f, 0.f, 0.f });

		shader.setUniform("projection", camera.getProjectionMatrix());
		shader.setUniform("view", camera.getViewMatrix());
		shader.setUniform("model", meshTransform.getTransformMatrix());

		window.draw(mesh);

		window.display();
		window.clear({ 0.2f, 0.3f, 0.3f });
	}

	return 0;
}
