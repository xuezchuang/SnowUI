#pragma once

#include "../Core/Widget.h"

namespace SnowUI {

class Button : public Widget {
public:
    Button();
    virtual ~Button() = default;
    
    void OnPaint(DrawList& drawList) override;
    void OnEvent(const Event& event) override;
    
    void SetOnClick(void (*callback)()) { onClick_ = callback; }
    
private:
    void (*onClick_)();
    bool isPressed_;
};

} // namespace SnowUI
