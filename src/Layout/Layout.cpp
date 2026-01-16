#include "SnowUI/Layout/Layout.h"

namespace SnowUI
{

	Layout::Layout(LayoutType type) : type_(type), spacing_(5)
	{
	}

	void Layout::AddWidget(std::shared_ptr<Widget> widget)
	{
		widgets_.push_back(widget);
	}

	void Layout::DoLayout(const Rect& bounds)
	{
		if (widgets_.empty())
			return;

		if (type_ == LayoutType::Vertical)
		{
			float itemHeight = (bounds.height - spacing_ * (widgets_.size() - 1)) / widgets_.size();
			float y = bounds.y;

			for (auto& widget : widgets_)
			{
				widget->SetBounds(Rect(bounds.x, y, bounds.width, itemHeight));
				y += itemHeight + spacing_;
			}
		}
		else if (type_ == LayoutType::Horizontal)
		{
			float itemWidth = (bounds.width - spacing_ * (widgets_.size() - 1)) / widgets_.size();
			float x = bounds.x;

			for (auto& widget : widgets_)
			{
				widget->SetBounds(Rect(x, bounds.y, itemWidth, bounds.height));
				x += itemWidth + spacing_;
			}
		}
	}

} // namespace SnowUI
