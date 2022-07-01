#pragma once
#include "lexer.hpp"
#include "../language.hpp"

#include <cstring>
#include <sstream>
#include <algorithm>

std::vector<std::string> tokenize(std::string const &str, const char delim) {
    std::stringstream ss(str);
    std::vector<std::string> out;
 
    std::string s;
    while (std::getline(ss, s, delim)) {
    	s.erase(std::remove(s.begin(), s.end(), '\t'), s.end());
        out.push_back(s);
    }

    return out;
}

class parser {
public:
	std::ifstream file;
	std::string file_name;
	std::string line;
	bool shell = false;
	std::string shell_str;
	int line_num = 0;

	parser(std::string shell_str, bool shell) : shell_str(shell_str), shell(shell) {}

	parser(std::string file_name) : file_name(file_name) { 
		this->file = std::ifstream(file_name);
	};

	std::vector<std::vector<token>> get_line_tokens() {
		if (shell) {
			std::vector<std::vector<token>> tokens;
			std::vector<std::string> split = tokenize(shell_str, ' ');
			for (auto i : split) {
				lexer lexer(i);
				tokens.emplace_back(lexer.make_tokens());
			}

			return tokens;
		}

		file = std::ifstream(file_name);
		std::vector<std::vector<token>> tokens;
		while (std::getline(this->file, this->line)) {
			std::vector<std::string> split = tokenize(this->line, ' ');
			for (auto i : split) {
				lexer lexer(i);
				tokens.emplace_back(lexer.make_tokens());
			}
			line_num++;
		}

		return tokens;
	}

	void parse() {
		std::vector<std::vector<token>> tokens = this->get_line_tokens();
		for (int i = 0; i < tokens.size(); i++) {
			for (int j = 0; j < tokens[i].size(); j++) {
				switch (tokens[i][j].type) {
					case token_type::v_num: num(tokens[i][j]); break;
					case token_type::v_str: str(tokens[i][j]); break;

					case token_type::keyword: handle_keywords(tokens[i][j]); break;

					case operations::add:
					case operations::substract:
					case operations::divide:
					case operations::multiply: 
					case operations::power:
					case operations::modulo: handle_math(tokens[i][j]); break;

					case symbols::equal:
					case symbols::greater_than:
					case symbols::lower_than: handle_symbols(tokens[i][j]); break;
			    }
			}
		}
	}
};