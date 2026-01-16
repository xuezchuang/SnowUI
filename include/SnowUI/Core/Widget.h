#pragma once

#include "Event.h"
#include "../Render/DrawCommand.h"
#include <vector>
#include <memory>
#include <string>

namespace SnowUI
{

	class Widget
	{
	  public:
		Widget();
		virtual ~Widget() = default;

		virtual void OnPaint(DrawList& drawList);
		virtual void OnEvent(const Event& event);
		virtual void SetBounds(const Rect& bounds);

		const Rect& GetBounds() const
		{
			return bounds_;
		}
		void AddChild(std::shared_ptr<Widget> child);
		const std::vector<std::shared_ptr<Widget>>& GetChildren() const
		{
			return children_;
		}

		void SetVisible(bool visible)
		{
			visible_ = visible;
		}
		bool IsVisible() const
		{
			return visible_;
		}

		void SetText(const std::string& text)
		{
			text_ = text;
		}
		const std::string& GetText() const
		{
			return text_;
		}

	  protected:
		Rect bounds_;
		std::vector<std::shared_ptr<Widget>> children_;
		bool visible_;
		std::string text_;
	};

} // namespace SnowUI
