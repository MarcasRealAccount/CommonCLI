#pragma once

#include "Escapes.h"

namespace ANSI {
	std::ostream& CursorHome(std::ostream& stream);

	struct CursorPosition {
	public:
		constexpr CursorPosition(std::uint32_t row, std::uint32_t col)
		    : m_Row(row), m_Col(col) { }

		friend std::ostream& operator<<(std::ostream& stream, CursorPosition cursorPosition);

	public:
		std::uint32_t m_Row, m_Col;
	};

	struct CursorPositionEffector {
	public:
		constexpr CursorPositionEffector(std::uint32_t row, std::uint32_t col)
		    : m_Row(row), m_Col(col) { }

		friend std::ostream& operator<<(std::ostream& stream, CursorPositionEffector cursorPositionEffector);

	public:
		std::uint32_t m_Row, m_Col;
	};

	struct CursorUp {
	public:
		constexpr CursorUp(std::uint32_t lines)
		    : m_Lines(lines) { }

		friend std::ostream& operator<<(std::ostream& stream, CursorUp cursorUp);

	public:
		std::uint32_t m_Lines;
	};

	struct CursorDown {
	public:
		constexpr CursorDown(std::uint32_t lines)
		    : m_Lines(lines) { }

		friend std::ostream& operator<<(std::ostream& stream, CursorDown cursorDown);

	public:
		std::uint32_t m_Lines;
	};

	struct CursorRight {
	public:
		constexpr CursorRight(std::uint32_t cols)
		    : m_Cols(cols) { }

		friend std::ostream& operator<<(std::ostream& stream, CursorRight cursorRight);

	public:
		std::uint32_t m_Cols;
	};

	struct CursorLeft {
	public:
		constexpr CursorLeft(std::uint32_t cols)
		    : m_Cols(cols) { }

		friend std::ostream& operator<<(std::ostream& stream, CursorLeft cursorLeft);

	public:
		std::uint32_t m_Cols;
	};

	struct CursorNextLine {
	public:
		constexpr CursorNextLine(std::uint32_t lines)
		    : m_Lines(lines) { }

		friend std::ostream& operator<<(std::ostream& stream, CursorNextLine cursorNextLine);

	public:
		std::uint32_t m_Lines;
	};

	struct CursorPreviousLine {
	public:
		constexpr CursorPreviousLine(std::uint32_t lines)
		    : m_Lines(lines) { }

		friend std::ostream& operator<<(std::ostream& stream, CursorPreviousLine cursorPreviousLine);

	public:
		std::uint32_t m_Lines;
	};

	struct CursorHorizontalAbs {
	public:
		constexpr CursorHorizontalAbs(std::uint32_t col)
		    : m_Col(col) { }

		friend std::ostream& operator<<(std::ostream& stream, CursorHorizontalAbs cursorHorizontalAbs);

	public:
		std::uint32_t m_Col;
	};

	std::ostream& SaveCursor(std::ostream& stream);
	std::ostream& RestoreCursor(std::ostream& stream);
} // namespace ANSI