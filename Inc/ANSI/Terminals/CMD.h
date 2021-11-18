#pragma once

#include "ANSI/ANSI.h"

namespace ANSI::Terminals {
	struct CMD : public ANSIImplementation {
		// Escapes
		virtual std::ostream& ESC(std::ostream& stream) override { return stream << '\033'; }
		virtual std::ostream& CSI(std::ostream& stream) override { return stream << "\033["; }

		virtual std::ostream& Reset(std::ostream& stream) override { return stream << "\033c"; }

		// Cursor Controls
		virtual std::ostream& CursorHome(std::ostream& stream) override { return stream << "\033[H"; }

		virtual std::ostream& CursorPosition(std::uint32_t row, std::uint32_t col, std::ostream& stream) override { return stream << "\033[" << row << ';' << col << 'H'; }
		virtual std::ostream& CursorPositionEffector(std::uint32_t row, std::uint32_t col, std::ostream& stream) override { return stream << "\033[" << row << ';' << col << 'f'; }

		virtual std::ostream& CursorUp(std::uint32_t lines, std::ostream& stream) override { return stream << "\033[" << lines << 'A'; }
		virtual std::ostream& CursorDown(std::uint32_t lines, std::ostream& stream) override { return stream << "\033[" << lines << 'B'; }
		virtual std::ostream& CursorRight(std::uint32_t cols, std::ostream& stream) override { return stream << "\033[" << cols << 'C'; }
		virtual std::ostream& CursorLeft(std::uint32_t cols, std::ostream& stream) override { return stream << "\033[" << cols << 'D'; }
		virtual std::ostream& CursorNextLine(std::uint32_t lines, std::ostream& stream) override { return stream << "\033[" << lines << 'E'; }
		virtual std::ostream& CursorPreviousLine(std::uint32_t lines, std::ostream& stream) override { return stream << "\033[" << lines << 'F'; }
		virtual std::ostream& CursorHorizontalAbs(std::uint32_t col, std::ostream& stream) override { return stream << "\033[" << col << 'G'; }

		virtual std::ostream& SaveCursor(std::ostream& stream) override { return stream << "\0337"; }
		virtual std::ostream& RestoreCursor(std::ostream& stream) override { return stream << "\0338"; }

		// Erase
		virtual std::ostream& EraseInDisplay(std::ostream& stream) override { return stream << "\033[J"; }
		virtual std::ostream& EraseFromCursorToEndOfScreen(std::ostream& stream) override { return stream << "\033[0J"; }
		virtual std::ostream& EraseFromCursorToBeginningOfScreen(std::ostream& stream) override { return stream << "\033[1J"; }
		virtual std::ostream& EraseEntireScreen(std::ostream& stream) override { return stream << "\033[2J"; }
		virtual std::ostream& EraseSavedLines(std::ostream& stream) override { return stream << "\033[3J"; }

		virtual std::ostream& EraseInLine(std::ostream& stream) override { return stream << "\033[K"; }
		virtual std::ostream& EraseFromCursorToEndOfLine(std::ostream& stream) override { return stream << "\033[0K"; }
		virtual std::ostream& EraseFromCursorToBeginningOfLine(std::ostream& stream) override { return stream << "\033[1K"; }
		virtual std::ostream& EraseEntireLine(std::ostream& stream) override { return stream << "\033[2K"; }

		// Graphics
		virtual std::ostream& GraphicsBold(std::ostream& stream) override { return stream << "\033[1m"; }
		virtual std::ostream& GraphicsDim(std::ostream& stream) override { return stream << "\033[2m"; }
		virtual std::ostream& GraphicsItalic(std::ostream& stream) override { return stream << "\033[3m"; }
		virtual std::ostream& GraphicsUnderline(std::ostream& stream) override { return stream << "\033[4m"; }
		virtual std::ostream& GraphicsBlink(std::ostream& stream) override { return stream << "\033[5m"; }
		virtual std::ostream& GraphicsInverse(std::ostream& stream) override { return stream << "\033[7m"; }
		virtual std::ostream& GraphicsHide(std::ostream& stream) override { return stream << "\033[8m"; }
		virtual std::ostream& GraphicsStrikethrough(std::ostream& stream) override { return stream << "\033[9m"; }

		virtual std::ostream& GraphicsForegroundColor(Color color, std::ostream& stream) override {
			switch (color.m_Mode) {
			case 3: return stream << "\033[" << 30 + color.m_Color << 'm';
			case 4:
				if (color.m_Color < 0b111)
					return stream << "\033[" << 30 + color.m_Color << 'm';
				else
					return stream << "\033[1;" << 30 + color.m_Color << 'm';
			case 8: return stream << "\033[38;5;" << color.m_Color << 'm';
			case 24: return stream << "\033[38;2;" << static_cast<std::uint32_t>(color.m_RGB.r) << ';' << static_cast<std::uint32_t>(color.m_RGB.g) << ';' << static_cast<std::uint32_t>(color.m_RGB.b) << 'm';
			default: return stream;
			}
		}

		virtual std::ostream& GraphicsBackgroundColor(Color color, std::ostream& stream) override {
			switch (color.m_Mode) {
			case 3: return stream << "\033[" << 40 + color.m_Color << 'm';
			case 4:
				if (color.m_Color < 0b111)
					return stream << "\033[" << 40 + color.m_Color << 'm';
				else
					return stream << "\033[1;" << 40 + color.m_Color << 'm';
			case 8: return stream << "\033[48;5;" << color.m_Color << 'm';
			case 24: return stream << "\033[48;2;" << static_cast<std::uint32_t>(color.m_RGB.r) << ';' << static_cast<std::uint32_t>(color.m_RGB.g) << ';' << static_cast<std::uint32_t>(color.m_RGB.b) << 'm';
			default: return stream;
			}
		}

		virtual std::ostream& GraphicsUnderlineColor(Color color, std::ostream& stream) override {
			switch (color.m_Mode) {
			case 3:
				[[fallthrough]];
			case 4:
				[[fallthrough]];
			case 8: return stream << "\033[58;5;" << color.m_Color << 'm';
			case 24: return stream << "\033[58;2;" << static_cast<std::uint32_t>(color.m_RGB.r) << ';' << static_cast<std::uint32_t>(color.m_RGB.g) << ';' << static_cast<std::uint32_t>(color.m_RGB.b) << 'm';
			default: return stream;
			}
		}

		virtual std::ostream& GraphicsReset(std::ostream& stream) override { return stream << "\033[0m"; }
		virtual std::ostream& GraphicsDisableBold(std::ostream& stream) override { return stream << "\033[22m"; }
		virtual std::ostream& GraphicsDisableDim(std::ostream& stream) override { return stream << "\033[22m"; }
		virtual std::ostream& GraphicsDisableItalic(std::ostream& stream) override { return stream << "\033[23m"; }
		virtual std::ostream& GraphicsDisableUnderline(std::ostream& stream) override { return stream << "\033[24m"; }
		virtual std::ostream& GraphicsDisableBlink(std::ostream& stream) override { return stream << "\033[25m"; }
		virtual std::ostream& GraphicsDisableInverse(std::ostream& stream) override { return stream << "\033[27m"; }
		virtual std::ostream& GraphicsReveal(std::ostream& stream) override { return stream << "\033[28m"; }
		virtual std::ostream& GraphicsDisableStrikethrough(std::ostream& stream) override { return stream << "\033[29m"; }

		virtual std::ostream& GraphicsForegroundDefault(std::ostream& stream) override { return stream << "\033[39m"; }
		virtual std::ostream& GraphicsBackgroundDefault(std::ostream& stream) override { return stream << "\033[49m"; }
		virtual std::ostream& GraphicsUnderlineDefault(std::ostream& stream) override { return stream << "\033[59m"; }
	};
} // namespace ANSI::Terminals