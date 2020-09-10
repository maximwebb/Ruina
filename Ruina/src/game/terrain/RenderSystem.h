#pragma once

#include <ECSEngine.h>
#include "System.h"
#include "ChunkPositionComponent.h"
#include "../../VertexArray.h"

class RenderSystem : public System {
public:
	RenderSystem(SystemId id) : System(id), va(VertexArray()),  {}
	VertexArray va;
	VertexBuffer vb = VertexBuffer(nullptr, 0);
	VertexBufferLayout vbl;



	void Update(const Event &e) override {
		std::vector<Component*> components = ECSEngine::component_manager().GetComponentGroup<MeshComponent>();
		for (Component* component : components) {
			MeshComponent c = *static_cast<MeshComponent*>(component);

		}
	}

};
