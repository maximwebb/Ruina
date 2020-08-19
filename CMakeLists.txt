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

add_executable(Ruina
        Dependencies/GLEW/include/GL/glew.h
        Dependencies/GLEW/include/GL/wglew.h
        Dependencies/GLFW/include/GLFW/glfw3.h
        Dependencies/GLFW/include/GLFW/glfw3native.h
        Ruina/src/vendor/stb_image/stb_image.h
        Ruina/src/vendor/stb_image/stb_image.cpp
        ${IMGUI}
        ${SOURCE_FILES}
        Ruina/src/gui/GuiManager.cpp Ruina/src/gui/GuiManager.h Ruina/src/gui/IGuiElement.h Ruina/src/gui/GuiText.cpp Ruina/src/gui/Gui.h Ruina/src/gui/GuiButton.cpp Ruina/src/gui/GuiCheckbox.cpp Ruina/src/gui/GuiColorPicker.cpp Ruina/src/gui/GuiTripleSlider.cpp Ruina/src/tests/Test.h Ruina/src/tests/TestClearColor.cpp Ruina/src/tests/TestClearColor.h Ruina/src/tests/Test.cpp Ruina/src/tests/TestColorQuad.cpp Ruina/src/tests/TestColorQuad.h Ruina/src/tests/TestTexture2D.cpp Ruina/src/tests/TestTexture2D.h Ruina/src/tests/TestSimpleBatchRender.cpp Ruina/src/tests/TestSimpleBatchRender.h Ruina/src/tests/TestColorBatchRender.cpp Ruina/src/tests/TestColorBatchRender.h Ruina/src/tests/TestTextureBatchRender.cpp Ruina/src/tests/TestTextureBatchRender.h Ruina/src/geometry/Vertex.h Ruina/src/geometry/Cube.h Ruina/src/tests/TestColorCube.cpp Ruina/src/tests/TestColorCube.h Ruina/src/geometry/Cube.cpp Ruina/src/game/Game.cpp Ruina/src/game/Game.h Ruina/src/game/Chunk.cpp Ruina/src/game/Chunk.h Ruina/src/tests/TestChunkRender.cpp Ruina/src/tests/TestChunkRender.h Ruina/src/game/Camera.cpp Ruina/src/game/Camera.h Ruina/src/game/events/EventManager.cpp Ruina/src/game/events/EventManager.h Ruina/src/game/events/Event.h Ruina/src/game/ecs/Component.h Ruina/src/game/ecs/System.h Ruina/src/game/ecs/Entity.h Ruina/src/game/ecs/EntityManager.cpp Ruina/src/game/ecs/EntityManager.h Ruina/src/game/ecs/Entity.cpp Ruina/src/game/ecs/ECS.h Ruina/src/tests/TestECS.cpp Ruina/src/tests/TestECS.h Ruina/src/game/ecs/ECSTypes.h Ruina/src/game/ecs/ComponentManager.cpp Ruina/src/game/ecs/ComponentManager.h Ruina/src/game/ecs/Component.cpp Ruina/src/game/ecs/ECSEngine.h Ruina/src/game/ecs/SystemManager.h Ruina/src/game/ecs/SystemManager.cpp Ruina/src/game/ecs/ECSEngine.cpp Ruina/src/game/ecs/System.cpp)

target_link_libraries(Ruina ${GLFW_LIB} ${GLEW_LIB} ${OPENGL_LIB})

add_definitions(-DGLEW_STATIC)