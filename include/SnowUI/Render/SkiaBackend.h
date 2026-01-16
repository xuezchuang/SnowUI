#pragma once

#include "SnowUI/Render/IRenderBackend.h"

namespace SnowUI
{

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

	  private:
		int width_;
		int height_;
		bool initialized_;
	};

} // namespace SnowUI
