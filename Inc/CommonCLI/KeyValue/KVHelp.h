#pragma once

#include <cstddef>
#include <cstdint>

#include <string>
#include <string_view>
#include <vector>

namespace CommonCLI::KeyValue {
	struct Key;
	struct HandlerContext;

	namespace Help {
		struct Info {
		public:
			Info(const std::string& desc = "", const std::string& note = "");
			Info(std::string&& desc, std::string&& note);

			auto& getDesc() const { return m_Desc; }
			auto& getNote() const { return m_Note; }

		private:
			std::string m_Desc;
			std::string m_Note;
		};

		class Help {
		public:
			void invoke(Key& self, HandlerContext& context, const std::vector<std::string_view>& values, std::size_t& usedValueCount);

			std::string formatKey(const Key& key) const;
		};
	} // namespace Help
} // namespace CommonCLI::KeyValue