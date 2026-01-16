#include "SnowUI/Core/Window.h"
#include <iostream>

namespace SnowUI
{

	Window::Window() : backend_(nullptr), shouldClose_(false)
	{
		visible_ = false;
	}

	bool Window::Create(const std::string& title, int width, int height, IRenderBackend* backend)
	{
		title_ = title;
		bounds_ = Rect(0, 0, static_cast<float>(width), static_cast<float>(height));
		backend_ = backend;

		if (backend_)
		{
			// First create the window (which sets up the GL context)
			if (!backend_->CreateWindow(title, width, height))
			{
				std::cerr << "Window: Failed to create platform window" << std::endl;
				// Fall back to non-windowed mode
			}

			// Then initialize the rendering context
			if (!backend_->Initialize(width, height))
			{
				return false;
			}
		}

		return true;
	}

	void Window::Show()
	{
		visible_ = true;
	}

	void Window::Close()
	{
		shouldClose_ = true;
		if (onClose_)
		{
			onClose_();
		}
	}

	bool Window::ShouldClose() const
	{
		if (backend_)
		{
			return shouldClose_ || backend_->ShouldClose();
		}
		return shouldClose_;
	}

	void Window::Update()
	{
		// Poll for events
		if (backend_)
		{
			backend_->PollEvents();
		}
	}

	void Window::Render()
	{
		if (!visible_ || !backend_)
			return;

		backend_->BeginFrame();

		drawList_.Clear();
		drawList_.AddClear(Color(0.2f, 0.2f, 0.2f, 1.0f));

		OnPaint(drawList_);

		backend_->ExecuteDrawList(drawList_);
		backend_->EndFrame();
	}

	void Window::Run()
	{
		Show();

		std::cout << "Window: Starting main loop" << std::endl;

		while (!ShouldClose())
		{
			Update();
			Render();
		}

		std::cout << "Window: Main loop ended" << std::endl;
	}

} // namespace SnowUI
