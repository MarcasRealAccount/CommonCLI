#pragma once

#include <ostream>
#include <string>

namespace ANSI {
	struct ANSIImplementation;

	struct ANSI {
	public:
		static ANSI s_Ansi;

	public:
		ANSI();
		~ANSI();

		auto& getTerminalName() const { return m_TerminalName; }
		auto& getImplementation() const { return *m_Implementation; }

	private:
		std::string m_TerminalName;
		ANSIImplementation* m_Implementation;
	};

	void setup();
	void restore();

	struct RGB {
	public:
		constexpr RGB(std::uint8_t r, std::uint8_t g, std::uint8_t b)
			: r(r), g(g), b(b) {}
		
	public:
		std::uint8_t r, g, b;
	};

	struct Color {
	public:
		constexpr Color(std::uint8_t id)
		    : m_Color(id), m_Mode(id <= 0b111 ? 3 : id <= 0b1111 ? 4 :
                                                                   8) { }
		constexpr Color(std::uint8_t r, std::uint8_t g, std::uint8_t b)
		    : m_RGB({ r, g, b }), m_Mode(24) { }

	public:
		union {
			RGB m_RGB;
			std::uint32_t m_Color;
		};
		std::uint8_t m_Mode;
	};

	namespace Colors3 {
		static constexpr Color Black   = { 0 };
		static constexpr Color Red     = { 1 };
		static constexpr Color Green   = { 2 };
		static constexpr Color Yellow  = { 3 };
		static constexpr Color Blue    = { 4 };
		static constexpr Color Magenta = { 5 };
		static constexpr Color Cyan    = { 6 };
		static constexpr Color White   = { 7 };
	} // namespace Colors3

	namespace Colors4 {
		using namespace Colors3;
		static constexpr Color Gray          = { 8 };
		static constexpr Color BrightRed     = { 9 };
		static constexpr Color BrightGreen   = { 10 };
		static constexpr Color BrightYellow  = { 11 };
		static constexpr Color BrightBlue    = { 12 };
		static constexpr Color BrightMagenta = { 13 };
		static constexpr Color BrightCyan    = { 14 };
		static constexpr Color BrightWhite   = { 15 };
	} // namespace Colors4

	namespace Colors8 {
		using namespace Colors4;
	} // namespace Colors8

	namespace Colors24 {
		static constexpr Color Black         = { 0, 0, 0 };
		static constexpr Color Red           = { 127, 0, 0 };
		static constexpr Color Green         = { 0, 127, 0 };
		static constexpr Color Yellow        = { 127, 127, 0 };
		static constexpr Color Blue          = { 0, 0, 127 };
		static constexpr Color Magenta       = { 127, 0, 127 };
		static constexpr Color Cyan          = { 0, 127, 127 };
		static constexpr Color White         = { 192, 192, 192 };
		static constexpr Color Gray          = { 127, 127, 127 };
		static constexpr Color BrightRed     = { 255, 0, 0 };
		static constexpr Color BrightGreen   = { 0, 255, 0 };
		static constexpr Color BrightYellow  = { 255, 255, 0 };
		static constexpr Color BrightBlue    = { 0, 0, 255 };
		static constexpr Color BrightMagenta = { 255, 0, 255 };
		static constexpr Color BrightCyan    = { 0, 255, 255 };
		static constexpr Color BrightWhite   = { 255, 255, 255 };
	} // namespace Colors24

	struct ANSIImplementation {
	public:
		virtual ~ANSIImplementation() = default;
		
		// Escapes
		virtual std::ostream& ESC(std::ostream& stream) = 0;
		virtual std::ostream& CSI(std::ostream& stream) = 0;

		virtual std::ostream& Reset(std::ostream& stream) = 0;

		// Cursor Controls
		virtual std::ostream& CursorHome(std::ostream& stream) = 0;

		virtual std::ostream& CursorPosition(std::uint32_t row, std::uint32_t col, std::ostream& stream)         = 0;
		virtual std::ostream& CursorPositionEffector(std::uint32_t row, std::uint32_t col, std::ostream& stream) = 0;

		virtual std::ostream& CursorUp(std::uint32_t lines, std::ostream& stream)           = 0;
		virtual std::ostream& CursorDown(std::uint32_t lines, std::ostream& stream)         = 0;
		virtual std::ostream& CursorRight(std::uint32_t cols, std::ostream& stream)         = 0;
		virtual std::ostream& CursorLeft(std::uint32_t cols, std::ostream& stream)          = 0;
		virtual std::ostream& CursorNextLine(std::uint32_t lines, std::ostream& stream)     = 0;
		virtual std::ostream& CursorPreviousLine(std::uint32_t lines, std::ostream& stream) = 0;
		virtual std::ostream& CursorHorizontalAbs(std::uint32_t col, std::ostream& stream)  = 0;

		virtual std::ostream& SaveCursor(std::ostream& stream)    = 0;
		virtual std::ostream& RestoreCursor(std::ostream& stream) = 0;

		// Erase
		virtual std::ostream& EraseInDisplay(std::ostream& stream)                     = 0;
		virtual std::ostream& EraseFromCursorToEndOfScreen(std::ostream& stream)       = 0;
		virtual std::ostream& EraseFromCursorToBeginningOfScreen(std::ostream& stream) = 0;
		virtual std::ostream& EraseEntireScreen(std::ostream& stream)                  = 0;
		virtual std::ostream& EraseSavedLines(std::ostream& stream)                    = 0;

		virtual std::ostream& EraseInLine(std::ostream& stream)                      = 0;
		virtual std::ostream& EraseFromCursorToEndOfLine(std::ostream& stream)       = 0;
		virtual std::ostream& EraseFromCursorToBeginningOfLine(std::ostream& stream) = 0;
		virtual std::ostream& EraseEntireLine(std::ostream& stream)                  = 0;

		// Graphics
		virtual std::ostream& GraphicsBold(std::ostream& stream)          = 0;
		virtual std::ostream& GraphicsDim(std::ostream& stream)           = 0;
		virtual std::ostream& GraphicsItalic(std::ostream& stream)        = 0;
		virtual std::ostream& GraphicsUnderline(std::ostream& stream)     = 0;
		virtual std::ostream& GraphicsBlink(std::ostream& stream)         = 0;
		virtual std::ostream& GraphicsInverse(std::ostream& stream)       = 0;
		virtual std::ostream& GraphicsHide(std::ostream& stream)          = 0;
		virtual std::ostream& GraphicsStrikethrough(std::ostream& stream) = 0;

		virtual std::ostream& GraphicsForegroundColor(Color color, std::ostream& stream) = 0;
		virtual std::ostream& GraphicsBackgroundColor(Color color, std::ostream& stream) = 0;
		virtual std::ostream& GraphicsUnderlineColor(Color color, std::ostream& stream)  = 0;

		virtual std::ostream& GraphicsReset(std::ostream& stream)                = 0;
		virtual std::ostream& GraphicsDisableBold(std::ostream& stream)          = 0;
		virtual std::ostream& GraphicsDisableDim(std::ostream& stream)           = 0;
		virtual std::ostream& GraphicsDisableItalic(std::ostream& stream)        = 0;
		virtual std::ostream& GraphicsDisableUnderline(std::ostream& stream)     = 0;
		virtual std::ostream& GraphicsDisableBlink(std::ostream& stream)         = 0;
		virtual std::ostream& GraphicsDisableInverse(std::ostream& stream)       = 0;
		virtual std::ostream& GraphicsReveal(std::ostream& stream)               = 0;
		virtual std::ostream& GraphicsDisableStrikethrough(std::ostream& stream) = 0;

		virtual std::ostream& GraphicsForegroundDefault(std::ostream& stream) = 0;
		virtual std::ostream& GraphicsBackgroundDefault(std::ostream& stream) = 0;
		virtual std::ostream& GraphicsUnderlineDefault(std::ostream& stream)  = 0;
	};
} // namespace ANSI
