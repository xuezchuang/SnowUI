#pragma once

#include "DrawCommand.h"
#include <memory>
#include <string>

namespace SnowUI
{

	class IRenderBackend
	{
	  public:
		virtual ~IRenderBackend() = default;

		virtual bool Initialize(int width, int height) = 0;
		virtual void Shutdown() = 0;
		virtual void BeginFrame() = 0;
		virtual void EndFrame() = 0;
		virtual void ExecuteDrawList(const DrawList& drawList) = 0;
		virtual void Resize(int width, int height) = 0;

		// Window management - implemented by backends that support windowing
		virtual bool CreateWindow(const std::string& title, int width, int height)
		{
			(void)title;
			(void)width;
			(void)height;
			return false;
		}
		virtual void DestroyWindow()
		{
		}
		virtual bool ShouldClose()
		{
			return true;
		}
		virtual void PollEvents()
		{
		}
		virtual void SwapBuffers()
		{
		}
		virtual void* GetNativeWindowHandle()
		{
			return nullptr;
		}
	};

} // namespace SnowUI
