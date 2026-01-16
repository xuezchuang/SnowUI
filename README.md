# SnowUI

Cross-platform C++ UI framework inspired by MFC/BCG. Self-built widgets and message-driven architecture. Rendering backends: OpenGL + Skia. Includes demos like PropertyGrid and engineering parameter dialogs.

## Features

- **Self-built UI System**: All windows, dialogs, widgets, events, and layouts implemented from scratch
- **Backend Abstraction**: UI code never calls OpenGL/Skia directly
- **Swappable Rendering**: Support for multiple rendering backends (OpenGL, Skia) via `IRenderBackend` interface
- **Cross-platform**: Designed for Windows, Linux, and macOS
- **MFC/BCG Inspired**: Familiar architecture for developers coming from Windows MFC/BCG frameworks

## Architecture

### Core Concepts

```
Widget → DrawList → IRenderBackend → OpenGL/Skia
```

The framework uses a command pattern for rendering:
1. UI widgets generate drawing commands via `DrawList`
2. Commands are queued without executing
3. Render backend translates commands to specific graphics API calls
4. Backends are hot-swappable without changing UI code

### Directory Structure

```
SnowUI/
├── include/SnowUI/          # Public headers
│   ├── Core/                # Core UI classes (Widget, Window, Dialog, Event)
│   ├── Render/              # Rendering abstraction (IRenderBackend, DrawCommand)
│   ├── Widgets/             # UI widgets (Button, Label, PropertyGrid)
│   └── Layout/              # Layout managers
├── src/                     # Implementation files
├── demos/                   # Demo applications
│   ├── demo_property_grid/  # Property grid demo
│   └── demo_soil_dialog/    # Soil parameter dialog demo
├── AGENTS.md                # Instructions for AI agents
├── CLAUDE.md                # Detailed guidance for Claude AI
└── .github/copilot-instructions.md  # GitHub Copilot instructions
```

## Building

### Requirements

- CMake 3.15 or higher
- C++17 compatible compiler (GCC, Clang, MSVC)

### Build Steps

```bash
# Create build directory
mkdir build
cd build

# Configure
cmake ..

# Build
cmake --build .

# Or with parallel jobs
cmake --build . -j$(nproc)
```

## Running Demos

### Property Grid Demo

Demonstrates a property grid widget with various property types:

```bash
./build/demos/demo_property_grid/demo_property_grid
```

### Soil Parameter Dialog

Shows an engineering parameter input dialog for soil properties:

```bash
./build/demos/demo_soil_dialog/demo_soil_dialog
```

## Quick Start

### Creating a Simple Window

```cpp
#include "SnowUI/Core/Window.h"
#include "SnowUI/Render/OpenGLBackend.h"

using namespace SnowUI;

int main() {
    OpenGLBackend backend;
    auto window = std::make_shared<Window>();
    window->Create("My Window", 800, 600, &backend);
    window->Show();
    window->Render();
    return 0;
}
```

### Creating a Custom Widget

```cpp
#include "SnowUI/Core/Widget.h"

class MyWidget : public SnowUI::Widget {
public:
    void OnPaint(SnowUI::DrawList& drawList) override {
        // Draw a red rectangle
        drawList.AddRect(bounds_, SnowUI::Color(1.0f, 0.0f, 0.0f, 1.0f));
        
        // Draw text
        drawList.AddText("Hello SnowUI!", bounds_.x + 10, bounds_.y + 10, 
                         SnowUI::Color(1.0f, 1.0f, 1.0f, 1.0f));
    }
    
    void OnEvent(const SnowUI::Event& event) override {
        if (event.type == SnowUI::EventType::MouseDown) {
            // Handle mouse click
        }
    }
};
```

## Documentation

- **AGENTS.md**: Instructions for AI agents working on the codebase
- **CLAUDE.md**: Detailed guidance for Claude AI
- **.github/copilot-instructions.md**: GitHub Copilot instructions

## Current Status

This is a **minimal buildable skeleton**. The framework includes:

✅ Core architecture defined  
✅ IRenderBackend abstraction layer  
✅ DrawCommand/DrawList pattern  
✅ Basic widgets (Button, Label, PropertyGrid)  
✅ Layout manager  
✅ Two working demos  
✅ CMake build system  

### Known Limitations (Stub Implementations)

⚠️ OpenGL and Skia backends are stubs (console output only)  
⚠️ No actual window creation (no GLFW/SDL integration)  
⚠️ No font rendering system  
⚠️ No image loading  
⚠️ No OS event input  

These will be implemented while maintaining the architecture and backend independence.

## Design Principles

1. **Separation of Concerns**: UI logic completely separate from rendering
2. **Backend Independence**: All rendering through DrawList → IRenderBackend
3. **No Direct GL/Skia Calls**: UI widgets only add commands to DrawList
4. **Message-Driven**: Events flow from window → widgets through OnEvent()

## Contributing

When contributing, please:
- Maintain backend independence in UI code
- Never call OpenGL/Skia directly from UI widgets
- Implement features in both OpenGL and Skia backends
- Follow C++17 standards
- Use existing code style (see documentation files)

## License

[License information to be added]
