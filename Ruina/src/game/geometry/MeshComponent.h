#pragma once
#include <vector>
#include "Component.h"
#include "Texture.h"
#include "VertexPNUV.h"

struct MeshComponent : public Component {
public:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	Texture& texture;
	glm::mat4 model;

	MeshComponent(ComponentId id, EntityId entityId, std::vector<VertexPNUV>& _vertices,
				  std::vector<unsigned int>& _indices, Texture& _texture,
				  glm::mat4 _model)
		: Component(id, entityId), indices(_indices), texture(_texture), model(_model) {
		vertices.reserve(_vertices.size() * 8);
		for (int i = 0; i < _vertices.size(); i++) {
			vertices.push_back(_vertices[i].x);
			vertices.push_back(_vertices[i].y);
			vertices.push_back(_vertices[i].z);

			vertices.push_back(_vertices[i].n_x);
			vertices.push_back(_vertices[i].n_y);
			vertices.push_back(_vertices[i].n_z);

			vertices.push_back(_vertices[i].u);
			vertices.push_back(_vertices[i].v);
		}
	};
};

