#include <SplayLibrary/SplayLibrary.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main()
{
	spl::RenderWindow window({ 1000, 600 }, "SPL Example");

	spl::Shader shader("examples/resources/shaders/main.vert", "examples/resources/shaders/main.frag");
	shader.use();

	spl::Mesh<> mesh("examples/resources/meshes/teapot.obj");

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

	spl::Transformable transform;
	transform.scale(0.01f);
	while (!window.shouldClose())
	{
		spl::Event* event = nullptr;
		while (window.pollEvent(event)) {}

		window.clear({ 0.2f, 0.3f, 0.3f });

		transform.rotate({ 0.3f, 1.f, -0.5f }, scp::pi / 144.f);
		shader.setUniform("model", transform.getMatrix());
		window.draw(mesh);

		window.display();
	}

	return 0;
}
