#include "CommonCLI/Handler.h"

#include <utility>

namespace CommonCLI {
	Handler::Handler(std::string_view programName, std::string_view programDesc)
	    : m_ProgramName(programName), m_ProgramDesc(programDesc) { }

	Handler::Handler(std::string&& programName, std::string&& programDesc)
	    : m_ProgramName(std::move(programName)), m_ProgramDesc(std::move(programDesc)) { }
} // namespace CommonCLI