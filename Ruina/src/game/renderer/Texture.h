#pragma once
#include "Renderer.h"
#include "stb_image/stb_image.h"

class Texture {
public:
	explicit Texture(const std::string& key);
	~Texture();
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	inline int GetWidth() const { return m_width; };
	inline int GetHeight() const { return m_height; };

	std::string m_filepath;

private:
	unsigned int m_rendererID{};
	unsigned char* m_local_buffer{};
	int m_width{}, m_height{}, m_bpp{};
};

