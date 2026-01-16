#include "SnowUI/Core/Window.h"

namespace SnowUI
{

	Window::Window() : backend_(nullptr)
	{
		visible_ = false;
	}

	bool Window::Create(const std::string& title, int width, int height, IRenderBackend* backend)
	{
		title_ = title;
		bounds_ = Rect(0, 0, static_cast<float>(width), static_cast<float>(height));
		backend_ = backend;

		if (backend_ && !backend_->Initialize(width, height))
		{
			return false;
		}

		return true;
	}

	void Window::Show()
	{
		visible_ = true;
	}

	void Window::Update()
	{
		// Update logic here
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

} // namespace SnowUI
