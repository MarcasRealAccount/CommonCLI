#pragma once

#include "KVHelp.h"

#include <cstddef>
#include <cstdint>

#include <concepts>
#include <functional>
#include <initializer_list>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

namespace CommonCLI::KeyValue {
	class Handler;
	struct Key;

	struct Message {
	public:
		Message();
		Message(const std::string& str, bool error = false);
		Message(std::string&& str, bool error = false);

		auto& getStr() const { return m_Str; }
		auto isError() const { return m_Error; }

	private:
		std::string m_Str;
		bool m_Error;
	};

	struct HandlerContext {
	public:
		HandlerContext(Handler& handler, std::size_t argCount, const char** args);

		void addMessage(const std::string& message, bool error = false);
		void addMessage(std::string&& message, bool error = false);

		auto& getHandler() { return m_Handler; }
		auto& getHandler() const { return m_Handler; }
		auto& getMessages() { return m_Messages; }
		auto& getMessages() const { return m_Messages; }
		auto getArgCount() const { return m_ArgCount; }
		auto getArgs() const { return m_Args; }

	private:
		Handler& m_Handler;
		std::vector<Message> m_Messages;
		std::size_t m_ArgCount;
		const char** m_Args;
	};

	using KeyCallback = std::function<void(Key& self, HandlerContext& context, const std::vector<std::string_view>& values, std::size_t& usedValueCount)>;
	template <class T>
	concept RandomKeyCallback = !std::same_as<T, KeyCallback> && !std::is_function_v<T> && !std::is_null_pointer_v<T>;

	enum class EValueMode {
		Required,      //Always 1
		Optional,      //?
		MultiRequired, //+
		Multi          //*
	};

	struct Value {
	public:
		Value(const std::string& value, EValueMode mode = EValueMode::Required, const std::initializer_list<std::string_view>& possibleValues = {}, const Help::Info& help = {});
		Value(std::string&& value, EValueMode mode = EValueMode::Required, std::vector<std::string>&& possibleValues = {}, Help::Info&& help = {});

		auto& getValue() const { return m_Value; }
		auto getMode() const { return m_Mode; }
		auto& getPossibleValues() const { return m_PossibleValues; }
		auto& getHelp() const { return m_Help; }

	private:
		std::string m_Value;
		EValueMode m_Mode;
		std::vector<std::string> m_PossibleValues;
		Help::Info m_Help;
	};

	struct Key {
	public:
		Key(const std::string& key, KeyCallback callback = nullptr, const std::initializer_list<Value>& values = {}, const Help::Info& help = {});
		Key(std::string&& key, KeyCallback&& callback = nullptr, std::vector<Value>&& values = {}, Help::Info&& help = {});
		template <RandomKeyCallback Callback>
		Key(const std::string& key, Callback&& callback, const std::initializer_list<Value>& values = {}, const Help::Info& help = {})
		    : Key(key,
		          static_cast<KeyCallback>(std::bind(std::forward<Callback&&>(callback), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)),
		          values,
		          help) { }
		template <RandomKeyCallback Callback, class T>
		Key(const std::string& key, Callback&& callback, T* object, const std::initializer_list<Value>& values = {}, const Help::Info& help = {})
		    : Key(key,
		          static_cast<KeyCallback>(std::bind(std::forward<Callback&&>(callback), object, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)),
		          values,
		          help) { }
		template <RandomKeyCallback Callback>
		Key(std::string&& key, Callback&& callback, std::vector<Value>&& values = {}, Help::Info&& help = {})
		    : Key(std::move(key),
		          static_cast<KeyCallback>(std::bind(std::forward<Callback&&>(callback), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)),
		          std::move(values),
		          std::move(help)) { }
		template <RandomKeyCallback Callback, class T>
		Key(std::string&& key, Callback&& callback, T* object, std::vector<Value>&& values = {}, Help::Info&& help = {})
		    : Key(std::move(key),
		          static_cast<KeyCallback>(std::bind(std::forward<Callback&&>(callback), object, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)),
		          std::move(values),
		          std::move(help)) { }

		auto& getKey() const { return m_Key; }
		auto& getValues() const { return m_Values; }
		auto& getHelp() const { return m_Help; }

		void invoke(HandlerContext& context, const std::vector<std::string_view>& values, std::size_t& usedValueCount);

	private:
		std::string m_Key;
		std::vector<Value> m_Values;
		Help::Info m_Help;
		KeyCallback m_Callback;
	};
} // namespace CommonCLI::KeyValue