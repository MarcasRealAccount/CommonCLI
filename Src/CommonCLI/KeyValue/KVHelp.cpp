#include "CommonCLI/KeyValue/KVHelp.h"
#include "CommonCLI/Colors.h"
#include "CommonCLI/KeyValue/KVHandler.h"
#include "CommonCLI/KeyValue/KVKey.h"

#include <iostream>
#include <sstream>
#include <utility>

namespace CommonCLI::KeyValue::Help {
	static void AddNote(std::ostringstream& str, std::string_view note) {
		str << Colors::Note << '(' << Colors::NoteLabel << "Note" << Colors::Note << ": " << note << ")";
	}

	Info::Info(const std::string& desc, const std::string& note)
	    : m_Desc(desc), m_Note(note) { }

	Info::Info(std::string&& desc, std::string&& note)
	    : m_Desc(std::move(desc)), m_Note(std::move(note)) { }

	void Help::invoke(Key& self, HandlerContext& context, const std::vector<std::string_view>& values, std::size_t& usedValueCount) {
		std::ostringstream helpStr;

		std::vector<const Key*> keys;

		if (values.empty()) {
			if (!context.getHandler().getProgramDesc().empty())
				helpStr << Colors::Info << context.getHandler().getProgramDesc() << '\n';
			helpStr << Colors::Help << context.getHandler().getProgramName() << " Syntax: " << Colors::Usage << '\'' << context.getArgs()[0] << " (--key (value ...) ...)'\n";

			auto& hkeys = context.getHandler().getKeys();
			keys.resize(hkeys.size());
			for (std::size_t i = 0; i < hkeys.size(); ++i)
				keys[i] = &hkeys[i];
		} else {
			for (auto& value : values) {
				auto key = context.getHandler().getKey(value);
				if (!key) {
					helpStr << Colors::Help << context.getHandler().getProgramName() << Colors::Warn << " Doesn't contain the key '" << value << "'\n";
					continue;
				}
				keys.push_back(key);
			}

			usedValueCount = values.size();
		}

		if (!keys.empty()) {
			helpStr << Colors::Help << context.getHandler().getProgramName() << " Keys:\n";
			std::vector<std::string> keyStrings(keys.size());
			std::size_t largestStrlen = 0;
			for (std::size_t i = 0; i < keys.size(); ++i) {
				keyStrings[i] = formatKey(*keys[i]);
				if (keyStrings[i].size() > largestStrlen)
					largestStrlen = keyStrings[i].size();
			}

			for (std::size_t i = 0; i < keys.size(); ++i) {
				auto& keyString = keyStrings[i];
				auto& key       = keys[i];
				if (i > 0)
					helpStr << '\n';
				helpStr << Colors::Info << "    - " << Colors::Usage << '\'' << keyString << '\'' << Colors::Info;
				helpStr << std::string(largestStrlen - keyString.size(), ' ') << '|';
				auto& help = key->getHelp();
				if (!help.getDesc().empty()) {
					helpStr << ' ' << Colors::Info << help.getDesc() << '\n';
					if (!help.getNote().empty()) {
						helpStr << std::string(8 + largestStrlen, ' ') << "|    ";
						AddNote(helpStr, help.getNote());
					}
				} else if (!help.getNote().empty()) {
					helpStr << ' ';
					AddNote(helpStr, help.getNote());
				}
			}
		}

		context.addMessage(helpStr.str(), true);
	}

	std::string Help::formatKey(const Key& key) const {
		std::string str = key.getKey();

		auto& values = key.getValues();
		if (!values.empty()) {
			str += ' ';
			bool space = false;
			for (auto& value : values) {
				if (space)
					str += ' ';
				space = true;

				auto mode = value.getMode();
				switch (mode) {
				case EValueMode::Required:
					[[fallthrough]];
				case EValueMode::MultiRequired:
					str += "[";
					break;
				case EValueMode::Optional:
					[[fallthrough]];
				case EValueMode::Multi:
					str += "(";
					break;
				}

				str += value.getValue();

				switch (mode) {
				case EValueMode::Required:
					str += "]";
					break;
				case EValueMode::Optional:
					str += ")";
					break;
				case EValueMode::MultiRequired:
					str += " ...]";
					break;
				case EValueMode::Multi:
					str += " ...)";
					break;
				}
			}
		}
		return str;
	}
} // namespace CommonCLI::KeyValue::Help