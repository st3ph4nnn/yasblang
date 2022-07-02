#pragma once
#include "tokens.hpp"

class lexer {
public:
    std::string txt;
    int pos = -1;
    char current_character = 0;

    void advance() {
        this->pos++;
        if (this->txt.length() > pos)
            current_character = this->txt[pos];
        else
            current_character = 0;
    }

    lexer(std::string text) : txt(text) {
        this->advance();
    }

    token get_number() {
        std::string num_str;
        bool fl = false;

        if (current_character == '-') {
            num_str += "-";
            this->advance();
        }

        while (current_character != 0 && ((current_character >= '0' && current_character <= '9') || current_character == '.' || current_character == '-')) {
            if (current_character == '.') {
                if (fl) break;
                num_str += ".";
                fl = true;
            } else {
                num_str += current_character;
            }
            this->advance();
        }

        return token(token_type::v_num, std::stod(num_str), num_str);
    }

    token get_str() {
    	std::string str;

    	while (current_character != 0 && current_character != '\"') {
    		str += current_character;
    		this->advance();
    	}
        
    	return token(token_type::v_str, 0, str);
    }

    token get_keyword() {
        std::string str;

        while (current_character != 0 && current_character != ' ') {
            str += current_character;
            this->advance();
        }

        return token(token_type::keyword, 0, str);
    }

    bool part_of_number() {
        if (current_character == '-') {
            if (pos+1 < txt.length()) {
                if (txt[pos+1] >= '0' && txt[pos+1] <= '9')
                    return true;
            }
        }

        return false;
    }

    void skip_to_next() {
        while (this->current_character != ' ')
            this->advance();

        if (this->current_character == ' ')
            this->advance();
    }

    std::vector<token> make_tokens() {
        std::vector<token> tokens;

        while (current_character != 0) {
            if (current_character == ' ' || current_character == '\t')
                this->advance();

            if (current_character >= '0' && current_character <= '9')
                tokens.emplace_back(this->get_number());

            if (current_character == '\"') {
                this->advance();
                tokens.emplace_back(this->get_str());
            }

            if (current_character >= 'a' && current_character <= 'z' || current_character == '.') {
                tokens.emplace_back(this->get_keyword());
            }

            switch (current_character) {
            case '-':
                if (part_of_number()) {
                    tokens.emplace_back(this->get_number());
                    break;
                }

                tokens.emplace_back(token(operations::substract, 0, "-"));
                break;
            case '+':
                tokens.emplace_back(token(operations::add, 0, "+"));
                break;
            case '*':
                tokens.emplace_back(token(operations::multiply, 0, "*"));
                break;
            case '/':
                tokens.emplace_back(token(operations::divide, 0, "/"));
                break;
            case '^':
                tokens.emplace_back(token(operations::power, 0, "^"));
                break;
            case '%':
                tokens.emplace_back(token(operations::modulo, 0, "%"));
                break;
            case '=':
                tokens.emplace_back(token(symbols::equal, 0, "="));
                break;
            case '>':
                tokens.emplace_back(token(symbols::greater_than, 0, ">"));
                break;
            case '<':
                tokens.emplace_back(token(symbols::lower_than, 0, "<"));
                break;
            case ':':
                tokens.emplace_back(token(token_type::word, 0, ":"));
                break;
            case ';':
                tokens.emplace_back(token(token_type::end, 0, ";"));
                break;
            }

            this->advance();
        }

        return tokens;
    }
};