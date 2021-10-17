#include <SplayLibrary/SplayLibrary.hpp>

#include <iostream>

int main()
{
	spl::RenderWindow window({ 1000, 600 }, "SPL Example");

	std::vector<spl::DefaultVertex> vertices = {
		{ { 1.f,  0.f, 0.0f} },
		{ { 0.f,  1.f, 0.0f} },
		{ {-1.f,  0.f, 0.0f} },
		{ { 0.f, -1.f, 0.0f} }
	};

	std::vector<uint32_t> indices = {
		0, 1, 2,
		0, 2, 3
	};

	spl::Mesh<> mesh(vertices, indices, spl::DrawableStorage::Stream);

	spl::Shader shader("examples/shaders/main.vert", "examples/shaders/main.frag");
	shader.use();

	float t = 0.0;
	while (!window.shouldClose())
	{
		spl::Event* event = nullptr;
		while (window.pollEvent(event)) {}

		window.clear({ 0.2f, 0.3f, 0.3f });

		t += 1.0 / 144;
		shader.setUniform("t", t);

		vertices[0].pos = { cos(t), sin(t), 0.f };
		vertices[1].pos = {-sin(t), cos(t), 0.f };
		vertices[2].pos = {-cos(t),-sin(t), 0.f };
		vertices[3].pos = { sin(t),-cos(t), 0.f };
		mesh.updateVertices(vertices);

		window.draw(mesh);

		window.display();

	}

	return 0;
}
