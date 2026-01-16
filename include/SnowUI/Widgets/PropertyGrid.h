#pragma once

#include "../Core/Widget.h"
#include <string>
#include <vector>

namespace SnowUI {

struct PropertyItem {
    std::string name;
    std::string value;
    std::string type;
};

class PropertyGrid : public Widget {
public:
    PropertyGrid();
    virtual ~PropertyGrid() = default;
    
    void OnPaint(DrawList& drawList) override;
    void OnEvent(const Event& event) override;
    
    void AddProperty(const std::string& name, const std::string& value, const std::string& type = "string");
    void Clear();
    
private:
    std::vector<PropertyItem> items_;
    int selectedIndex_;
};

} // namespace SnowUI
