#include <filesystem>
#include "Shader.h"

Shader::Shader(const std::string& vertex_filepath, const std::string& fragment_filepath)
		: m_vertex_filepath(vertex_filepath), m_fragment_filepath(fragment_filepath), m_rendererID(0) {
	m_source.VertexSource = ParseShader(vertex_filepath);
	m_source.FragmentSource = ParseShader(fragment_filepath);
	m_rendererID = CreateShader(m_source.VertexSource, m_source.FragmentSource);
}

Shader::~Shader() {
	glDeleteProgram(m_rendererID);
}

std::string Shader::ParseShader(const std::string& filepath) {
	std::ifstream stream(filepath);
	std::string line;
	std::stringstream ss;

	while (getline(stream, line)) {
		ss << line << '\n';
	}

	return ss.str();
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
#ifdef WIN32
		char *message = (char *) _malloca(length * sizeof(char));
#else
		char* message = (char*) malloc(length * sizeof(char));
#endif

		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " <<
				  (type == GL_VERTEX_SHADER ? "Vertex Shader " : "Fragment Shader ") << ":(" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return false;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();

	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::Bind() const {
	glUseProgram(m_rendererID);
}

void Shader::Unbind() const {
	glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int value) {
	glUniform1i(GetUniformLocation(name), (GLint) value);
}

void Shader::SetUniform1f(const std::string& name, float value) {
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform4f(const std::string& name, glm::vec4 v) {
	glUniform4f(GetUniformLocation(name), v.x, v.y, v.z, v.w);
}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& matrix) {
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::GetUniformLocation(const std::string& name) {
	if (m_location_cache.find(name) != m_location_cache.end())
		return m_location_cache[name];

	int location = glGetUniformLocation(m_rendererID, name.c_str());
	if (location == -1)
		std::cout << "Warning: uniform " << name << " does not exist..." << std::endl;
	m_location_cache[name] = location;
	return glGetUniformLocation(m_rendererID, name.c_str());
}