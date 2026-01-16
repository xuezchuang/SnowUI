#pragma once

#include <cstdint>

namespace SnowUI {

enum class EventType {
    None = 0,
    MouseMove,
    MouseDown,
    MouseUp,
    KeyDown,
    KeyUp,
    Resize,
    Paint,
};

struct Event {
    EventType type;
    int x, y;
    int button;
    int keyCode;
    int width, height;
    
    Event() : type(EventType::None), x(0), y(0), button(0), keyCode(0), width(0), height(0) {}
};

} // namespace SnowUI
