#pragma once

#include "ANSI.h"

#if __cpp_lib_format
	#include <format>
#endif

namespace ANSI {
	bool SupportsGraphics();
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

#if __cpp_lib_format

template <>
struct std::formatter<ANSI::Color, char> {
	using PC = basic_format_parse_context<char>;
	template <class Out>
	using FC = basic_format_context<Out, char>;

	enum class EColorType {
		Foreground,
		Background,
		Underline
	} m_Type = EColorType::Foreground;

	constexpr typename PC::iterator parse(PC& pc) {
		auto itr = pc.begin();
		if (itr == pc.end() || *itr == '}')
			return itr;

		switch (*itr) {
		case 'b':
			m_Type = EColorType::Background;
			++itr;
			break;
		case 'u':
			m_Type = EColorType::Underline;
			++itr;
			break;
		}

		if (itr == pc.end() && *itr != '}')
			throw std::format_error("Expected '}'");
		return itr;
	}

	template <class Out>
	typename FC<Out>::iterator format(ANSI::Color color, FC<Out>& fc) const {
		std::ostringstream str;
		switch (m_Type) {
		case EColorType::Foreground:
			str << ANSI::GraphicsForegroundColor { color };
			break;
		case EColorType::Background:
			str << ANSI::GraphicsBackgroundColor { color };
			break;
		case EColorType::Underline:
			str << ANSI::GraphicsUnderlineColor { color };
			break;
		}
		return std::format_to(fc.out(), "{}", str.str());
	}
};

template <>
struct std::formatter<ANSI::GraphicsForegroundColor, char> {
	using PC = basic_format_parse_context<char>;
	template <class Out>
	using FC = basic_format_context<Out, char>;

	constexpr typename PC::iterator parse(PC& pc) {
		return pc.begin();
	}

	template <class Out>
	typename FC<Out>::iterator format(ANSI::GraphicsForegroundColor color, FC<Out>& fc) const {
		std::ostringstream str;
		str << color;
		return std::format_to(fc.out(), "{}", str.str());
	}
};

template <>
struct std::formatter<ANSI::GraphicsBackgroundColor, char> {
	using PC = basic_format_parse_context<char>;
	template <class Out>
	using FC = basic_format_context<Out, char>;

	constexpr typename PC::iterator parse(PC& pc) {
		return pc.begin();
	}

	template <class Out>
	typename FC<Out>::iterator format(ANSI::GraphicsBackgroundColor color, FC<Out>& fc) const {
		std::ostringstream str;
		str << color;
		return std::format_to(fc.out(), "{}", str.str());
	}
};

template <>
struct std::formatter<ANSI::GraphicsUnderlineColor, char> {
	using PC = basic_format_parse_context<char>;
	template <class Out>
	using FC = basic_format_context<Out, char>;

	constexpr typename PC::iterator parse(PC& pc) {
		return pc.begin();
	}

	template <class Out>
	typename FC<Out>::iterator format(ANSI::GraphicsUnderlineColor color, FC<Out>& fc) const {
		std::ostringstream str;
		str << color;
		return std::format_to(fc.out(), "{}", str.str());
	}
};

#endif