#pragma once

#include <vector>
#include <ECSTypes.h>
#include <glm/glm.hpp>
#include <ECSEngine.h>
#include "VertexPNUV.h"
#include "TextureData.h"

class MeshComponentFactory {
public:
	static ComponentId CreateCubeMesh(EntityId id, glm::mat4 model) {
		return ECSEngine::component_manager().CreateComponent<MeshComponent>(id, *vertices, *indices, *textures, model);
	}
private:
	static std::vector<VertexPNUV>* vertices;
	static std::vector<unsigned int>* indices;
	static std::vector<TextureData>* textures;
};

std::vector<VertexPNUV>* MeshComponentFactory::vertices = new std::vector<VertexPNUV> {
		VertexPNUV(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.333f, 0.0f),
		VertexPNUV(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
		VertexPNUV(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.333f, 0.5f),
		VertexPNUV(1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f),

		VertexPNUV(1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.667f, 0.0f),
		VertexPNUV(1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.333f, 0.0f),
		VertexPNUV(1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.667f, 0.5f),
		VertexPNUV(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.333f, 0.5f),

		VertexPNUV(1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f),
		VertexPNUV(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.667f, 0.0f),
		VertexPNUV(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f),
		VertexPNUV(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.667f, 0.5f),

		VertexPNUV(0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.333f, 0.5f),
		VertexPNUV(0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.5f),
		VertexPNUV(0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.333f, 1.0f),
		VertexPNUV(0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f),

		VertexPNUV(0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.667f, 0.5f),
		VertexPNUV(1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.333f, 0.5f),
		VertexPNUV(0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.667f, 1.0f),
		VertexPNUV(1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.333f, 1.0f),

		VertexPNUV(0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f),
		VertexPNUV(1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.667f, 0.5f),
		VertexPNUV(0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f),
		VertexPNUV(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.667f, 1.0f)
};

std::vector<unsigned int>* MeshComponentFactory::indices = new std::vector<unsigned int>{
		0, 1, 2,
		2, 1, 3,

		4, 5, 6,
		6, 5, 7,

		8, 9, 10,
		10, 9, 11,

		12, 13, 14,
		14, 13, 15,

		16, 17, 18,
		18, 17, 19,

		20, 21, 22,
		22, 21, 23
};

std::vector<TextureData>* MeshComponentFactory::textures = new std::vector<TextureData> {
		TextureData(1u, std::string("test"))
};