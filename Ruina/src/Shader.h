#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderProgramSource {
	ShaderProgramSource() = default;

	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {
private:
	std::string m_vertex_filepath;
	std::string m_fragment_filepath;
	ShaderProgramSource m_source;
	unsigned int m_rendererID;
	std::unordered_map<std::string, int> m_location_cache;
public:
	Shader(const std::string &vertex_filepath, const std::string &fragment_filepath);

	~Shader();

	void Bind() const;

	void Unbind() const;

	void SetUniform1i(const std::string &name, int value);

	void SetUniform1f(const std::string &name, float value);

	void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3);

	void SetUniformMat4(const std::string &name, const glm::mat4& matrix);

private:
	std::string ParseShader(const std::string &filepath);

	unsigned int CompileShader(unsigned int type, const std::string &source);

	unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);

	int GetUniformLocation(const std::string &name);
};

