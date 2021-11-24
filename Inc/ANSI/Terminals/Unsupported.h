#pragma once

#include "ANSI/ANSI.h"

namespace ANSI::Terminals {
	struct Unsupported : public ANSIImplementation {
		virtual bool SupportsCursor() override { return false; }
		virtual bool SupportsErase() override { return false; }
		virtual bool SupportsGraphics() override { return false; }
		
		// Escapes
		virtual std::ostream& ESC(std::ostream& stream) override { return stream; }
		virtual std::ostream& CSI(std::ostream& stream) override { return stream; }

		virtual std::ostream& Reset(std::ostream& stream) override { return stream; }

		// Cursor Controls
		virtual std::ostream& CursorHome(std::ostream& stream) override { return stream; }

		virtual std::ostream& CursorPosition(std::uint32_t row, std::uint32_t col, std::ostream& stream) override { return stream; }
		virtual std::ostream& CursorPositionEffector(std::uint32_t row, std::uint32_t col, std::ostream& stream) override { return stream; }

		virtual std::ostream& CursorUp(std::uint32_t lines, std::ostream& stream) override { return stream; }
		virtual std::ostream& CursorDown(std::uint32_t lines, std::ostream& stream) override { return stream; }
		virtual std::ostream& CursorRight(std::uint32_t cols, std::ostream& stream) override { return stream; }
		virtual std::ostream& CursorLeft(std::uint32_t cols, std::ostream& stream) override { return stream; }
		virtual std::ostream& CursorNextLine(std::uint32_t lines, std::ostream& stream) override { return stream; }
		virtual std::ostream& CursorPreviousLine(std::uint32_t lines, std::ostream& stream) override { return stream; }
		virtual std::ostream& CursorHorizontalAbs(std::uint32_t col, std::ostream& stream) override { return stream; }

		virtual std::ostream& SaveCursor(std::ostream& stream) override { return stream; }
		virtual std::ostream& RestoreCursor(std::ostream& stream) override { return stream; }

		// Erase
		virtual std::ostream& EraseInDisplay(std::ostream& stream) override { return stream; }
		virtual std::ostream& EraseFromCursorToEndOfScreen(std::ostream& stream) override { return stream; }
		virtual std::ostream& EraseFromCursorToBeginningOfScreen(std::ostream& stream) override { return stream; }
		virtual std::ostream& EraseEntireScreen(std::ostream& stream) override { return stream; }
		virtual std::ostream& EraseSavedLines(std::ostream& stream) override { return stream; }

		virtual std::ostream& EraseInLine(std::ostream& stream) override { return stream; }
		virtual std::ostream& EraseFromCursorToEndOfLine(std::ostream& stream) override { return stream; }
		virtual std::ostream& EraseFromCursorToBeginningOfLine(std::ostream& stream) override { return stream; }
		virtual std::ostream& EraseEntireLine(std::ostream& stream) override { return stream; }

		// Graphics
		virtual std::ostream& GraphicsBold(std::ostream& stream) override { return stream; }
		virtual std::ostream& GraphicsDim(std::ostream& stream) override { return stream; }
		virtual std::ostream& GraphicsItalic(std::ostream& stream) override { return stream; }
		virtual std::ostream& GraphicsUnderline(std::ostream& stream) override { return stream; }
		virtual std::ostream& GraphicsBlink(std::ostream& stream) override { return stream; }
		virtual std::ostream& GraphicsInverse(std::ostream& stream) override { return stream; }
		virtual std::ostream& GraphicsHide(std::ostream& stream) override { return stream; }
		virtual std::ostream& GraphicsStrikethrough(std::ostream& stream) override { return stream; }

		virtual std::ostream& GraphicsForegroundColor(Color color, std::ostream& stream) override { return stream; }
		virtual std::ostream& GraphicsBackgroundColor(Color color, std::ostream& stream) override { return stream; }
		virtual std::ostream& GraphicsUnderlineColor(Color color, std::ostream& stream) override { return stream; }

		virtual std::ostream& GraphicsReset(std::ostream& stream) override { return stream; }
		virtual std::ostream& GraphicsDisableBold(std::ostream& stream) override { return stream; }
		virtual std::ostream& GraphicsDisableDim(std::ostream& stream) override { return stream; }
		virtual std::ostream& GraphicsDisableItalic(std::ostream& stream) override { return stream; }
		virtual std::ostream& GraphicsDisableUnderline(std::ostream& stream) override { return stream; }
		virtual std::ostream& GraphicsDisableBlink(std::ostream& stream) override { return stream; }
		virtual std::ostream& GraphicsDisableInverse(std::ostream& stream) override { return stream; }
		virtual std::ostream& GraphicsReveal(std::ostream& stream) override { return stream; }
		virtual std::ostream& GraphicsDisableStrikethrough(std::ostream& stream) override { return stream; }

		virtual std::ostream& GraphicsForegroundDefault(std::ostream& stream) override { return stream; }
		virtual std::ostream& GraphicsBackgroundDefault(std::ostream& stream) override { return stream; }
		virtual std::ostream& GraphicsUnderlineDefault(std::ostream& stream) override { return stream; }
	};
} // namespace ANSI::Terminals
