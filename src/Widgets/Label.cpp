#include "SnowUI/Widgets/Label.h"

namespace SnowUI
{

	Label::Label()
	{
	}

	void Label::OnPaint(DrawList& drawList)
	{
		if (!visible_)
			return;

		if (!text_.empty())
		{
			drawList.AddText(text_, bounds_.x, bounds_.y, Color(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

} // namespace SnowUI
