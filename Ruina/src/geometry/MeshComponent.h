#pragma once

#include "VertexPNUV.h"
#include "TextureData.h"
#include <vector>
#include <Component.h>

struct MeshComponent : public Component {
public:
	std::vector<VertexPNUV> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<TextureData> m_textures;

	MeshComponent(ComponentId id, EntityId entityId, std::vector<VertexPNUV>& vertices,
				  std::vector<unsigned int> &indices, std::vector<TextureData> &textures)
		: Component(id, entityId), m_vertices(vertices), m_indices(indices), m_textures(textures) {};
};

