#pragma once

#include <string>

struct TextureData {
	TextureData(unsigned int id, const std::string &type) : id(id), type(type) {}

	unsigned int id;
	std::string type;
};