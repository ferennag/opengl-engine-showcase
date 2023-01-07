cmake_minimum_required(VERSION 3.25)
project(engine_showcase)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory(lib/qtimgui)
include_directories(lib/qtimgui)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        OpenGL
        REQUIRED)

find_package(ImGui REQUIRED)

add_executable(engine_showcase src/main.cpp src/ui/MainWindow.cpp src/ui/MainWindow.h src/ui/MainWindow.ui src/ui/GLRendererWindow.cpp src/ui/GLRendererWindow.h src/engine/World.cpp src/engine/World.h src/engine/camera/Camera.cpp src/engine/camera/Camera.h src/engine/demo-objects/Triangle.cpp src/engine/demo-objects/Triangle.h src/engine/demo-objects/Cube.cpp src/engine/demo-objects/Cube.h src/engine/demo-objects/DemoObject.h src/engine/texture/TextureManager.cpp src/engine/texture/TextureManager.h src/engine/lighting/Material.h src/engine/lighting/DirectionalLight.h src/engine/lighting/PointLight.h src/engine/shader/ShaderManager.cpp src/engine/shader/ShaderManager.h src/engine/shader/ShaderCompilationException.h src/engine/shader/ShaderProgramCompilationException.h src/debug/DebugWindow.cpp src/debug/DebugWindow.h)
target_link_libraries(engine_showcase
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt6::OpenGL
        qt_imgui_widgets)

if(UNIX)
    add_definitions(-g -O2 -std=c++20 -Wall -Wextra)
endif()