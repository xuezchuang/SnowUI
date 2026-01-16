#include "SnowUI/Render/OpenGLBackend.h"
#include "SnowUI/Render/GLFWUtils.h"
#include <iostream>
#include <cstring>

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

	OpenGLBackend::OpenGLBackend() : width_(0), height_(0), initialized_(false), window_(nullptr), ownsWindow_(false)
	{
	}

	OpenGLBackend::~OpenGLBackend()
	{
		Shutdown();
	}

	bool OpenGLBackend::CreateWindow(const std::string& title, int width, int height)
	{
#ifdef SNOWUI_GLFW_ENABLED
		if (!InitializeGLFW())
		{
			std::cerr << "OpenGL Backend: Failed to initialize GLFW" << std::endl;
			return false;
		}

		// Set OpenGL hints for compatibility profile
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

		GLFWwindow* glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (!glfwWindow)
		{
			std::cerr << "OpenGL Backend: Failed to create GLFW window" << std::endl;
			TerminateGLFW();
			return false;
		}

		glfwMakeContextCurrent(glfwWindow);
		glfwSwapInterval(1); // Enable vsync

		window_ = glfwWindow;
		ownsWindow_ = true;
		width_ = width;
		height_ = height;

		std::cout << "OpenGL Backend: Window created (" << width << "x" << height << ")" << std::endl;
		return true;
#else
		(void)title;
		(void)width;
		(void)height;
		std::cerr << "OpenGL Backend: GLFW not available, cannot create window" << std::endl;
		return false;
#endif
	}

	void OpenGLBackend::DestroyWindow()
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

	bool OpenGLBackend::ShouldClose()
	{
#ifdef SNOWUI_GLFW_ENABLED
		if (window_)
		{
			return glfwWindowShouldClose(static_cast<GLFWwindow*>(window_));
		}
#endif
		return true;
	}

	void OpenGLBackend::PollEvents()
	{
#ifdef SNOWUI_GLFW_ENABLED
		glfwPollEvents();
#endif
	}

	void OpenGLBackend::SwapBuffers()
	{
#ifdef SNOWUI_GLFW_ENABLED
		if (window_)
		{
			glfwSwapBuffers(static_cast<GLFWwindow*>(window_));
		}
#endif
	}

	void* OpenGLBackend::GetNativeWindowHandle()
	{
		return window_;
	}

	bool OpenGLBackend::Initialize(int width, int height)
	{
		width_ = width;
		height_ = height;

		std::cout << "OpenGL Backend: Initializing (" << width << "x" << height << ")" << std::endl;

#ifdef SNOWUI_OPENGL_ENABLED
		// If we have a window context, set up the viewport
		if (window_)
		{
			glViewport(0, 0, width, height);

			// Set up orthographic projection for 2D rendering
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, width, height, 0, -1, 1); // Top-left origin

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			// Enable blending for transparency
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
#endif

		initialized_ = true;
		return true;
	}

	void OpenGLBackend::Shutdown()
	{
		if (!initialized_)
			return;

		std::cout << "OpenGL Backend: Shutting down" << std::endl;

		DestroyWindow();
		initialized_ = false;
	}

	void OpenGLBackend::BeginFrame()
	{
		if (!initialized_)
			return;

#ifdef SNOWUI_OPENGL_ENABLED
		// Check for window resize
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

	void OpenGLBackend::EndFrame()
	{
		if (!initialized_)
			return;

		SwapBuffers();
	}

	void OpenGLBackend::ClearScreen(const Color& color)
	{
#ifdef SNOWUI_OPENGL_ENABLED
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT);
#else
		(void)color;
#endif
	}

	void OpenGLBackend::DrawRect(const Rect& rect, const Color& color)
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

	void OpenGLBackend::DrawLine(float x1, float y1, float x2, float y2, const Color& color)
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

	void OpenGLBackend::DrawText(const std::string& text, float x, float y, const Color& color)
	{
		// Basic text rendering using simple rectangles for each character
		// In a real implementation, this would use font rendering with textures
#ifdef SNOWUI_OPENGL_ENABLED
		if (text.empty())
			return;

		// Draw a simple text indicator (a colored rectangle with character approximation)
		// Each character is rendered as a 6x10 pixel block
		const float charWidth = 7.0f;
		const float charHeight = 12.0f;

		float curX = x;
		for (size_t i = 0; i < text.length(); ++i)
		{
			char c = text[i];
			if (c == ' ')
			{
				curX += charWidth;
				continue;
			}

			// Draw character as small filled rectangle (placeholder for real font rendering)
			glColor4f(color.r, color.g, color.b, color.a);
			glBegin(GL_QUADS);
			glVertex2f(curX, y);
			glVertex2f(curX + charWidth - 1, y);
			glVertex2f(curX + charWidth - 1, y + charHeight);
			glVertex2f(curX, y + charHeight);
			glEnd();

			curX += charWidth;
		}
#else
		(void)text;
		(void)x;
		(void)y;
		(void)color;
#endif
	}

	void OpenGLBackend::ExecuteDrawList(const DrawList& drawList)
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
				// rect.x, rect.y = start point; rect.width, rect.height = end point
				DrawLine(cmd.rect.x, cmd.rect.y, cmd.rect.width, cmd.rect.height, cmd.color);
				break;
			}
		}
	}

	void OpenGLBackend::Resize(int width, int height)
	{
		width_ = width;
		height_ = height;

		if (initialized_)
		{
#ifdef SNOWUI_OPENGL_ENABLED
			glViewport(0, 0, width, height);

			// Update orthographic projection
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, width, height, 0, -1, 1);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
#endif
		}
	}

} // namespace SnowUI
