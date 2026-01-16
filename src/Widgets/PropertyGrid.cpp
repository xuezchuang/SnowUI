#include "SnowUI/Widgets/PropertyGrid.h"

namespace SnowUI {

PropertyGrid::PropertyGrid() : selectedIndex_(-1) {
}

void PropertyGrid::OnPaint(DrawList& drawList) {
    if (!visible_) return;
    
    // Draw background
    drawList.AddRect(bounds_, Color(0.25f, 0.25f, 0.25f, 1.0f));
    
    // Draw property items
    float itemHeight = 25.0f;
    float y = bounds_.y + 5.0f;
    
    for (size_t i = 0; i < items_.size(); ++i) {
        const auto& item = items_[i];
        
        // Highlight selected
        if (static_cast<int>(i) == selectedIndex_) {
            Rect selRect(bounds_.x, y, bounds_.width, itemHeight);
            drawList.AddRect(selRect, Color(0.4f, 0.4f, 0.6f, 1.0f));
        }
        
        // Draw name and value
        drawList.AddText(item.name, bounds_.x + 5.0f, y + 5.0f, Color(0.8f, 0.8f, 0.8f, 1.0f));
        drawList.AddText(item.value, bounds_.x + bounds_.width / 2.0f, y + 5.0f, Color(1.0f, 1.0f, 1.0f, 1.0f));
        
        y += itemHeight;
    }
}

void PropertyGrid::OnEvent(const Event& event) {
    if (!visible_) return;
    
    if (event.type == EventType::MouseDown) {
        float mx = static_cast<float>(event.x);
        float my = static_cast<float>(event.y);
        
        if (mx >= bounds_.x && mx <= bounds_.x + bounds_.width &&
            my >= bounds_.y && my <= bounds_.y + bounds_.height) {
            float itemHeight = 25.0f;
            int index = static_cast<int>((my - bounds_.y - 5.0f) / itemHeight);
            if (index >= 0 && index < static_cast<int>(items_.size())) {
                selectedIndex_ = index;
            }
        }
    }
}

void PropertyGrid::AddProperty(const std::string& name, const std::string& value, const std::string& type) {
    PropertyItem item;
    item.name = name;
    item.value = value;
    item.type = type;
    items_.push_back(item);
}

void PropertyGrid::Clear() {
    items_.clear();
    selectedIndex_ = -1;
}

} // namespace SnowUI
