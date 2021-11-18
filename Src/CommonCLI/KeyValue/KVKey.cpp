#include "CommonCLI/KeyValue/KVKey.h"

#include <utility>

namespace CommonCLI::KeyValue {
	Message::Message()
	    : m_Str(""), m_Error(false) { }

	Message::Message(const std::string& str, bool error)
	    : m_Str(str), m_Error(error) { }

	Message::Message(std::string&& str, bool error)
	    : m_Str(std::move(str)), m_Error(error) { }

	HandlerContext::HandlerContext(Handler& handler, std::size_t argCount, const char** args)
	    : m_Handler(handler), m_ArgCount(argCount), m_Args(args) { }

	void HandlerContext::addMessage(const std::string& message, bool error) {
		m_Messages.emplace_back(message, error);
	}

	void HandlerContext::addMessage(std::string&& message, bool error) {
		m_Messages.emplace_back(std::move(message), error);
	}

	Value::Value(const std::string& value, EValueMode mode, const std::initializer_list<std::string_view>& possibleValues, const Help::Info& help)
	    : m_Value(value), m_Mode(mode), m_PossibleValues(possibleValues.size()), m_Help(help) {
		std::size_t i = 0;
		for (auto& possibleValue : possibleValues) {
			m_PossibleValues[i] = possibleValue;
			++i;
		}
	}

	Value::Value(std::string&& value, EValueMode mode, std::vector<std::string>&& possibleValues, Help::Info&& help)
	    : m_Value(std::move(value)), m_Mode(mode), m_PossibleValues(std::move(possibleValues)), m_Help(std::move(help)) { }

	Key::Key(const std::string& key, KeyCallback callback, const std::initializer_list<Value>& values, const Help::Info& help)
	    : m_Key(key), m_Values(values), m_Help(help), m_Callback(callback) { }

	Key::Key(std::string&& key, KeyCallback&& callback, std::vector<Value>&& values, Help::Info&& help)
	    : m_Key(std::move(key)), m_Values(std::move(values)), m_Help(std::move(help)), m_Callback(std::move(callback)) { }

	void Key::invoke(HandlerContext& context, const std::vector<std::string_view>& values, std::size_t& usedValueCount) {
		if (m_Callback)
			m_Callback(*this, context, values, usedValueCount);
	}
} // namespace CommonCLI::KeyValue