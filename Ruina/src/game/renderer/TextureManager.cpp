#include "TextureManager.h"

std::map<std::string, std::unique_ptr<Texture>> TextureManager::textures;

Texture& TextureManager::Get(const std::string& key) {
	auto it = textures.find(key);
	if (it != textures.end()) {
		return *(it->second);
	}
	textures.insert({key, std::make_unique<Texture>(key)});
	return *textures.find(key)->second;
}