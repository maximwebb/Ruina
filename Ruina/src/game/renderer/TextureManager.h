#pragma once
#include <memory>
#include <map>
#include "Texture.h"

class TextureManager {
public:
	static Texture& Get(const std::string& key);

private:
	static std::map<std::string, std::unique_ptr<Texture>> textures;
};