#pragma once
#include <GL/glew.h>
#include <string>
#include <GLFW/glfw3.h>
#define ASSERT(x) if (!(x)) __debugbreak();

const std::string GetSeverity(GLenum severity);
int __stdcall LogErrorInfo(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
