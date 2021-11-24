#include "ANSI/Cursor.h"

namespace ANSI {
	bool SupportsCursor() {
		return ANSI::s_Ansi.getImplementation().SupportsCursor();
	}
	
	std::ostream& CursorHome(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().CursorHome(stream);
	}

	std::ostream& operator<<(std::ostream& stream, CursorPosition cursorPosition) {
		return ANSI::s_Ansi.getImplementation().CursorPosition(cursorPosition.m_Col, cursorPosition.m_Row, stream);
	}

	std::ostream& operator<<(std::ostream& stream, CursorPositionEffector cursorPositionEffector) {
		return ANSI::s_Ansi.getImplementation().CursorPositionEffector(cursorPositionEffector.m_Col, cursorPositionEffector.m_Row, stream);
	}

	std::ostream& operator<<(std::ostream& stream, CursorUp cursorUp) {
		return ANSI::s_Ansi.getImplementation().CursorUp(cursorUp.m_Lines, stream);
	}

	std::ostream& operator<<(std::ostream& stream, CursorDown cursorDown) {
		return ANSI::s_Ansi.getImplementation().CursorDown(cursorDown.m_Lines, stream);
	}

	std::ostream& operator<<(std::ostream& stream, CursorRight cursorRight) {
		return ANSI::s_Ansi.getImplementation().CursorRight(cursorRight.m_Cols, stream);
	}

	std::ostream& operator<<(std::ostream& stream, CursorLeft cursorLeft) {
		return ANSI::s_Ansi.getImplementation().CursorLeft(cursorLeft.m_Cols, stream);
	}

	std::ostream& operator<<(std::ostream& stream, CursorNextLine cursorNextLine) {
		return ANSI::s_Ansi.getImplementation().CursorNextLine(cursorNextLine.m_Lines, stream);
	}

	std::ostream& operator<<(std::ostream& stream, CursorPreviousLine cursorPreviousLine) {
		return ANSI::s_Ansi.getImplementation().CursorPreviousLine(cursorPreviousLine.m_Lines, stream);
	}

	std::ostream& operator<<(std::ostream& stream, CursorHorizontalAbs cursorHorizontalAbs) {
		return ANSI::s_Ansi.getImplementation().CursorHorizontalAbs(cursorHorizontalAbs.m_Col, stream);
	}

	std::ostream& SaveCursor(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().SaveCursor(stream);
	}

	std::ostream& RestoreCursor(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().RestoreCursor(stream);
	}
} // namespace ANSI
