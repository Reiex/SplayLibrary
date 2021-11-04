#include <SplayLibrary/SplayLibrary.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main()
{
	spl::RenderWindow window({ 1000, 600 }, "SPL Example");

	std::vector<spl::DefaultVertex> vertices = {
		{ { 1.f,  0.f, 0.0f}, {0.f, 0.f, 0.f}, { 1.f, -1.f} },
		{ { 0.f,  1.f, 0.0f}, {0.f, 0.f, 0.f}, { 1.f,  1.f} },
		{ {-1.f,  0.f, 0.0f}, {0.f, 0.f, 0.f}, {-1.f,  1.f} },
		{ { 0.f, -1.f, 0.0f}, {0.f, 0.f, 0.f}, {-1.f, -1.f} }
	};

	std::vector<uint32_t> indices = {
		0, 1, 2,
		0, 2, 3
	};

	spl::Mesh<> mesh(vertices, indices, spl::DrawableStorage::Stream);

	spl::Shader shader("examples/resources/shaders/main.vert", "examples/resources/shaders/main.frag");
	shader.use();

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

	float t = 0.0;
	while (!window.shouldClose())
	{
		spl::Event* event = nullptr;
		while (window.pollEvent(event))
		{
			switch (event->type)
			{
				case spl::EventType::TextEvent:
				{
					spl::TextEvent textEvent = event->specialize<spl::EventType::TextEvent>();
					// std::cout << (char)textEvent.unicode << std::endl;
				}
				case spl::EventType::MouseMoveEvent:
				{
					spl::MouseMoveEvent mouseMoveEvent = event->specialize<spl::EventType::MouseMoveEvent>();
					// std::cout << mouseMoveEvent.pos.x << ", " << mouseMoveEvent.pos.y << std::endl;
				}
			}
		}

		window.clear({ 0.2f, 0.3f, 0.3f });

		t += 1.f / 144;
		shader.setUniform("t", t);
		shader.setUniform("colorTexture", texture, 8);

		vertices[0].pos = {cos(t), sin(t), 0.f};
		vertices[1].pos = {-sin(t), cos(t), 0.f };
		vertices[2].pos = {-cos(t),-sin(t), 0.f };
		vertices[3].pos = { sin(t),-cos(t), 0.f };
		mesh.updateVertices(vertices);

		window.draw(mesh);

		window.display();
	}

	return 0;
}
