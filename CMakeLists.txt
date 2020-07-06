cmake_minimum_required(VERSION 3.16)
project(Ruina)

set(CMAKE_CXX_STANDARD 14)

include_directories(Dependencies)
include_directories(Dependencies/GLEW)
include_directories(Dependencies/GLEW/include)
include_directories(Dependencies/GLEW/include/GL)
include_directories(Dependencies/GLFW)
include_directories(Dependencies/GLFW/include)
include_directories(Dependencies/GLFW/include/GLFW)
include_directories(Ruina/res/shaders)


find_library(GLFW_LIB glfw3 Dependencies/GLFW/lib-vc2017)
find_library(GLEW_LIB glew32s Dependencies/GLEW/lib/Release/Win32)
find_library(OPENGL_LIB opengl32 CMAKE_C_COMPILER/lib)

add_executable(Ruina
        Dependencies/GLEW/include/GL/glew.h
        Dependencies/GLEW/include/GL/wglew.h
        Dependencies/GLFW/include/GLFW/glfw3.h
        Dependencies/GLFW/include/GLFW/glfw3native.h
        Ruina/src/Main.cpp
        Ruina/src/Renderer.cpp
        Ruina/src/Renderer.h
        Ruina/src/VertexBuffer.cpp
        Ruina/src/VertexBuffer.h
        Ruina/src/IndexBuffer.cpp
        Ruina/src/IndexBuffer.h
        Ruina/res/shaders/Vertex.shader
        Ruina/res/shaders/Fragment.shader
        )

target_link_libraries(Ruina ${GLFW_LIB} ${GLEW_LIB} ${OPENGL_LIB})

add_definitions(-DGLEW_STATIC)