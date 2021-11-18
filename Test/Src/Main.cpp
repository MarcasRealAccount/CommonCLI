#include <ANSI/Graphics.h>
#include <CommonCLI/Colors.h>
#include <CommonCLI/KeyValue/KVHandler.h>

#include <iostream>
#include <utility>

int main(int argc, char** argv) {
	using namespace CommonCLI::KeyValue;
	Handler handler("TestCLI", "", { 1, 0, 0, "", "alpha" });

	handler.addKey({ "test" });
	handler.addKey(Key {
	    "another-test",
	    nullptr,
	    std::vector<Value> {
	        { "he",
	          CommonCLI::KeyValue::EValueMode::MultiRequired,
	          std::vector<std::string> { "he",
	                                     "ree" } } },
	    Help::Info { "",
	                 "A note on its own?" } });

	auto result    = handler.handle(argc, const_cast<const char**>(argv));
	auto& messages = result.getMessages();
	bool exit      = false;
	for (auto& message : messages) {
		if (message.isError()) {
			std::cerr << message.getStr() << '\n';
			exit = true;
		} else {
			std::cout << message.getStr() << '\n';
		}
	}
	std::cout << ANSI::GraphicsReset;

	auto& defaultValues = result.getDefaultValues();
	bool first          = true;
	for (auto& defaultValue : defaultValues) {
		if (!first) {
			std::cout << CommonCLI::Colors::Info << ", ";
		}
		first = false;
		std::cout << CommonCLI::Colors::Arg << '\'' << defaultValue << '\'';
	}
	if (exit) return EXIT_FAILURE;

	return EXIT_SUCCESS;
}