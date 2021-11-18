#pragma once

#include <string>
#include <string_view>

namespace CommonCLI {
	enum class EHandler {
		KeyValue
	};

	class Handler {
	public:
		Handler(std::string_view programName, std::string_view programDesc);
		Handler(std::string&& programName, std::string&& programDesc);

		virtual EHandler getType() = 0;

		auto& getProgramName() const { return m_ProgramName; }
		auto& getProgramDesc() const { return m_ProgramDesc; }

	private:
		std::string m_ProgramName;
		std::string m_ProgramDesc;
	};
} // namespace CommonCLI