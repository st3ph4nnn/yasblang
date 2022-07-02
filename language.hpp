#pragma once
#include <stack>
#include <vector>
#include <iostream>
#include <cmath>

#include "components/tokens.hpp"
#include "utilities/error_handling.hpp"

#include "components/parser.hpp"

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

namespace stacks {
	std::stack<int> int_stack;
	std::stack<double> double_stack;
	std::stack<std::string> str_stack;
	int selected = 0;
}

void num(token tk) {
	int first_decimal = (int)(tk.value*10)%10;
	if (first_decimal == 0) {
		stacks::int_stack.push((int)tk.value);
	} else {
		stacks::double_stack.push(tk.value);
	}
}

void str(token tk) {
	stacks::str_stack.push(tk.str);
}

void handle_symbols(token tk) {
	switch (tk.type) {
		case symbols::equal: {
			switch (stacks::selected) {
				case 0: {
					if (stacks::int_stack.size() <= 1)
						error("math", "not enough stack members for equal checking. (integer stack)");

					int first = stacks::int_stack.top();
					stacks::int_stack.pop();
					int second = stacks::int_stack.top();
					stacks::int_stack.pop();
					printf("%d\n", first==second);
					stacks::int_stack.push(second);
					stacks::int_stack.push(first);
					break;
				}
				case 1: {
					if (stacks::double_stack.size() <= 1)
						error("math", "not enough stack members for equal checking. (floating point int stack)");

					double first = stacks::double_stack.top();
					stacks::double_stack.pop();
					double second = stacks::double_stack.top();
					stacks::double_stack.pop();
					printf("%d\n", first==second);
					stacks::double_stack.push(second);
					stacks::double_stack.push(first);
					break;
				}
				case 2: {
					if (stacks::str_stack.size() <= 1)
						error("math", "not enough stack members for equal checking. (string stack)");

					std::string first = stacks::str_stack.top();
					stacks::str_stack.pop();
					std::string second = stacks::str_stack.top();
					stacks::str_stack.pop();

					printf("%d\n", first==second);

					stacks::str_stack.push(second);
					stacks::str_stack.push(first);
					break;
				}
			}
			break;
		}
		case symbols::greater_than: {
			switch (stacks::selected) {
				case 0: {
					if (stacks::int_stack.size() <= 1)
						error("math", "not enough stack members for greater than checking. (integer stack)");

					int first = stacks::int_stack.top();
					stacks::int_stack.pop();
					int second = stacks::int_stack.top();
					stacks::int_stack.pop();
					printf("%d\n", (first > second));
					stacks::int_stack.push(second);
					stacks::int_stack.push(first);
					break;
				}
				case 1: {
					if (stacks::double_stack.size() <= 1)
						error("math", "not enough stack members for greater than checking. (floating point int stack)");

					double first = stacks::double_stack.top();
					stacks::double_stack.pop();
					double second = stacks::double_stack.top();
					stacks::double_stack.pop();
					printf("%d\n", (first > second));
					stacks::double_stack.push(second);
					stacks::double_stack.push(first);
					break;
				}
				case 2: {
					if (stacks::str_stack.size() <= 1)
						error("math", "not enough stack members for greater than checking. (string stack)");

					std::string first = stacks::str_stack.top();
					stacks::str_stack.pop();
					std::string second = stacks::str_stack.top();
					stacks::str_stack.pop();

					printf("%d\n", (first > second));

					stacks::str_stack.push(second);
					stacks::str_stack.push(first);
					break;
				}
			}
			break;
		}
		case symbols::lower_than: {
			switch (stacks::selected) {
				case 0: {
					if (stacks::int_stack.size() <= 1)
						error("math", "not enough stack members for lower than checking. (integer stack)");

					int first = stacks::int_stack.top();
					stacks::int_stack.pop();
					int second = stacks::int_stack.top();
					stacks::int_stack.pop();
					printf("%d\n", (first < second));

					stacks::int_stack.push(second);
					stacks::int_stack.push(first);
					break;
				}
				case 1: {
					if (stacks::double_stack.size() <= 1)
						error("math", "not enough stack members for lower than checking. (floating point int stack)");

					double first = stacks::double_stack.top();
					stacks::double_stack.pop();
					double second = stacks::double_stack.top();
					stacks::double_stack.pop();
					printf("%d\n", (first < second));

					stacks::double_stack.push(second);
					stacks::double_stack.push(first);
					break;
				}
				case 2: {
					if (stacks::str_stack.size() <= 1)
						error("math", "not enough stack members for lower than checking. (string stack)");

					std::string first = stacks::str_stack.top();
					stacks::str_stack.pop();
					std::string second = stacks::str_stack.top();
					stacks::str_stack.pop();

					printf("%d\n", (first < second));

					stacks::str_stack.push(second);
					stacks::str_stack.push(first);
					break;
				}
			}
			break;
		}
	}
}

void handle_math(token tk) {
	switch (tk.type) {
		case operations::add: {
			switch (stacks::selected) {
				case 0: {
					if (stacks::int_stack.size() <= 1)
						error("math", "not enough stack members for adding. (integer stack)");

					int first = stacks::int_stack.top();
					stacks::int_stack.pop();
					int second = stacks::int_stack.top();
					stacks::int_stack.pop();
					stacks::int_stack.push(first+second);
					break;
				}
				case 1: {
					if (stacks::double_stack.size() <= 1)
						error("math", "not enough stack members for adding. (floating point int stack)");

					double first = stacks::double_stack.top();
					stacks::double_stack.pop();
					double second = stacks::double_stack.top();
					stacks::double_stack.pop();
					stacks::double_stack.push(first+second);
					break;
				}
				case 2: {
					if (stacks::str_stack.size() <= 1)
						error("math", "not enough stack members for adding. (string stack)");

					std::string first = stacks::str_stack.top();
					stacks::str_stack.pop();
					std::string second = stacks::str_stack.top();
					stacks::str_stack.pop();

					first += second;

					stacks::str_stack.push(first);
					break;
				}
			}
			break;
		}
		case operations::substract: {
			switch (stacks::selected) {
				case 0: {
					if (stacks::int_stack.size() <= 1)
						error("math", "not enough stack members for substracting. (integer stack)");

					int first = stacks::int_stack.top();
					stacks::int_stack.pop();
					int second = stacks::int_stack.top();
					stacks::int_stack.pop();
					stacks::int_stack.push(first-second);
					break;
				}
				case 1: {
					if (stacks::double_stack.size() <= 1)
						error("math", "not enough stack members for substracting. (floating point int stack)");

					double first = stacks::double_stack.top();
					stacks::double_stack.pop();
					double second = stacks::double_stack.top();
					stacks::double_stack.pop();
					stacks::double_stack.push(first-second);
					break;
				}
				case 2: {
					if (stacks::str_stack.size() <= 1)
						error("math", "not enough stack members for substracting. (string stack)");

					std::string first = stacks::str_stack.top();
					stacks::str_stack.pop();
					std::string second = stacks::str_stack.top();
					stacks::str_stack.pop();

					size_t pos = first.find(second);
					if (pos != std::string::npos) 
						first.erase(pos, second.length());

					stacks::str_stack.push(first);
					break;
				}
			}
			break;
		}
		case operations::multiply: {
			switch (stacks::selected) {
				case 0: {
					if (stacks::int_stack.size() <= 1)
						error("math", "not enough stack members for multplying. (integer stack)");

					int first = stacks::int_stack.top();
					stacks::int_stack.pop();
					int second = stacks::int_stack.top();
					stacks::int_stack.pop();
					stacks::int_stack.push(first*second);
					break;
				}
				case 1: {
					if (stacks::double_stack.size() <= 1)
						error("math", "not enough stack members for substracting. (floating point int stack)");

					double first = stacks::double_stack.top();
					stacks::double_stack.pop();
					double second = stacks::double_stack.top();
					stacks::double_stack.pop();
					stacks::double_stack.push(first*second);
					break;
				}
				case 2: {
					error("math", "multplying is not allowed on strings.");
					break;
				}
			}
			break;
		}
		case operations::divide: {
			switch (stacks::selected) {
				case 0: {
					if (stacks::int_stack.size() <= 1)
						error("math", "not enough stack members for division. (integer stack)");

					int first = stacks::int_stack.top();
					stacks::int_stack.pop();
					int second = stacks::int_stack.top();
					stacks::int_stack.pop();
					stacks::int_stack.push(first/second);
					break;
				}
				case 1: {
					if (stacks::double_stack.size() <= 1)
						error("math", "not enough stack members for division. (floating point int stack)");

					double first = stacks::double_stack.top();
					stacks::double_stack.pop();
					double second = stacks::double_stack.top();
					stacks::double_stack.pop();
					stacks::double_stack.push(first/second);
					break;
				}
				case 2: {
					error("math", "division is not allowed on strings.");
					break;
				}
			}
			break;
		}
		case operations::power: {
			switch (stacks::selected) {
				case 0: {
					if (stacks::int_stack.size() <= 1)
						error("math", "not enough stack members for power. (integer stack)");

					int first = stacks::int_stack.top();
					stacks::int_stack.pop();
					int second = stacks::int_stack.top();
					stacks::int_stack.pop();
					stacks::int_stack.push(pow(first, second));
					break;
				}
				case 1: {
					if (stacks::double_stack.size() <= 1)
						error("math", "not enough stack members for power. (floating point int stack)");

					double first = stacks::double_stack.top();
					stacks::double_stack.pop();
					double second = stacks::double_stack.top();
					stacks::double_stack.pop();
					stacks::double_stack.push(pow(first, second));
					break;
				}
				case 2: {
					error("math", "power is not allowed on strings.");
					break;
				}
			}
			break;
		}
		case operations::modulo: {
			switch (stacks::selected) {
				case 0: {
					if (stacks::int_stack.size() <= 1)
						error("math", "not enough stack members for mod. (integer stack)");

					int first = stacks::int_stack.top();
					stacks::int_stack.pop();
					int second = stacks::int_stack.top();
					stacks::int_stack.pop();
					stacks::int_stack.push(first % second);
					break;
				}
				case 1: {
					error("math", "mod is not allowed on floats.");
					break;
				}
				case 2: {
					error("math", "mod is not allowed on strings.");
					break;
				}
			}
			break;
		}
	}
}

bool handle_keywords(token tk) {
	if (tk.str == "int") {
		stacks::selected = 0;
		return true;
	}

	if (tk.str == "float") {
		stacks::selected = 1;
		return true;
	}

	if (tk.str == "string") {
		stacks::selected = 2;
		return true;
	}

	if (tk.str == "print") {
		switch (stacks::selected) {
		case 0: {
			std::stack<int> copy = stacks::int_stack;
			int sz = copy.size();
			printf("\n%s\n\n", (sz == 0 ? "The integer stack is currently empty." : "[PRINT] integer stack:"));
			while (!copy.empty()) {
				if (sz == copy.size())
					printf("%d <--- TOP\n", copy.top());
				else
					printf("%d\n", copy.top());

				copy.pop();
			}
			break;
		}
		case 1: {
			std::stack<double> copy = stacks::double_stack;
			int sz = copy.size();
			printf("\n%s\n\n", (sz == 0 ? "The floating point integer stack is currently empty." : "[PRINT] floating point integer stack:"));
			while (!copy.empty()) {
				if (sz == copy.size())
					printf("%f <--- TOP\n", copy.top());
				else
					printf("%f\n", copy.top());

				copy.pop();
			}
			break;
		}
		case 2: {
			std::stack<std::string> copy = stacks::str_stack;
			int sz = copy.size();
			printf("\n%s\n\n", (sz == 0 ? "The string stack is currently empty." : "[PRINT] string stack:"));
			while (!copy.empty()) {
				if (sz == copy.size())
					printf("%s <--- TOP\n", copy.top().c_str());
				else
					printf("%s\n", copy.top().c_str());

				copy.pop();
			}
			break;
		}
	}
		return true;
	}

	if (tk.str == "exit" || tk.str == "quit")
		exit(0);

	if (tk.str == "clear") {
		switch (stacks::selected) {
			case 0: while (!stacks::int_stack.empty()) stacks::int_stack.pop(); break;
			case 1: while (!stacks::double_stack.empty()) stacks::double_stack.pop(); break;
			case 2: while (!stacks::str_stack.empty()) stacks::str_stack.pop(); break;
		}
		return true;
	}

	if (tk.str == "size" || tk.str == "length") {
		switch (stacks::selected) {
			case 0: {
				printf("int stack size: %d\n", stacks::int_stack.size());
				break;
			}
			case 1: {
				printf("double stack size: %d\n", stacks::double_stack.size());
				break;	
			}
			case 2: {
				printf("string stack size: %d\n", stacks::str_stack.size());
				break;
			}
		}
		return true;
	}

	if (tk.str == "pop" || tk.str == "drop") {
		switch (stacks::selected) {
			case 0: {
				if (stacks::int_stack.size() == 0)
					error("could not drop/pop the top element", "stack is empty. (integer stack)");
				stacks::int_stack.pop();
				break;
			}
			case 1: {
				if (stacks::double_stack.size() == 0)
					error("could not drop/pop the top element", "stack is empty. (floating point int stack)");
				stacks::double_stack.pop();
				break;	
			}
			case 2: {
				if (stacks::str_stack.size() == 0)
					error("could not drop/pop the top element", "stack is empty. (string stack)");
				stacks::str_stack.pop();
				break;
			}
		}
		return true;
	}

	if (tk.str == "dup") {
		switch (stacks::selected) {
			case 0: {
				if (stacks::int_stack.size() == 0)
					error("could not duplicate the top element", "stack is empty. (integer stack)");

				stacks::int_stack.push(stacks::int_stack.top());
				break;
			}
			case 1: {
				if (stacks::double_stack.size() == 0)
					error("could not duplicate the top element", "stack is empty. (floating point int stack)");

				stacks::double_stack.push(stacks::double_stack.top());
				break;
			}
			case 2: {
				if (stacks::str_stack.size() == 0)
					error("could not duplicate the top element", "stack is empty. (string stack)");

				stacks::str_stack.push(stacks::str_stack.top());
				break;
			}
		}
		return true;
	}

	if (tk.str == "top") {
		switch (stacks::selected) {
			case 0: {
				if (stacks::int_stack.size() == 0)
					error("could not print the top element", "stack is empty. (integer stack)");

				printf("%d\n", stacks::int_stack.top());
				break;
			}
			case 1: {
				if (stacks::double_stack.size() == 0)
					error("could not print the top element", "stack is empty. (floating point int stack)");

				printf("%f\n", stacks::double_stack.top());
				break;
			}
			case 2: {
				if (stacks::str_stack.size() == 0)
					error("could not print the top element", "stack is empty. (string stack)");

				printf("%s\n", stacks::str_stack.top().c_str());
				break;
			}
		}
		return true;
	}

	if (tk.str == ".") {
		switch (stacks::selected) {
			case 0: {
				if (stacks::int_stack.size() == 0)
					error("could not print the top element", "stack is empty. (integer stack)");

				printf("%d\n", stacks::int_stack.top());
				stacks::int_stack.pop();
				break;
			}
			case 1: {
				if (stacks::double_stack.size() == 0)
					error("could not print the top element", "stack is empty. (floating point int stack)");

				printf("%f\n", stacks::double_stack.top());
				stacks::double_stack.pop();
				break;
			}
			case 2: {
				if (stacks::str_stack.size() == 0)
					error("could not print the top element", "stack is empty. (string stack)");

				printf("%s\n", stacks::str_stack.top().c_str());
				stacks::str_stack.pop();
				break;
			}
		}
		return true;
	}

	if (tk.str == "negate") {
		switch (stacks::selected) {
			case 0: {
				if (stacks::int_stack.size() == 0)
					error("could not negate the top element", "stack is empty. (integer stack)");

				int top = stacks::int_stack.top();
				stacks::int_stack.pop();
				stacks::int_stack.push(-top);
				break;
			}
			case 1: {
				if (stacks::double_stack.size() == 0)
					error("could not negate the top element", "stack is empty. (floating point int stack)");

				double top = stacks::double_stack.top();
				stacks::double_stack.pop();
				stacks::double_stack.push(-top);
				break;
			}
			case 2: {
				error("math", "negation is not allowed on strings."); 
				break;	
			}
		}
		return true;
	}

	if (tk.str == "abs") {
		switch (stacks::selected) {
			case 0: {
				if (stacks::int_stack.size() == 0)
					error("could not absolute the top element", "stack is empty. (integer stack)");

				int top = stacks::int_stack.top();
				stacks::int_stack.pop();
				stacks::int_stack.push(std::abs(top));
				break;
			}
			case 1: {
				if (stacks::double_stack.size() == 0)
					error("could not absolute the top element", "stack is empty. (floating point int stack)");

				double top = stacks::double_stack.top();
				stacks::double_stack.pop();
				stacks::double_stack.push(std::abs(top));
				break;
			}
			case 2: {
				error("math", "absolution is not allowed on strings."); 
				break;	
			}
		}
		return true;
	}

	if (tk.str == "max") {
		switch (stacks::selected) {
			case 0: {
				if (stacks::int_stack.size() <= 1)
					error("could not max the top two elements", "not enough elements. (integer stack)");

				int first = stacks::int_stack.top();
				stacks::int_stack.pop();
				int second = stacks::int_stack.top();
				stacks::int_stack.pop();
				stacks::int_stack.push(std::max(first, second));
				break;
			}
			case 1: {
				if (stacks::double_stack.size() <= 1)
					error("could not max the top two elements", "not enough elements. (floating point int stack)");

				double first = stacks::double_stack.top();
				stacks::double_stack.pop();
				double second = stacks::double_stack.top();
				stacks::double_stack.pop();
				stacks::double_stack.push(std::max(first, second));
				break;
			}
			case 2: {
				if (stacks::str_stack.size() <= 1)
					error("could not max the top two elements", "not enough elements. (string stack)");

				std::string first = stacks::str_stack.top();
				stacks::str_stack.pop();
				std::string second = stacks::str_stack.top();
				stacks::str_stack.pop();

				stacks::str_stack.push((first.length() > second.length()) ? first : second);
				break;
			}
		}
		return true;
	}

	if (tk.str == "min") {
		switch (stacks::selected) {
			case 0: {
				if (stacks::int_stack.size() <= 1)
					error("could not min the top two elements", "not enough elements. (integer stack)");

				int first = stacks::int_stack.top();
				stacks::int_stack.pop();
				int second = stacks::int_stack.top();
				stacks::int_stack.pop();
				stacks::int_stack.push(std::min(first, second));
				break;
			}
			case 1: {
				if (stacks::double_stack.size() <= 1)
					error("could not min the top two elements", "not enough elements. (floating point int stack)");

				double first = stacks::double_stack.top();
				stacks::double_stack.pop();
				double second = stacks::double_stack.top();
				stacks::double_stack.pop();
				stacks::double_stack.push(std::min(first, second));
				break;
			}
			case 2: {
				if (stacks::str_stack.size() <= 1)
					error("could not min the top two elements", "not enough elements. (string stack)");

				std::string first = stacks::str_stack.top();
				stacks::str_stack.pop();
				std::string second = stacks::str_stack.top();
				stacks::str_stack.pop();

				stacks::str_stack.push((first.length() < second.length()) ? first : second);
				break;
			}
		}
		return true;
	}

	if (tk.str == "swap") {
				switch (stacks::selected) {
			case 0: {
				if (stacks::int_stack.size() <= 1)
					error("could not swap the top two elements", "not enough elements. (integer stack)");

				int first = stacks::int_stack.top();
				stacks::int_stack.pop();
				int second = stacks::int_stack.top();
				stacks::int_stack.pop();

				stacks::int_stack.push(first);
				stacks::int_stack.push(second);
				break;
			}
			case 1: {
				if (stacks::double_stack.size() <= 1)
					error("could not swap the top two elements", "not enough elements. (floating point int stack)");

				double first = stacks::double_stack.top();
				stacks::double_stack.pop();
				double second = stacks::double_stack.top();
				stacks::double_stack.pop();
				
				stacks::double_stack.push(first);
				stacks::double_stack.push(second);
				break;
			}
			case 2: {
				if (stacks::str_stack.size() <= 1)
					error("could not swap the top two elements", "not enough elements. (string stack)");

				std::string first = stacks::str_stack.top();
				stacks::str_stack.pop();
				std::string second = stacks::str_stack.top();
				stacks::str_stack.pop();

				stacks::str_stack.push(first);
				stacks::str_stack.push(second);
				break;
			}
		}
		return true;
	}

	if (tk.str == "emit") {
		if (stacks::int_stack.size() == 0)
			error("invalid emit", "top element does not exist.");

		int top = stacks::int_stack.top();

		if (top < 0 || top > 127)
			error("invalid emit", "ascii char " + std::to_string(top) + " does not exist.");

		printf("%c", top);
		stacks::int_stack.pop();

		return true;
	}

	return false;
}

#include "components/words.hpp"

std::vector<word_class> words;

std::vector<std::string> keywords { "int", "float", "string", "print", "exit", "quit", "size", "length", "clear", "pop", "drop", "dup", "top", ".", "negate", "abs", "swap", "max", "min", "emit" };

void parse_word(token tk) {
	for (auto i : words) {
		if (i.name == tk.str) {
			i.parse_word();
			return;
		}
	}

	error("invalid word", tk.str + " is not a word/keyword");
}

int handle_word(std::vector<std::vector<token>> &tks, int i, int j) {
	std::vector<std::string> cpy;
	for (auto i : words)
		cpy.emplace_back(i.name);

	if (std::binary_search(cpy.begin(), cpy.end(), tks[i][j+1].str))
		error("invalid word", "'" + tks[i][j+1].str + "' word already exists.");

	if (std::count(keywords.begin(), keywords.end(), tks[i][j+1].str))
		error("invalid word", "'" + tks[i][j+1].str + "' is a already existing keyword.");

	std::string name = tks[i][j+1].str;
	std::string content = "";

	int to_add = 1;

	for (int x = j+2; tks[i][x].str != ";"; x++) {
		content += (tks[i][x].str + " ");
		to_add++;
	}

	words.emplace_back(word_class(name, content));

	return to_add;
}