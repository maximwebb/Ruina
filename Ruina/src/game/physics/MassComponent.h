#pragma once
#include <glm/vec3.hpp>
#include <vector>
#include "Component.h"

struct MassComponent : public Component {
	explicit MassComponent(float mass) : mass(mass) {}

	float mass;
};