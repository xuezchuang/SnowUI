#pragma once

#include "../Core/Widget.h"

namespace SnowUI
{

	class Label : public Widget
	{
	  public:
		Label();
		virtual ~Label() = default;

		void OnPaint(DrawList& drawList) override;
	};

} // namespace SnowUI
