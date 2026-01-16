#pragma once

#include <vector>
#include <string>
#include <cstdint>

namespace SnowUI
{

	enum class DrawCommandType
	{
		Clear,
		DrawRect,
		DrawText,
		DrawLine,
	};

	struct Color
	{
		float r, g, b, a;

		Color() : r(0), g(0), b(0), a(1)
		{
		}
		Color(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a)
		{
		}
	};

	struct Rect
	{
		float x, y, width, height;

		Rect() : x(0), y(0), width(0), height(0)
		{
		}
		Rect(float x, float y, float w, float h) : x(x), y(y), width(w), height(h)
		{
		}
	};

	struct DrawCommand
	{
		DrawCommandType type;
		Rect rect;
		Color color;
		std::string text;

		DrawCommand(DrawCommandType t) : type(t)
		{
		}
	};

	class DrawList
	{
	  public:
		void Clear()
		{
			commands_.clear();
		}

		void AddClear(const Color& color)
		{
			DrawCommand cmd(DrawCommandType::Clear);
			cmd.color = color;
			commands_.push_back(cmd);
		}

		void AddRect(const Rect& rect, const Color& color)
		{
			DrawCommand cmd(DrawCommandType::DrawRect);
			cmd.rect = rect;
			cmd.color = color;
			commands_.push_back(cmd);
		}

		void AddText(const std::string& text, float x, float y, const Color& color)
		{
			DrawCommand cmd(DrawCommandType::DrawText);
			cmd.text = text;
			cmd.rect.x = x;
			cmd.rect.y = y;
			cmd.color = color;
			commands_.push_back(cmd);
		}

		void AddLine(float x1, float y1, float x2, float y2, const Color& color)
		{
			DrawCommand cmd(DrawCommandType::DrawLine);
			cmd.rect.x = x1;
			cmd.rect.y = y1;
			cmd.rect.width = x2;
			cmd.rect.height = y2;
			cmd.color = color;
			commands_.push_back(cmd);
		}

		const std::vector<DrawCommand>& GetCommands() const
		{
			return commands_;
		}

	  private:
		std::vector<DrawCommand> commands_;
	};

} // namespace SnowUI
