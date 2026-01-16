#pragma once

#include "SnowUI/Render/IRenderBackend.h"
#include <string>

namespace SnowUI
{

	class OpenGLBackend : public IRenderBackend
	{
	  public:
		OpenGLBackend();
		virtual ~OpenGLBackend();

		bool Initialize(int width, int height) override;
		void Shutdown() override;
		void BeginFrame() override;
		void EndFrame() override;
		void ExecuteDrawList(const DrawList& drawList) override;
		void Resize(int width, int height) override;

		// Window management
		bool CreateWindow(const std::string& title, int width, int height) override;
		void DestroyWindow() override;
		bool ShouldClose() override;
		void PollEvents() override;
		void SwapBuffers() override;
		void* GetNativeWindowHandle() override;

	  private:
		void DrawRect(const Rect& rect, const Color& color);
		void DrawLine(float x1, float y1, float x2, float y2, const Color& color);
		void DrawText(const std::string& text, float x, float y, const Color& color);
		void ClearScreen(const Color& color);

		int width_;
		int height_;
		bool initialized_;
		void* window_;	 // GLFW window handle
		bool ownsWindow_; // Whether this backend created the window
	};

} // namespace SnowUI
