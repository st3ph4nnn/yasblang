#include <stdio.h>

#include <fstream>
#include <string>
#include <vector>

#include "utilities/linenoise.hpp"

#include "components/parser.hpp"

namespace args {
	bool shell = true;
	std::string file_name;
}

void handle_args(int argc, char *argv[]) {
	std::vector<std::string> args(argv + 1, argv + argc);

	for (int i = 0; i < args.size(); i++) {
		if (args[i] == "run") {
			if (i+1 > args.size())
				goto wrong;

			args::file_name = args[i+1];
			args::shell = false;
			i++;
			continue;
		}
	}

	return;

wrong:
	printf("\n[ERROR] arguments were used in the wrong way.\n");
	printf("[HINT] how to use: yasb (for the shell) or yasb run example.yasb (to run a file)\n");
	exit(0);
}

int main(int argc, char *argv[]) {
	handle_args(argc, argv);

	printf("                               __        __                               \n");
	printf("                              /  |      /  |                              \n");
	printf(" __    __   ______    _______ $$ |____  $$ |  ______   _______    ______  \n");
	printf(R"(/  |  /  | /      \  /       |$$      \ $$ | /      \ /       \  /      \)");
	printf("\n$$ |  $$ | $$$$$$  |/$$$$$$$/ $$$$$$$  |$$ | $$$$$$  |$$$$$$$  |/$$$$$$  |\n");
	printf(R"($$ |  $$ | /    $$ |$$      \ $$ |  $$ |$$ | /    $$ |$$ |  $$ |$$ |  $$ |)");
	printf("\n");
	printf(R"($$ \__$$ |/$$$$$$$ | $$$$$$  |$$ |__$$ |$$ |/$$$$$$$ |$$ |  $$ |$$ \__$$ |)");
	printf("\n$$    $$ |$$    $$ |/     $$/ $$    $$/ $$ |$$    $$ |$$ |  $$ |$$    $$ |\n");
	printf(" $$$$$$$ | $$$$$$$/ $$$$$$$/  $$$$$$$/  $$/  $$$$$$$/ $$/   $$/  $$$$$$$ |\n");
	printf(R"(/  \__$$ |                                                      /  \__$$ |)");
	printf("\n$$    $$/                                                       $$    $$/ \n");
	printf(" $$$$$$/                                                         $$$$$$/  \n\n\n");

	printf("info: yasblang: version 1.0.0\n");
	printf("description: (y)et (a)nother (s)tack (b)ased programming (lang)uage\n");
	printf("developed by: stephan\n");
	printf("bug reporting: stephan@schizo.gq\n\n");

	if (args::shell) {

		while (1) {
			std::string str;
			bool quit = linenoise::Readline("yasb > ", str);

			if (quit)
				return 0;

			parser parser(str, true);
			parser.parse();
		}
	} else {
		printf("[INFO] running: %s\n\n", args::file_name);
		parser parser(args::file_name);
		parser.parse();
	}

	return 0;
}