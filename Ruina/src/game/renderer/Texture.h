#pragma once
#include "Renderer.h"
#include "stb_image/stb_image.h"

class Texture {
public:
	Texture() = default;
	explicit Texture(const std::string&);
	~Texture();
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	inline int GetWidth() const { return width; };
	inline int GetHeight() const { return height; };

	std::string path;

private:
	unsigned int renderer_id{};
	unsigned char* local_buffer{};
	int width{}, height{}, bpp{};
};

