#include "SnowUI/Core/Window.h"
#include <iostream>

namespace SnowUI
{

	Window::Window() : backend_(nullptr), shouldClose_(false), hasWindow_(false)
	{
		visible_ = false;
	}

	bool Window::Create(const std::string& title, int width, int height, IRenderBackend* backend)
	{
		title_ = title;
		bounds_ = Rect(0, 0, static_cast<float>(width), static_cast<float>(height));
		backend_ = backend;
		hasWindow_ = false;

		if (backend_)
		{
			// First create the window (which sets up the GL context)
			hasWindow_ = backend_->CreateWindow(title, width, height);
			if (!hasWindow_)
			{
				std::cerr << "Window: Failed to create platform window - will run in headless mode" << std::endl;
			}

			// Initialize the rendering context regardless of window creation
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
		// If no window was created, exit immediately
		if (!hasWindow_)
		{
			return true;
		}

		if (backend_)
		{
			return shouldClose_ || backend_->ShouldClose();
		}
		return shouldClose_;
	}

	void Window::Update()
	{
		// Poll for events only if we have a window
		if (backend_ && hasWindow_)
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

		if (!hasWindow_)
		{
			std::cout << "Window: No platform window available - rendering single frame" << std::endl;
			Render();
			return;
		}

		std::cout << "Window: Starting main loop" << std::endl;

		while (!ShouldClose())
		{
			Update();
			Render();
		}

		std::cout << "Window: Main loop ended" << std::endl;
	}

} // namespace SnowUI
