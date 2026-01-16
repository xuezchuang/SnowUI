#pragma once

#include "../Core/Widget.h"
#include <memory>

namespace SnowUI {

enum class LayoutType {
    Vertical,
    Horizontal,
    Grid,
};

class Layout {
public:
    Layout(LayoutType type);
    virtual ~Layout() = default;
    
    void AddWidget(std::shared_ptr<Widget> widget);
    void DoLayout(const Rect& bounds);
    
private:
    LayoutType type_;
    std::vector<std::shared_ptr<Widget>> widgets_;
    int spacing_;
};

} // namespace SnowUI
