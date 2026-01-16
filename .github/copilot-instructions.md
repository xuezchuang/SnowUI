# GitHub Copilot Instructions for SnowUI

## Project Overview

SnowUI is a cross-platform C++ UI framework with self-built widgets and pluggable rendering backends.

## Architecture Rules

### Rendering Abstraction
- **NEVER** have UI code call OpenGL or Skia directly
- **ALWAYS** use DrawList to accumulate rendering commands
- **ALWAYS** implement rendering in both OpenGLBackend and SkiaBackend

### Code Flow
```
Widget::OnPaint(DrawList&) → DrawList::AddXXX() → Window::Render() → 
IRenderBackend::ExecuteDrawList() → OpenGL/Skia calls
```

## Key Classes

- **Widget**: Base class for UI elements. Override `OnPaint()` for rendering, `OnEvent()` for input
- **Window**: Top-level container. Owns IRenderBackend instance
- **DrawList**: Command buffer. UI adds commands like `AddRect()`, `AddText()`
- **IRenderBackend**: Interface for backends. `ExecuteDrawList()` translates commands

## Coding Standards

- C++17 required
- Namespace: `SnowUI`
- Include guards: `#pragma once`
- Member variables: trailing underscore (e.g., `visible_`)
- No external UI library dependencies
- Cross-platform code only

## Common Patterns

### Creating a Widget
```cpp
class MyWidget : public Widget {
    void OnPaint(DrawList& drawList) override {
        drawList.AddRect(bounds_, Color(1, 0, 0, 1)); // Red rectangle
    }
};
```

### Adding to DrawList
- `AddClear(color)` - Clear screen
- `AddRect(rect, color)` - Draw filled rectangle
- `AddText(text, x, y, color)` - Draw text
- `AddLine(x1, y1, x2, y2, color)` - Draw line

### Event Handling
```cpp
void OnEvent(const Event& event) override {
    if (event.type == EventType::MouseDown) {
        // Handle click
    }
}
```

## Build Commands

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## Important Notes

- Current implementation is a buildable skeleton
- OpenGL/Skia backends are stubs (print to console)
- No actual window creation yet (future: GLFW or SDL)
- Maintain backend independence in all UI code
