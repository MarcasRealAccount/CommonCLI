#pragma once

#include "ANSI.h"

namespace ANSI {
	std::ostream& GraphicsBold(std::ostream& stream);
	std::ostream& GraphicsDim(std::ostream& stream);
	std::ostream& GraphicsItalic(std::ostream& stream);
	std::ostream& GraphicsUnderline(std::ostream& stream);
	std::ostream& GraphicsBlink(std::ostream& stream);
	std::ostream& GraphicsInverse(std::ostream& stream);
	std::ostream& GraphicsHide(std::ostream& stream);
	std::ostream& GraphicsStrikethrough(std::ostream& stream);

	struct GraphicsForegroundColor {
	public:
		constexpr GraphicsForegroundColor(std::uint8_t id)
		    : m_Color(id), m_Mode(id <= 0b111 ? 3 : id <= 0b1111 ? 4 :
                                                                   8) { }
		constexpr GraphicsForegroundColor(std::uint8_t r, std::uint8_t g, std::uint8_t b)
		    : m_RGB({ r, g, b }), m_Mode(24) { }
		constexpr GraphicsForegroundColor(Color color)
		    : m_Color(color.m_Color), m_Mode(color.m_Mode) { }

		operator Color() const {
			Color color { 0 };
			color.m_Color = m_Color;
			color.m_Mode  = m_Mode;
			return color;
		}

		friend std::ostream& operator<<(std::ostream& stream, GraphicsForegroundColor color);

	public:
		union {
			RGB m_RGB;
			std::uint32_t m_Color;
		};
		std::uint8_t m_Mode;
	};

	struct GraphicsBackgroundColor {
	public:
		constexpr GraphicsBackgroundColor(std::uint8_t id)
		    : m_Color(id), m_Mode(id <= 0b111 ? 3 : id <= 0b1111 ? 4 :
                                                                   8) { }
		constexpr GraphicsBackgroundColor(std::uint8_t r, std::uint8_t g, std::uint8_t b)
		    : m_RGB({ r, g, b }), m_Mode(24) { }
		constexpr GraphicsBackgroundColor(Color color)
		    : m_Color(color.m_Color), m_Mode(color.m_Mode) { }

		operator Color() const {
			Color color { 0 };
			color.m_Color = m_Color;
			color.m_Mode  = m_Mode;
			return color;
		}

		friend std::ostream& operator<<(std::ostream& stream, GraphicsBackgroundColor color);

	public:
		union {
			RGB m_RGB;
			std::uint32_t m_Color;
		};
		std::uint8_t m_Mode;
	};

	struct GraphicsUnderlineColor {
	public:
		constexpr GraphicsUnderlineColor(std::uint8_t id)
		    : m_Color(id), m_Mode(id <= 0b111 ? 3 : id <= 0b1111 ? 4 :
                                                                   8) { }
		constexpr GraphicsUnderlineColor(std::uint8_t r, std::uint8_t g, std::uint8_t b)
		    : m_RGB({ r, g, b }), m_Mode(24) { }
		constexpr GraphicsUnderlineColor(Color color)
		    : m_Color(color.m_Color), m_Mode(color.m_Mode) { }

		operator Color() const {
			Color color { 0 };
			color.m_Color = m_Color;
			color.m_Mode  = m_Mode;
			return color;
		}

		friend std::ostream& operator<<(std::ostream& stream, GraphicsUnderlineColor color);

	public:
		union {
			RGB m_RGB;
			std::uint32_t m_Color;
		};
		std::uint8_t m_Mode;
	};

	std::ostream& GraphicsReset(std::ostream& stream);
	std::ostream& GraphicsDisableBold(std::ostream& stream);
	std::ostream& GraphicsDisableDim(std::ostream& stream);
	std::ostream& GraphicsDisableItalic(std::ostream& stream);
	std::ostream& GraphicsDisableUnderline(std::ostream& stream);
	std::ostream& GraphicsDisableBlink(std::ostream& stream);
	std::ostream& GraphicsDisableInverse(std::ostream& stream);
	std::ostream& GraphicsReveal(std::ostream& stream);
	std::ostream& GraphicsDisableStrikethrough(std::ostream& stream);

	std::ostream& GraphicsForegroundDefault(std::ostream& stream);
	std::ostream& GraphicsBackgroundDefault(std::ostream& stream);
	std::ostream& GraphicsUnderlineDefault(std::ostream& stream);
} // namespace ANSI
