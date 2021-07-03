#pragma once

#ifndef DEBUGGER

#include <string>
#include <GL/glew.h>

#include <iostream>

#define DEBUGGER
#define ASSERT(x) if (!(x)) __debugbreak();
#ifndef WIN32
#define __stdcall
#endif

std::string GetSeverity(GLenum severity);

int
__stdcall LogErrorInfo(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
					   const void *userParam);

void initDebugger();

#endif