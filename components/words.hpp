#pragma once
#include <vector>
#include <sstream>
#include <algorithm>

#include "tokens.hpp"
#include "../utilities/error_handling.hpp"

#include "../language.hpp"

class word_class {
public:
	std::string name;
	std::string contents;

	word_class() {};
	word_class(std::string name, std::string contents) : name(name), contents(contents) {};

	void parse_word() {
		std::vector<std::vector<token>> tokens;
		lexer lexer(contents);
		tokens.emplace_back(lexer.make_tokens());

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

					case token_type::word: error("word", "attempt to define a word in a word"); break;
			    }
			}
		}
	}
};