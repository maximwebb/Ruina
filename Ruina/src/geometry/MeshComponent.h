#pragma once

#include "VertexPNUV.h"
#include "TextureData.h"
#include "Texture.h"
#include <vector>
#include <Component.h>

struct MeshComponent : public Component {
public:
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
	Texture& m_textures;

	glm::mat4 m_model;

	MeshComponent(ComponentId id, EntityId entityId, std::vector<VertexPNUV>& vertices,
				  std::vector<unsigned int>& indices, Texture& texture,
				  glm::mat4 model)
		: Component(id, entityId), m_indices(indices), m_textures(texture), m_model(model) {
		m_vertices.reserve(vertices.size() * 8);
		for (int i = 0; i < vertices.size(); i++) {
			m_vertices.push_back(vertices[i].x);
			m_vertices.push_back(vertices[i].y);
			m_vertices.push_back(vertices[i].z);

			m_vertices.push_back(vertices[i].n_x);
			m_vertices.push_back(vertices[i].n_y);
			m_vertices.push_back(vertices[i].n_z);

			m_vertices.push_back(vertices[i].u);
			m_vertices.push_back(vertices[i].v);
		}
	};
};

