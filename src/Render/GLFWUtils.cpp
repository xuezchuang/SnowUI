#include <mutex>

#ifdef SNOWUI_GLFW_ENABLED
#include <GLFW/glfw3.h>
#endif

namespace SnowUI
{

	// Global GLFW initialization tracking (shared across all backends)
	static int g_glfwRefCount = 0;
	static std::mutex g_glfwMutex;

	bool InitializeGLFW()
	{
#ifdef SNOWUI_GLFW_ENABLED
		std::lock_guard<std::mutex> lock(g_glfwMutex);
		if (g_glfwRefCount == 0)
		{
			if (!glfwInit())
			{
				return false;
			}
		}
		g_glfwRefCount++;
		return true;
#else
		return false;
#endif
	}

	void TerminateGLFW()
	{
#ifdef SNOWUI_GLFW_ENABLED
		std::lock_guard<std::mutex> lock(g_glfwMutex);
		if (g_glfwRefCount > 0)
		{
			g_glfwRefCount--;
			if (g_glfwRefCount == 0)
			{
				glfwTerminate();
			}
		}
#endif
	}

} // namespace SnowUI
