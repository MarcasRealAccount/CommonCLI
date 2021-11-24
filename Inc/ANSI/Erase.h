#pragma once

#include "ANSI.h"

namespace ANSI {
	bool SupportsErase();
	std::ostream& EraseInDisplay(std::ostream& stream);
	std::ostream& EraseFromCursorToEndOfScreen(std::ostream& stream);
	std::ostream& EraseFromCursorToBeginningOfScreen(std::ostream& stream);
	std::ostream& EraseEntireScreen(std::ostream& stream);
	std::ostream& EraseSavedLines(std::ostream& stream);

	std::ostream& EraseInLine(std::ostream& stream);
	std::ostream& EraseFromCursorToEndOfLine(std::ostream& stream);
	std::ostream& EraseFromCursorToBeginningOfLine(std::ostream& stream);
	std::ostream& EraseEntireLine(std::ostream& stream);
} // namespace ANSI
