#include "ANSI/Escapes.h"

namespace ANSI {
	std::ostream& ESC(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().ESC(stream);
	}

	std::ostream& CSI(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().CSI(stream);
	}

	std::ostream& Reset(std::ostream& stream) {
		return ANSI::s_Ansi.getImplementation().Reset(stream);
	}
} // namespace ANSI