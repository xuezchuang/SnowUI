#include "SnowUI/Widgets/Button.h"

namespace SnowUI {

Button::Button() : onClick_(nullptr), isPressed_(false) {
}

void Button::OnPaint(DrawList& drawList) {
    if (!visible_) return;
    
    Color bgColor = isPressed_ ? Color(0.4f, 0.4f, 0.4f, 1.0f) : Color(0.6f, 0.6f, 0.6f, 1.0f);
    drawList.AddRect(bounds_, bgColor);
    
    if (!text_.empty()) {
        float centerX = bounds_.x + bounds_.width / 2.0f;
        float centerY = bounds_.y + bounds_.height / 2.0f;
        drawList.AddText(text_, centerX, centerY, Color(1.0f, 1.0f, 1.0f, 1.0f));
    }
}

void Button::OnEvent(const Event& event) {
    if (!visible_) return;
    
    if (event.type == EventType::MouseDown) {
        float mx = static_cast<float>(event.x);
        float my = static_cast<float>(event.y);
        if (mx >= bounds_.x && mx <= bounds_.x + bounds_.width &&
            my >= bounds_.y && my <= bounds_.y + bounds_.height) {
            isPressed_ = true;
        }
    } else if (event.type == EventType::MouseUp) {
        if (isPressed_ && onClick_) {
            onClick_();
        }
        isPressed_ = false;
    }
}

} // namespace SnowUI
