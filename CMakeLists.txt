cmake_minimum_required(VERSION 3.15)
project(SnowUI VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
option(SNOWUI_BUILD_DEMOS "Build demo applications" ON)

# SnowUI Library
add_library(SnowUI STATIC
    src/Core/Widget.cpp
    src/Core/Window.cpp
    src/Core/Dialog.cpp
    src/Widgets/Button.cpp
    src/Widgets/Label.cpp
    src/Widgets/PropertyGrid.cpp
    src/Layout/Layout.cpp
    src/Render/OpenGLBackend.cpp
    src/Render/SkiaBackend.cpp
)

target_include_directories(SnowUI PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Demos
if(SNOWUI_BUILD_DEMOS)
    add_subdirectory(demos/demo_property_grid)
    add_subdirectory(demos/demo_soil_dialog)
endif()

# Installation
install(TARGETS SnowUI
    EXPORT SnowUITargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/SnowUI
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
