#pragma once

#include <unordered_map>
#include "Texture.h"
#include "Texture.h"

class TextureManager {
public:
	static Texture& Get(const std::string& key);

	static std::unique_ptr<Texture> GetPtr(const std::string& key);

private:
	static std::unordered_map<std::string, std::unique_ptr<Texture>> m_textures;
};

