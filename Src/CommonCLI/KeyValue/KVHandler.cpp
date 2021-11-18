#include "CommonCLI/KeyValue/KVHandler.h"
#include "CommonCLI/Colors.h"

#include <sstream>
#include <utility>

static bool StringStartsWith(std::string_view a, std::string_view b) {
	if (b.size() > a.size())
		return false;

	for (std::size_t i = 0; i < b.size(); ++i)
		if (a[i] != b[i])
			return false;
	return true;
}

namespace CommonCLI::KeyValue {
	static void ArgValueErrorMessage(std::ostringstream& str, std::string_view key, const Value& value, std::size_t keyIndex, std::size_t valueIndex) {
		str << Colors::Error << "Value " << Colors::Arg << '\'' << value.getValue() << '\'' << Colors::Error << " at " << Colors::Arg << '\'' << valueIndex + 1 << '\'' << Colors::Error << " of key " << Colors::Arg << '\'' << key << '\'' << Colors::Error << " at " << Colors::Arg << '\'' << keyIndex + 1 << '\'' << Colors::Error;
	}

	ProcessedArgument::ProcessedArgument(std::string_view arg)
	    : m_Arg(arg), m_Present(false) { }

	void ProcessedArgument::setPresent() {
		m_Present = true;
	}

	void ProcessedArgument::setValues(std::vector<std::string>&& values) {
		m_Values = std::move(values);
	}

	ProcessedArguments::ProcessedArguments(std::string_view procCall, std::vector<ProcessedArgument>&& processedArgs, std::vector<Message>&& messages, std::vector<std::string>&& defaultValues)
	    : m_ProcCall(procCall), m_ProcessedArgs(std::move(processedArgs)), m_Messages(std::move(messages)), m_DefaultValues(std::move(defaultValues)) { }

	Handler::Handler(std::string_view programName, std::string_view programDesc, const Version::Version& version)
	    : ::CommonCLI::Handler(programName, programDesc), m_Version(version) {
		addDefaultKeys();
	}

	Handler::Handler(std::string&& programName, std::string&& programDesc, Version::Version&& version)
	    : ::CommonCLI::Handler(std::move(programName), std::move(programDesc)), m_Version(std::move(version)) {
		addDefaultKeys();
	}

	ProcessedArguments Handler::handle(std::size_t argc, const char** argv) {
		std::vector<ProcessedArgument> processedArgs;
		processedArgs.reserve(m_Keys.size());
		for (auto& key : m_Keys)
			processedArgs.emplace_back(key.getKey());

		HandlerContext context = { *this, argc, argv };
		std::vector<std::string> defaultValues;

		std::size_t keyIndex = 0;
		for (std::size_t i = 1; i < argc; ++i, ++keyIndex) {
			std::string_view currentArg = argv[i];
			if (!StringStartsWith(currentArg, "--")) {
				defaultValues.emplace_back(currentArg);
				continue;
			}

			std::string_view currentKey = currentArg.substr(2);
			if (currentKey.empty())
				continue;

			auto key = getKey(currentKey);
			if (!key) {
				std::ostringstream str;
				str << Colors::Warn << "Unknown key " << Colors::Arg << '\'' << currentKey << '\'';
				context.addMessage(str.str());
				break;
			}

			auto& keyValues = key->getValues();
			std::vector<std::string_view> values;
			std::size_t usedValueCount = 0;

			std::size_t k = 1;

			bool hasMulti   = false;
			bool required   = false;
			bool wrongValue = false;
			for (std::size_t j = 0; j < keyValues.size(); ++j) {
				auto& keyValue = keyValues[j];
				switch (keyValue.getMode()) {
				case EValueMode::Required:
					usedValueCount = std::max(usedValueCount, usedValueCount + 1);
					required       = true;
					[[fallthrough]];
				case EValueMode::Optional:
					if ((i + k) < argc) {
						std::string_view currentValue = argv[i + k];
						if (!StringStartsWith(currentValue, "--")) {
							auto& keyPossibleValues = keyValue.getPossibleValues();
							if (!keyPossibleValues.empty()) {
								bool found = false;
								for (auto& posVal : keyPossibleValues) {
									if (posVal == currentValue) {
										found = true;
										break;
									}
								}

								if (!found) {
									if (required) {
										std::ostringstream str;
										ArgValueErrorMessage(str, currentKey, keyValue, keyIndex, i + k);
										str << " is not one of the possible values";
										context.addMessage(str.str());
										wrongValue = true;
									}
									break;
								}
							}

							values.push_back(currentValue);
							required = false;
							++k;
						}
					}
					break;
				case EValueMode::MultiRequired:
					usedValueCount = std::max(usedValueCount, usedValueCount + 1);
					required       = true;
					[[fallthrough]];
				case EValueMode::Multi:
					hasMulti = true;
					for (; (i + k) < argc; ++k) {
						std::string_view currentValue = argv[i + k];
						if (StringStartsWith(currentValue, "--"))
							break;

						auto& keyPossibleValues = keyValue.getPossibleValues();
						if (!keyPossibleValues.empty()) {
							bool found = false;
							for (auto& posVal : keyPossibleValues) {
								if (posVal == currentValue) {
									found = true;
									break;
								}
							}

							if (!found) {
								if (required) {
									std::ostringstream str;
									ArgValueErrorMessage(str, currentKey, keyValue, keyIndex, i + k);
									str << " is not one of the possible values";
									context.addMessage(str.str());
									wrongValue = true;
								}
								break;
							}
						}

						values.push_back(currentValue);
						required = false;
					}
					break;
				}

				if (required && !wrongValue) {
					std::ostringstream str;
					ArgValueErrorMessage(str, currentKey, keyValue, keyIndex, i + k);
					str << " missing required value";
					context.addMessage(str.str());
					break;
				}
			}

			if (!required) {
				key->invoke(context, values, usedValueCount);

				for (auto& processedArg : processedArgs) {
					if (processedArg.getArg() == currentKey) {
						processedArg.setPresent();
						std::vector<std::string> actualValues(std::min(usedValueCount, values.size()));
						for (std::size_t l = 0; l < actualValues.size(); ++l)
							actualValues[l] = values[l];
						processedArg.setValues(std::move(actualValues));
						break;
					}
				}
			}

			i += usedValueCount;
		}

		return { argv[0], std::move(processedArgs), std::move(context.getMessages()), std::move(defaultValues) };
	}

	void Handler::addKey(const Key& key) {
		m_Keys.push_back(key);
	}

	void Handler::addKey(Key&& key) {
		m_Keys.emplace_back(std::move(key));
	}

	Key* Handler::getKey(std::string_view key) const {
		for (auto& k : m_Keys)
			if (k.getKey() == key)
				return const_cast<Key*>(&k);
		return nullptr;
	}

	void Handler::addDefaultKeys() {
		addKey(Key {
		    "help",
		    &Help::Help::invoke,
		    &m_Help,
		    std::vector<Value> {
		        { "key",
		          EValueMode::Multi } },
		    { "Shows this help page",
		      "you can give this argument the same key multiple times" } });
		addKey(Key {
		    "version",
		    &Version::Version::invoke,
		    &m_Version,
		    std::vector<Value> {
		        { "silent",
		          EValueMode::Optional,
		          std::vector<std::string> { "silent" } } },
		    { "Shows the version of this application",
		      "Giving 'silent' as a parameter will only print the version number" } });
	}
} // namespace CommonCLI::KeyValue