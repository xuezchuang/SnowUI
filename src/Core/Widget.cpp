#include "SnowUI/Core/Widget.h"

namespace SnowUI {

Widget::Widget() : visible_(true) {
    bounds_ = Rect(0, 0, 100, 100);
}

void Widget::OnPaint(DrawList& drawList) {
    if (!visible_) return;
    
    // Default paint: draw border
    drawList.AddRect(bounds_, Color(0.5f, 0.5f, 0.5f, 1.0f));
    
    // Paint children
    for (auto& child : children_) {
        child->OnPaint(drawList);
    }
}

void Widget::OnEvent(const Event& event) {
    // Forward events to children
    for (auto& child : children_) {
        child->OnEvent(event);
    }
}

void Widget::SetBounds(const Rect& bounds) {
    bounds_ = bounds;
}

void Widget::AddChild(std::shared_ptr<Widget> child) {
    children_.push_back(child);
}

} // namespace SnowUI
