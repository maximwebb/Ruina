#pragma once
#include <memory>
#include <unordered_map>
#include "Texture.h"

class TextureManager {
public:
	static Texture& Get(const std::string& key);

private:
	static std::unordered_map<std::string, std::unique_ptr<Texture>> textures;
};

