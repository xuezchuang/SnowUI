#pragma once

#include "Widget.h"
#include "../Render/IRenderBackend.h"
#include <memory>

namespace SnowUI
{

	class Window : public Widget
	{
	  public:
		Window();
		virtual ~Window() = default;

		bool Create(const std::string& title, int width, int height, IRenderBackend* backend);
		void Show();
		void Update();
		void Render();

		void SetTitle(const std::string& title)
		{
			title_ = title;
		}
		const std::string& GetTitle() const
		{
			return title_;
		}

		IRenderBackend* GetRenderBackend()
		{
			return backend_;
		}

	  protected:
		std::string title_;
		IRenderBackend* backend_;
		DrawList drawList_;
	};

} // namespace SnowUI
