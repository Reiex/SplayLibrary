#include <SplayLibrary/SplayLibrary.hpp>

#include <iostream>

struct Vertex
{
	static std::vector<spl::VertexAttribute> getVertexAttributes()
	{
		return {
			{0, spl::VertexAttribute::Type::Vec3, offsetof(Vertex, pos), sizeof(Vertex)}
		};
	}

	spl::vec3 pos;
};

int main()
{
	spl::RenderWindow window({ 800, 600 }, "SPL Example");

	std::vector<Vertex> vertices = {
		{{ 0.5f,  0.5f, 0.0f}},
		{{ 0.5f, -0.5f, 0.0f}},
		{{-0.5f, -0.5f, 0.0f}},
		{{-0.5f,  0.5f, 0.0f}}
	};

	std::vector<uint32_t> indices = {
		0, 1, 3,
		1, 2, 3
	};

	spl::Mesh<Vertex> mesh(vertices, indices);

	spl::Shader shader("examples/shaders/main.vert", "examples/shaders/main.frag");
	shader.use();

	uint32_t i = 0;
	while (!window.shouldClose())
	{
		spl::Event* event = nullptr;
		while (window.pollEvent(event)) {}

		window.clear({ 0.2f, 0.3f, 0.3f });

		shader.setUniform("t", (float)(2.f * scp::pi * ++i / 144 ));

		window.draw(mesh);

		window.display();

	}

	return 0;
}
