#include "ANSI/Erase.h"

namespace ANSI {
	std::ostream& EraseInDisplay(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().EraseInDisplay(stream);
	}

	std::ostream& EraseFromCursorToEndOfScreen(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().EraseFromCursorToEndOfScreen(stream);
	}

	std::ostream& EraseFromCursorToBeginningOfScreen(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().EraseFromCursorToBeginningOfScreen(stream);
	}

	std::ostream& EraseEntireScreen(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().EraseEntireScreen(stream);
	}

	std::ostream& EraseSavedLines(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().EraseSavedLines(stream);
	}

	std::ostream& EraseInLine(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().EraseInLine(stream);
	}

	std::ostream& EraseFromCursorToEndOfLine(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().EraseFromCursorToEndOfLine(stream);
	}

	std::ostream& EraseFromCursorToBeginningOfLine(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().EraseFromCursorToBeginningOfLine(stream);
	}

	std::ostream& EraseEntireLine(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().EraseEntireLine(stream);
	}
} // namespace ANSI