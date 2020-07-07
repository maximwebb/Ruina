#pragma once

#include "Renderer.h"
#include "Debugger.h"

class Texture {
private:
	unsigned int m_rendererID;
	std::string m_filepath;
	unsigned char *m_local_buffer;
	int m_width, m_height, m_bpp;

public:
	Texture(const std::string &path);

	~Texture();

	void Bind(unsigned int slot = 0);

	void Unbind();

	inline int GetWidth() const { return m_width; };

	inline int GetHeight() const { return m_height; };
};

