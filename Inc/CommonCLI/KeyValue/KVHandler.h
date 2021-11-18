#pragma once

#include "CommonCLI/Handler.h"
#include "KVHelp.h"
#include "KVKey.h"
#include "KVVersion.h"

#include <vector>

namespace CommonCLI::KeyValue {
	struct ProcessedArgument {
	public:
		ProcessedArgument(std::string_view arg);

		auto& getArg() const { return m_Arg; }
		bool isPresent() const { return m_Present; }
		auto& getValues() const { return m_Values; }

		void setPresent();
		void setValues(std::vector<std::string>&& values);

	private:
		std::string m_Arg;
		bool m_Present;
		std::vector<std::string> m_Values;
	};

	struct ProcessedArguments {
	public:
		ProcessedArguments(std::string_view procCall, std::vector<ProcessedArgument>&& processedArgs, std::vector<Message>&& messages, std::vector<std::string>&& defaultValues);

		auto& getProcCall() const { return m_ProcCall; }
		auto& getProcessedArgs() const { return m_ProcessedArgs; }
		auto& getMessages() const { return m_Messages; }
		auto& getDefaultValues() const { return m_DefaultValues; }

	private:
		std::string m_ProcCall;
		std::vector<ProcessedArgument> m_ProcessedArgs;
		std::vector<Message> m_Messages;
		std::vector<std::string> m_DefaultValues;
	};

	class Handler : public ::CommonCLI::Handler {
	public:
		Handler(std::string_view programName, std::string_view programDesc = "", const Version::Version& version = { 0, 1, 0 });
		Handler(std::string&& programName, std::string&& programDesc, Version::Version&& version);

		ProcessedArguments handle(std::size_t argc, const char** argv);

		virtual EHandler getType() override { return EHandler::KeyValue; }

		void addKey(const Key& key);
		void addKey(Key&& key);
		Key* getKey(std::string_view key) const;

		auto& getKeys() const { return m_Keys; }
		auto& getHelp() const { return m_Help; }
		auto& getVersion() const { return m_Version; }

	private:
		void addDefaultKeys();

	private:
		std::vector<Key> m_Keys;
		Help::Help m_Help;
		Version::Version m_Version;
	};
} // namespace CommonCLI::KeyValue