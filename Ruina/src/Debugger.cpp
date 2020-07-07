#pragma once

#ifndef DEBUGGER

#include "Debugger.h"

#define DEBUGGER

const std::string GetSeverity(GLenum severity) {
	if (severity == GL_DEBUG_SEVERITY_HIGH_AMD) {
		return "HIGH";
	} else if (severity == GL_DEBUG_SEVERITY_MEDIUM_AMD) {
		return "MEDIUM";
	} else if (severity == GL_DEBUG_SEVERITY_LOW_AMD) {
		return "LOW";
	}

	return "NONE";
}

int
__stdcall LogErrorInfo(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
					   const void *userParam) {
	const std::string severity_name = GetSeverity(severity);
	if (severity_name != "NONE") {
		std::cout << "[OpenGL Error] Severity: " << severity_name << std::endl << message << std::endl;
		__debugbreak();
	}
	return 0;
}

void initDebugger() {
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback((GLDEBUGPROC) LogErrorInfo, nullptr);
}

#endif