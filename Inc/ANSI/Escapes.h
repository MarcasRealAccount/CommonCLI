#pragma once

#include "ANSI.h"

#include <ostream>

namespace ANSI {
	std::ostream& ESC(std::ostream& stream);
	std::ostream& CSI(std::ostream& stream);

	std::ostream& Reset(std::ostream& stream);
} // namespace ANSI