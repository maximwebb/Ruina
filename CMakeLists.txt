cmake_minimum_required(VERSION 3.16)
project(Ruina)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-9")


include_directories(Dependencies)
include_directories(Dependencies/GLEW)
include_directories(Dependencies/GLEW/include)
include_directories(Dependencies/GLEW/include/GL)
include_directories(Dependencies/GLEW/lib)
include_directories(Dependencies/GLFW)
include_directories(Dependencies/GLFW/include)
include_directories(Dependencies/GLFW/include/GLFW)
include_directories(Ruina/res/shaders)
include_directories(Ruina/src)
include_directories(Ruina/src/gui)
include_directories(Ruina/src/tests)
include_directories(Ruina/src/vendor)
include_directories(Ruina/src/game/ecs)
include_directories(Ruina/src/game/geometry)
include_directories(Ruina/src/game/physics)
include_directories(Ruina/src/game/renderer)
include_directories(/usr/include/GL)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

find_library(GLFW_LIB glfw /usr/local/lib/libglfw.so.3.3)
find_library(GLEW_LIB libGLEW Dependencies/GLEW/lib/libGLEW.so.2.1.0)

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

file(GLOB GEOMETRY_FILES
        Ruina/src/game/geometry/*.h
        Ruina/src/game/geometry/*.cpp
        )

file(GLOB PHYSICS_FILES
        Ruina/src/game/physics/*.h
        Ruina/src/game/physics/*.cpp
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
        Dependencies/GLFW/include/GLFW/glfw3.h
        Dependencies/GLFW/include/GLFW/glfw3native.h
        Ruina/src/vendor/stb_image/stb_image.h
        Ruina/src/vendor/stb_image/stb_image.cpp
        ${IMGUI}
        ${SOURCE_FILES}
        ${ECS_FILES}
        ${GEOMETRY_FILES}
        ${PHYSICS_FILES}
        ${RENDERER_FILES}
        ${TEST_FILES}
        Ruina/src/gui/GuiManager.cpp Ruina/src/gui/GuiManager.h Ruina/src/gui/IGuiElement.h Ruina/src/gui/GuiText.cpp
        Ruina/src/gui/Gui.h Ruina/src/gui/GuiButton.cpp Ruina/src/gui/GuiCheckbox.cpp Ruina/src/gui/GuiColorPicker.cpp
        Ruina/src/gui/GuiTripleSlider.cpp Ruina/src/game/ecs/System.cpp Ruina/src/game/ecs/System.h Ruina/src/game/ecs/Entity.h Ruina/src/game/ecs/Component.h
        Ruina/src/game/ecs/Manager.h Ruina/src/game/ecs/Manager.cpp Ruina/src/game/ecs/Group.h Ruina/src/game/ecs/Event.h)

target_link_libraries(Ruina ${GLEW_LIBRARIES} ${GLFW_LIB} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

add_definitions(-DGLEW_STATIC)