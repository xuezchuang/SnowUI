# AGENTS.md

## GitHub Copilot Agents Instructions

This document contains instructions for GitHub Copilot agents working on the SnowUI framework.

### Project Overview

SnowUI is a cross-platform C++ UI framework inspired by MFC/BCG with a self-built UI system. The framework focuses on:

- **Self-built UI**: All windows, dialogs, widgets, events, and layouts are implemented from scratch
- **Render Backend Abstraction**: UI code never calls OpenGL/Skia directly
- **Swappable Backends**: Rendering is done through IRenderBackend interface with DrawCommand/DrawList pattern
- **Cross-platform**: Designed to work on Windows, Linux, and macOS

### Architecture

#### Core Components

1. **Core** (`include/SnowUI/Core/`)
   - `Widget.h/cpp`: Base class for all UI elements
   - `Window.h/cpp`: Top-level window implementation
   - `Dialog.h/cpp`: Dialog box implementation
   - `Event.h`: Event system for user input

2. **Render** (`include/SnowUI/Render/`)
   - `IRenderBackend.h`: Interface for render backends
   - `DrawCommand.h`: Command pattern for rendering operations
   - `OpenGLBackend.h/cpp`: OpenGL rendering implementation
   - `SkiaBackend.h/cpp`: Skia rendering implementation

3. **Widgets** (`include/SnowUI/Widgets/`)
   - `Button.h/cpp`: Button widget
   - `Label.h/cpp`: Text label widget
   - `PropertyGrid.h/cpp`: Property grid for key-value editing

4. **Layout** (`include/SnowUI/Layout/`)
   - `Layout.h/cpp`: Layout manager for automatic widget positioning

### Key Design Principles

1. **Separation of Concerns**: UI logic is completely separate from rendering
2. **Backend Independence**: All rendering goes through DrawList → IRenderBackend
3. **No Direct GL/Skia Calls**: UI widgets only add commands to DrawList
4. **Message-Driven**: Events flow from window → widgets through OnEvent()

### Building the Project

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Running Demos

```bash
./build/demos/demo_property_grid/demo_property_grid
./build/demos/demo_soil_dialog/demo_soil_dialog
```

### Adding New Widgets

1. Inherit from `Widget` class
2. Override `OnPaint(DrawList&)` to add draw commands
3. Override `OnEvent(const Event&)` for user interaction
4. Never call OpenGL/Skia directly - only use DrawList API

### Adding New Backends

1. Inherit from `IRenderBackend`
2. Implement all virtual methods
3. In `ExecuteDrawList()`, translate DrawCommands to backend-specific calls
4. Backend should handle window creation and context management

### Code Style

- Use C++17 features
- Follow standard C++ naming conventions
- Keep headers minimal and include only what's needed
- Document complex logic with comments
- Prefer composition over inheritance
