#pragma once

#include "VertexPNUV.h"
#include "TextureData.h"
#include <vector>
#include <Component.h>

struct MeshComponent : public Component {
public:
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<TextureData> m_textures;

	glm::mat4 m_model;

	MeshComponent(ComponentId id, EntityId entityId, std::vector<VertexPNUV>& vertices,
				  std::vector<unsigned int>& indices, std::vector<TextureData>& textures,
				  glm::mat4 model)
		: Component(id, entityId), m_indices(indices), m_textures(textures), m_model(model) {
		m_vertices.reserve(vertices.size() * 8);
		for (int i = 0; i < vertices.size(); i++) {
			m_vertices.push_back(vertices[i].position.x);
			m_vertices.push_back(vertices[i].position.y);
			m_vertices.push_back(vertices[i].position.z);

			m_vertices.push_back(vertices[i].normal.x);
			m_vertices.push_back(vertices[i].normal.y);
			m_vertices.push_back(vertices[i].normal.z);

			m_vertices.push_back(vertices[i].tex_coords[0]);
			m_vertices.push_back(vertices[i].tex_coords[1]);
		}
	};
};

