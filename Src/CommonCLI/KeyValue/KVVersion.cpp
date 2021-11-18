#include "CommonCLI/KeyValue/KVVersion.h"
#include "CommonCLI/Colors.h"
#include "CommonCLI/KeyValue/KVHandler.h"
#include "Premake/Defines.h"

#include <iostream>
#include <sstream>
#include <utility>

namespace CommonCLI::KeyValue::Version {
	Version::Version(std::size_t major, std::size_t minor, std::size_t patch, const std::string& prefix, const std::string& suffix)
	    : m_Major(major), m_Minor(minor), m_Patch(patch), m_Prefix(prefix), m_Suffix(suffix) { }

	Version::Version(std::size_t major, std::size_t minor, std::size_t patch, std::string&& prefix, std::string&& suffix)
	    : m_Major(major), m_Minor(minor), m_Patch(patch), m_Prefix(std::move(prefix)), m_Suffix(std::move(suffix)) { }

	void Version::invoke(Key& self, HandlerContext& context, const std::vector<std::string_view>& values, std::size_t& usedValueCount) {
		std::ostringstream versionStr;

		if (values.size() > 0 && (values[0] == "silent" || values[0] == "s")) {
			versionStr << getVersionStr();
			usedValueCount = 1;
		} else {
			versionStr << Colors::Info << context.getHandler().getProgramName() << " version is " << Colors::Arg << '\'' << getVersionStr() << "'\n";
			versionStr << Colors::Info << "Build for " << Colors::Arg << '\'';
			Premake::printPremakeSystemFlags(versionStr, Premake::s_System);
			versionStr << '\'' << Colors::Info << " (Config " << Colors::Arg << '\'';
			Premake::printPremakeConfigFlags(versionStr, Premake::s_Config);
			versionStr << '\'' << Colors::Info << ", Platform " << Colors::Arg << '\'';
			Premake::printPremakePlatformFlags(versionStr, Premake::s_Platform);
			versionStr << '\'' << Colors::Info << ", Toolset " << Colors::Arg << '\'';
			Premake::printPremakeToolsetFlags(versionStr, Premake::s_Toolset);
			versionStr << '\'' << Colors::Info << ")";
		}

		context.addMessage(versionStr.str(), true);
	}

	std::string Version::getVersionStr() const {
		std::string str;
		if (!m_Prefix.empty()) str = m_Prefix + '-';
		str += std::to_string(m_Major) + "." + std::to_string(m_Minor) + "." + std::to_string(m_Patch);
		if (!m_Suffix.empty()) str += '-' + m_Suffix;
		return str;
	}
} // namespace CommonCLI::KeyValue::Version