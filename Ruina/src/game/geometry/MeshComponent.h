#pragma once
#include <utility>
#include <vector>
#include "Component.h"
#include "Texture.h"
#include "VertexPNUV.h"

struct MeshComponent : public Component {
public:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	Texture texture;
	glm::mat4 model;

	MeshComponent(const std::vector<VertexPNUV>& _vertices,
				  std::vector<unsigned int> indices, const Texture& initial_texture,
				  glm::mat4 model)
		: indices(std::move(indices)), model(model) {
		vertices.reserve(_vertices.size() * 8);
		for (auto& _vertex : _vertices) {
			vertices.push_back(_vertex.x);
			vertices.push_back(_vertex.y);
			vertices.push_back(_vertex.z);

			vertices.push_back(_vertex.n_x);
			vertices.push_back(_vertex.n_y);
			vertices.push_back(_vertex.n_z);

			vertices.push_back(_vertex.u);
			vertices.push_back(_vertex.v);
		}

		texture = initial_texture;
	};
};

