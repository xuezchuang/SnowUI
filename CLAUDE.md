# CLAUDE.md

## Instructions for Claude AI

This document provides specific guidance for Claude AI when working with the SnowUI codebase.

### Project Context

SnowUI is a cross-platform C++ UI framework with a self-built widget system and pluggable rendering backends (OpenGL and Skia). The architecture emphasizes separation of UI logic from rendering through an abstraction layer.

### Understanding the Codebase

#### The Rendering Abstraction

The most important architectural decision is the rendering abstraction:

```
UI Widget → DrawList → IRenderBackend → OpenGL/Skia
```

**Never** suggest that UI code should call OpenGL or Skia functions directly. All rendering must go through:
1. Widget creates DrawCommands via DrawList API
2. DrawList accumulates commands
3. Window passes DrawList to IRenderBackend
4. Backend translates commands to GL/Skia calls

#### Key Classes

- **Widget**: Base for all UI elements. Override `OnPaint()` and `OnEvent()`
- **Window**: Top-level container, owns the render backend
- **DrawList**: Command buffer for rendering operations
- **IRenderBackend**: Interface that OpenGL/Skia backends implement

### Common Tasks

#### Adding a New Widget

```cpp
class MyWidget : public Widget {
public:
    void OnPaint(DrawList& drawList) override {
        // Add draw commands - NEVER call GL/Skia directly
        drawList.AddRect(bounds_, Color(1, 0, 0, 1));
    }
    
    void OnEvent(const Event& event) override {
        // Handle user input
    }
};
```

#### Extending DrawCommand Types

If you need a new primitive:
1. Add to `DrawCommandType` enum
2. Add parameters to `DrawCommand` struct
3. Add helper method to `DrawList`
4. Implement in both OpenGLBackend and SkiaBackend

### Build and Test

Always verify changes compile:
```bash
mkdir -p build && cd build
cmake ..
cmake --build .
```

Run demos to test:
```bash
./demos/demo_property_grid/demo_property_grid
./demos/demo_soil_dialog/demo_soil_dialog
```

### Code Conventions

1. **Namespaces**: All code in `namespace SnowUI`
2. **Headers**: Use `#pragma once` for include guards
3. **Includes**: Relative to include/ directory (e.g., `#include "SnowUI/Core/Widget.h"`)
4. **Member Variables**: Use trailing underscore (e.g., `width_`)
5. **Getters/Setters**: Use Get/Set prefix

### Important Constraints

- **No Direct Rendering**: UI code must not include or call OpenGL/Skia
- **Backend Swappability**: Any feature must work with both backends
- **Self-contained**: Don't add dependencies on other UI libraries
- **Cross-platform**: Avoid platform-specific code in core UI

### When Modifying Core

- Keep Widget interface minimal and stable
- Maintain backward compatibility in DrawCommand
- Document any changes to IRenderBackend interface
- Update both backend implementations together

### Current Limitations (Stub Implementations)

The current codebase is a buildable skeleton:
- OpenGL and Skia backends are stubs (no actual rendering)
- No platform window creation (no GLFW/SDL integration yet)
- No font rendering system
- No image loading
- No event input from OS

When implementing these, maintain the architecture:
- Platform code should be isolated
- Backends handle their own context setup
- UI layer remains backend-agnostic
