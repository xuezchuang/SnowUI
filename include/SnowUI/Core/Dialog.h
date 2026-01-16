#pragma once

#include "Window.h"

namespace SnowUI
{

	class Dialog : public Window
	{
	  public:
		Dialog();
		virtual ~Dialog() = default;

		virtual void OnInitDialog()
		{
		}
		virtual void OnOK()
		{
		}
		virtual void OnCancel()
		{
		}
	};

} // namespace SnowUI
