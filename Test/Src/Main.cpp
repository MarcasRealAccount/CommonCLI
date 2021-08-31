#include <CommonCLI.h>

#include <iostream>

int main(int argc, char** argv) {
	CommonCLI::KeyValue::Handler handler("TestCLI");

	handler.getVersion().setVersion(1, 0, 0, {}, "alpha");

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
	if (exit) return EXIT_FAILURE;

	return EXIT_SUCCESS;
}