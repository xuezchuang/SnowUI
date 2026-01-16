#include "SnowUI/Render/SkiaBackend.h"
#include "SnowUI/Render/GLFWUtils.h"
#include <iostream>
#include <cstring>

// Skia backend implementation
// Note: Full Skia support requires installing the Skia library.
// This implementation provides a fallback using OpenGL when Skia is not available,
// so demos can still run and display windows.

#ifdef SNOWUI_GLFW_ENABLED
#include <GLFW/glfw3.h>
#endif

#ifdef SNOWUI_OPENGL_ENABLED
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#endif

namespace SnowUI
{

	// Text rendering constants (placeholder for real font system)
	static constexpr float kDefaultCharWidth = 7.0f;
	static constexpr float kDefaultCharHeight = 12.0f;

	SkiaBackend::SkiaBackend() : width_(0), height_(0), initialized_(false), window_(nullptr), ownsWindow_(false)
	{
	}

	SkiaBackend::~SkiaBackend()
	{
		Shutdown();
	}

	bool SkiaBackend::CreateWindow(const std::string& title, int width, int height)
	{
#ifdef SNOWUI_GLFW_ENABLED
		if (!InitializeGLFW())
		{
			std::cerr << "Skia Backend: Failed to initialize GLFW" << std::endl;
			return false;
		}

		// Set OpenGL hints
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

		GLFWwindow* glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (!glfwWindow)
		{
			std::cerr << "Skia Backend: Failed to create GLFW window" << std::endl;
			TerminateGLFW();
			return false;
		}

		glfwMakeContextCurrent(glfwWindow);
		glfwSwapInterval(1);

		window_ = glfwWindow;
		ownsWindow_ = true;
		width_ = width;
		height_ = height;

		std::cout << "Skia Backend: Window created (" << width << "x" << height
				  << ") [Using OpenGL fallback]" << std::endl;
		return true;
#else
		(void)title;
		(void)width;
		(void)height;
		std::cerr << "Skia Backend: GLFW not available, cannot create window" << std::endl;
		return false;
#endif
	}

	void SkiaBackend::DestroyWindow()
	{
#ifdef SNOWUI_GLFW_ENABLED
		if (window_ && ownsWindow_)
		{
			glfwDestroyWindow(static_cast<GLFWwindow*>(window_));
			window_ = nullptr;
			ownsWindow_ = false;
			TerminateGLFW();
		}
#endif
	}

	bool SkiaBackend::ShouldClose()
	{
#ifdef SNOWUI_GLFW_ENABLED
		if (window_)
		{
			return glfwWindowShouldClose(static_cast<GLFWwindow*>(window_));
		}
#endif
		return true;
	}

	void SkiaBackend::PollEvents()
	{
#ifdef SNOWUI_GLFW_ENABLED
		glfwPollEvents();
#endif
	}

	void SkiaBackend::SwapBuffers()
	{
#ifdef SNOWUI_GLFW_ENABLED
		if (window_)
		{
			glfwSwapBuffers(static_cast<GLFWwindow*>(window_));
		}
#endif
	}

	void* SkiaBackend::GetNativeWindowHandle()
	{
		return window_;
	}

	bool SkiaBackend::Initialize(int width, int height)
	{
		width_ = width;
		height_ = height;

		std::cout << "Skia Backend: Initializing (" << width << "x" << height << ")" << std::endl;

#ifdef SNOWUI_OPENGL_ENABLED
		if (window_)
		{
			glViewport(0, 0, width, height);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, width, height, 0, -1, 1);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
#endif

		initialized_ = true;
		return true;
	}

	void SkiaBackend::Shutdown()
	{
		if (!initialized_)
			return;

		std::cout << "Skia Backend: Shutting down" << std::endl;

		DestroyWindow();
		initialized_ = false;
	}

	void SkiaBackend::BeginFrame()
	{
		if (!initialized_)
			return;

#ifdef SNOWUI_OPENGL_ENABLED
		if (window_)
		{
#ifdef SNOWUI_GLFW_ENABLED
			int newWidth, newHeight;
			glfwGetFramebufferSize(static_cast<GLFWwindow*>(window_), &newWidth, &newHeight);
			if (newWidth != width_ || newHeight != height_)
			{
				Resize(newWidth, newHeight);
			}
#endif
		}
#endif
	}

	void SkiaBackend::EndFrame()
	{
		if (!initialized_)
			return;

		SwapBuffers();
	}

	void SkiaBackend::ClearScreen(const Color& color)
	{
#ifdef SNOWUI_OPENGL_ENABLED
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT);
#else
		(void)color;
#endif
	}

	void SkiaBackend::DrawRect(const Rect& rect, const Color& color)
	{
#ifdef SNOWUI_OPENGL_ENABLED
		glColor4f(color.r, color.g, color.b, color.a);
		glBegin(GL_QUADS);
		glVertex2f(rect.x, rect.y);
		glVertex2f(rect.x + rect.width, rect.y);
		glVertex2f(rect.x + rect.width, rect.y + rect.height);
		glVertex2f(rect.x, rect.y + rect.height);
		glEnd();
#else
		(void)rect;
		(void)color;
#endif
	}

	void SkiaBackend::DrawLine(float x1, float y1, float x2, float y2, const Color& color)
	{
#ifdef SNOWUI_OPENGL_ENABLED
		glColor4f(color.r, color.g, color.b, color.a);
		glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glEnd();
#else
		(void)x1;
		(void)y1;
		(void)x2;
		(void)y2;
		(void)color;
#endif
	}

	void SkiaBackend::DrawText(const std::string& text, float x, float y, const Color& color)
	{
#ifdef SNOWUI_OPENGL_ENABLED
		if (text.empty())
			return;

		float curX = x;
		for (size_t i = 0; i < text.length(); ++i)
		{
			char c = text[i];
			if (c == ' ')
			{
				curX += kDefaultCharWidth;
				continue;
			}

			glColor4f(color.r, color.g, color.b, color.a);
			glBegin(GL_QUADS);
			glVertex2f(curX, y);
			glVertex2f(curX + kDefaultCharWidth - 1, y);
			glVertex2f(curX + kDefaultCharWidth - 1, y + kDefaultCharHeight);
			glVertex2f(curX, y + kDefaultCharHeight);
			glEnd();

			curX += kDefaultCharWidth;
		}
#else
		(void)text;
		(void)x;
		(void)y;
		(void)color;
#endif
	}

	void SkiaBackend::ExecuteDrawList(const DrawList& drawList)
	{
		if (!initialized_)
			return;

		const auto& commands = drawList.GetCommands();

		for (const auto& cmd : commands)
		{
			switch (cmd.type)
			{
			case DrawCommandType::Clear:
				ClearScreen(cmd.color);
				break;
			case DrawCommandType::DrawRect:
				DrawRect(cmd.rect, cmd.color);
				break;
			case DrawCommandType::DrawText:
				DrawText(cmd.text, cmd.rect.x, cmd.rect.y, cmd.color);
				break;
			case DrawCommandType::DrawLine:
				DrawLine(cmd.rect.x, cmd.rect.y, cmd.rect.width, cmd.rect.height, cmd.color);
				break;
			}
		}
	}

	void SkiaBackend::Resize(int width, int height)
	{
		width_ = width;
		height_ = height;

		if (initialized_)
		{
#ifdef SNOWUI_OPENGL_ENABLED
			glViewport(0, 0, width, height);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, width, height, 0, -1, 1);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
#endif
		}
	}

} // namespace SnowUI
