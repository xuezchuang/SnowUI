#pragma once

#include "SnowUI/Render/IRenderBackend.h"
#include <string>

namespace SnowUI
{

	// SkiaBackend provides a Skia-based rendering implementation
	// Note: Full Skia integration requires the Skia library to be available.
	// This implementation provides a fallback software rendering mode when Skia is not available.
	class SkiaBackend : public IRenderBackend
	{
	  public:
		SkiaBackend();
		virtual ~SkiaBackend();

		bool Initialize(int width, int height) override;
		void Shutdown() override;
		void BeginFrame() override;
		void EndFrame() override;
		void ExecuteDrawList(const DrawList& drawList) override;
		void Resize(int width, int height) override;

		// Window management (uses GLFW as Skia GPU context requires OpenGL)
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
		void* window_;	 // GLFW window handle for Skia GPU context
		bool ownsWindow_;
	};

} // namespace SnowUI
