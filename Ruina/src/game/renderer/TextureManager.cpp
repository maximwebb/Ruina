#include "TextureManager.h"

std::unordered_map<std::string, std::unique_ptr<Texture>> TextureManager::m_textures;

Texture& TextureManager::Get(const std::string& key) {
	auto it = m_textures.find(key);
	if (it != m_textures.end()) {
		return *(it->second);
	}
	m_textures.insert({key, std::make_unique<Texture>(key)});
	return *m_textures.find(key)->second;
}