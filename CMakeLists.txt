cmake_minimum_required(VERSION 3.15)
project(SnowUI VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
option(SNOWUI_BUILD_DEMOS "Build demo applications" ON)
option(SNOWUI_USE_OPENGL "Build with OpenGL backend" ON)
option(SNOWUI_USE_SKIA "Build with Skia backend" OFF)
option(SNOWUI_USE_GLFW "Use GLFW for window management" ON)
option(SNOWUI_USE_SDL "Use SDL for window management" OFF)

# Find required packages
if(SNOWUI_USE_OPENGL)
    find_package(OpenGL)
    if(OPENGL_FOUND)
        message(STATUS "OpenGL found: ${OPENGL_LIBRARIES}")
    else()
        message(WARNING "OpenGL not found, OpenGL backend will be stub-only")
    endif()
endif()

if(SNOWUI_USE_GLFW)
    find_package(glfw3)
    if(glfw3_FOUND)
        message(STATUS "GLFW3 found")
    else()
        message(WARNING "GLFW3 not found, window creation will be stub-only")
    endif()
endif()

if(SNOWUI_USE_SDL)
    find_package(SDL2)
    if(SDL2_FOUND)
        message(STATUS "SDL2 found")
    else()
        message(WARNING "SDL2 not found, window creation will be stub-only")
    endif()
endif()

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

# Link libraries based on options
if(SNOWUI_USE_OPENGL AND OPENGL_FOUND)
    target_link_libraries(SnowUI PUBLIC ${OPENGL_LIBRARIES})
    target_compile_definitions(SnowUI PUBLIC SNOWUI_OPENGL_ENABLED)
endif()

if(SNOWUI_USE_GLFW AND glfw3_FOUND)
    target_link_libraries(SnowUI PUBLIC glfw)
    target_compile_definitions(SnowUI PUBLIC SNOWUI_GLFW_ENABLED)
endif()

if(SNOWUI_USE_SDL AND SDL2_FOUND)
    target_link_libraries(SnowUI PUBLIC SDL2::SDL2)
    target_compile_definitions(SnowUI PUBLIC SNOWUI_SDL_ENABLED)
endif()

# Platform-specific libraries
if(WIN32)
    # Windows-specific libraries
    target_compile_definitions(SnowUI PUBLIC SNOWUI_PLATFORM_WINDOWS)
elseif(APPLE)
    # macOS-specific libraries
    target_compile_definitions(SnowUI PUBLIC SNOWUI_PLATFORM_MACOS)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    if(COCOA_LIBRARY AND IOKIT_LIBRARY AND COREVIDEO_LIBRARY)
        target_link_libraries(SnowUI PUBLIC ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
    endif()
elseif(UNIX)
    # Linux-specific libraries
    target_compile_definitions(SnowUI PUBLIC SNOWUI_PLATFORM_LINUX)
    find_package(X11)
    if(X11_FOUND)
        target_link_libraries(SnowUI PUBLIC ${X11_LIBRARIES})
    endif()
endif()

# Compiler warnings
if(MSVC)
    target_compile_options(SnowUI PRIVATE /W4)
else()
    target_compile_options(SnowUI PRIVATE -Wall -Wextra -Wpedantic)
endif()

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

# Export configuration
install(EXPORT SnowUITargets
    FILE SnowUITargets.cmake
    NAMESPACE SnowUI::
    DESTINATION lib/cmake/SnowUI
)

# Create package config file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/SnowUIConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/SnowUIConfigVersion.cmake"
    DESTINATION lib/cmake/SnowUI
)
