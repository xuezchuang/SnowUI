#pragma once

#include "Widget.h"
#include "../Render/IRenderBackend.h"
#include <memory>
#include <functional>

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
		void Close();

		// Main event loop - runs until window is closed
		void Run();

		// Check if window should close
		bool ShouldClose() const;

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

		// Event callbacks
		void SetOnClose(std::function<void()> callback)
		{
			onClose_ = callback;
		}

	  protected:
		std::string title_;
		IRenderBackend* backend_;
		DrawList drawList_;
		bool shouldClose_;
		std::function<void()> onClose_;
	};

} // namespace SnowUI
