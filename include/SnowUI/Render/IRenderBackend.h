#pragma once

#include "DrawCommand.h"
#include <memory>

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
	};

} // namespace SnowUI
