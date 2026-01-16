#pragma once

namespace SnowUI
{

	// GLFW initialization utilities shared across backends
	// These functions manage GLFW reference counting to ensure proper initialization
	// and termination when multiple backend instances are created.

	bool InitializeGLFW();
	void TerminateGLFW();

} // namespace SnowUI
