cmake_minimum_required(VERSION 3.16)
project(Ruina)

set(CMAKE_CXX_STANDARD 17)

include_directories(Dependencies)
include_directories(Dependencies/GLEW)
include_directories(Dependencies/GLEW/include)
include_directories(Dependencies/GLEW/include/GL)
include_directories(Dependencies/GLEW/lib)
include_directories(Dependencies/GLFW)
include_directories(Dependencies/GLFW/include)
include_directories(Dependencies/GLFW/include/GLFW)
include_directories(Ruina/res/shaders)
include_directories(Ruina/src/gui)
include_directories(Ruina/src/tests)
include_directories(Ruina/src/vendor)
include_directories(Ruina/src/game/ecs)
include_directories(Ruina/src/game/events)
include_directories(Ruina/src/game/renderer)
#include_directories(Ruina/src/vendor/imgui)
#include_directories(Ruina/src/vendor/stb_image)


find_library(GLFW_LIB glfw3 Dependencies/GLFW/lib-vc2017)
find_library(GLEW_LIB glew32s Dependencies/GLEW/lib/Release/Win32)
find_library(OPENGL_LIB opengl32 CMAKE_C_COMPILER/lib)

file(GLOB IMGUI
        Ruina/src/vendor/imgui/*.h
        Ruina/src/vendor/imgui/*.cpp
        )

file(GLOB SOURCE_FILES
        Ruina/src/*.h
        Ruina/src/*.cpp
        )

file(GLOB ECS_FILES
        Ruina/src/game/ecs/*.h
        Ruina/src/game/ecs/*.cpp
        )

file(GLOB EVENT_FILES
        Ruina/src/game/events/*.h
        Ruina/src/game/events/*.cpp
        )

file(GLOB RENDERER_FILES
        Ruina/src/game/renderer/*.h
        Ruina/src/game/renderer/*.cpp
        )

file(GLOB TEST_FILES
        Ruina/src/tests/*.h
        Ruina/src/tests/*.cpp
        )

add_executable(Ruina
        Dependencies/GLEW/include/GL/glew.h
        Dependencies/GLEW/include/GL/wglew.h
        Dependencies/GLFW/include/GLFW/glfw3.h
        Dependencies/GLFW/include/GLFW/glfw3native.h
        Ruina/src/vendor/stb_image/stb_image.h
        Ruina/src/vendor/stb_image/stb_image.cpp
        ${IMGUI}
        ${SOURCE_FILES}
        ${ECS_FILES}
        ${EVENT_FILES}
        ${RENDERER_FILES}
        ${TEST_FILES}
        Ruina/src/gui/GuiManager.cpp Ruina/src/gui/GuiManager.h Ruina/src/gui/IGuiElement.h Ruina/src/gui/GuiText.cpp Ruina/src/gui/Gui.h Ruina/src/gui/GuiButton.cpp Ruina/src/gui/GuiCheckbox.cpp Ruina/src/gui/GuiColorPicker.cpp Ruina/src/gui/GuiTripleSlider.cpp
        Ruina/src/geometry/Vertex.h Ruina/src/geometry/Cube.h
        Ruina/src/geometry/Cube.cpp Ruina/src/game/Game.cpp Ruina/src/game/Game.h Ruina/src/game/Chunk.cpp Ruina/src/game/Chunk.h Ruina/src/game/renderer/Camera.cpp Ruina/src/game/renderer/Camera.h Ruina/src/game/terrain/Block.h
        Ruina/src/game/terrain/ChunkPositionComponent.h Ruina/src/game/terrain/ChunkEntity.h Ruina/src/game/terrain/CubeComponent.h
        Ruina/src/geometry/VertexPNUV.h Ruina/src/geometry/MeshComponent.h Ruina/src/geometry/TextureData.h Ruina/src/tests/TestECSRender.cpp Ruina/src/tests/TestECSRender.h Ruina/src/geometry/MeshComponentFactory.h)

target_link_libraries(Ruina ${GLFW_LIB} ${GLEW_LIB} ${OPENGL_LIB})

add_definitions(-DGLEW_STATIC)