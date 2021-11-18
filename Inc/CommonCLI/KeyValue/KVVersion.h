#pragma once

#include <cstddef>
#include <cstdint>

#include <string>
#include <string_view>
#include <vector>

namespace CommonCLI::KeyValue {
	struct Key;
	struct HandlerContext;

	namespace Version {
		class Version {
		public:
			Version(std::size_t major, std::size_t minor, std::size_t patch, const std::string& prefix = "", const std::string& suffix = "");
			Version(std::size_t major, std::size_t minor, std::size_t patch, std::string&& prefix, std::string&& suffix = "");

			void invoke(Key& self, HandlerContext& context, const std::vector<std::string_view>& values, std::size_t& usedValueCount);

			std::string getVersionStr() const;

		private:
			std::size_t m_Major, m_Minor, m_Patch;
			std::string m_Prefix;
			std::string m_Suffix;
		};
	} // namespace Version
} // namespace CommonCLI::KeyValue