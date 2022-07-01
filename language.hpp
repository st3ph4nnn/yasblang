#pragma once
#include <stack>
#include <vector>
#include <iostream>
#include <variant>
#include <cmath>

#include "components/tokens.hpp"
#include "utilities/error_handling.hpp"

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
						error("math", "not enough stack members for equal checking.");

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
						error("math", "not enough stack members for equal checking.");

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
						error("math", "not enough stack members for equal checking.");

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
						error("math", "not enough stack members for greater than checking.");

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
						error("math", "not enough stack members for greater than checking.");

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
						error("math", "not enough stack members for greater than checking.");

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
						error("math", "not enough stack members for lower than checking.");

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
						error("math", "not enough stack members for lower than checking.");

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
						error("math", "not enough stack members for lower than checking.");

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
						error("math", "not enough stack members for adding.");

					int first = stacks::int_stack.top();
					stacks::int_stack.pop();
					int second = stacks::int_stack.top();
					stacks::int_stack.pop();
					stacks::int_stack.push(first+second);
					break;
				}
				case 1: {
					if (stacks::double_stack.size() <= 1)
						error("math", "not enough stack members for adding.");

					double first = stacks::double_stack.top();
					stacks::double_stack.pop();
					double second = stacks::double_stack.top();
					stacks::double_stack.pop();
					stacks::double_stack.push(first+second);
					break;
				}
				case 2: {
					if (stacks::str_stack.size() <= 1)
						error("math", "not enough stack members for adding.");

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
						error("math", "not enough stack members for substracting.");

					int first = stacks::int_stack.top();
					stacks::int_stack.pop();
					int second = stacks::int_stack.top();
					stacks::int_stack.pop();
					stacks::int_stack.push(first-second);
					break;
				}
				case 1: {
					if (stacks::double_stack.size() <= 1)
						error("math", "not enough stack members for substracting.");

					double first = stacks::double_stack.top();
					stacks::double_stack.pop();
					double second = stacks::double_stack.top();
					stacks::double_stack.pop();
					stacks::double_stack.push(first-second);
					break;
				}
				case 2: {
					if (stacks::str_stack.size() <= 1)
						error("math", "not enough stack members for substracting.");

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
						error("math", "not enough stack members for multplying.");

					int first = stacks::int_stack.top();
					stacks::int_stack.pop();
					int second = stacks::int_stack.top();
					stacks::int_stack.pop();
					stacks::int_stack.push(first*second);
					break;
				}
				case 1: {
					if (stacks::double_stack.size() <= 1)
						error("math", "not enough stack members for substracting.");

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
						error("math", "not enough stack members for division.");

					int first = stacks::int_stack.top();
					stacks::int_stack.pop();
					int second = stacks::int_stack.top();
					stacks::int_stack.pop();
					stacks::int_stack.push(first/second);
					break;
				}
				case 1: {
					if (stacks::double_stack.size() <= 1)
						error("math", "not enough stack members for division.");

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
						error("math", "not enough stack members for power.");

					int first = stacks::int_stack.top();
					stacks::int_stack.pop();
					int second = stacks::int_stack.top();
					stacks::int_stack.pop();
					stacks::int_stack.push(pow(first, second));
					break;
				}
				case 1: {
					if (stacks::double_stack.size() <= 1)
						error("math", "not enough stack members for power.");

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
						error("math", "not enough stack members for modulo.");

					int first = stacks::int_stack.top();
					stacks::int_stack.pop();
					int second = stacks::int_stack.top();
					stacks::int_stack.pop();
					stacks::int_stack.push(first % second);
					break;
				}
				case 1: {
					error("math", "modulo is not allowed on floats.");
					break;
				}
				case 2: {
					error("math", "modulo is not allowed on strings.");
					break;
				}
			}
			break;
		}
	}
}

void print_stack() {
	switch (stacks::selected) {
		case 0: {
			std::stack<int> copy = stacks::int_stack;
			int sz = copy.size();
			printf("\n%s\n\n", (sz == 0 ? "The current stack is currently empty." : "[PRINT] integer stack:"));
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
			printf("\n%s\n\n", (sz == 0 ? "The current stack is currently empty." : "[PRINT] floating point integer stack:"));
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
			printf("\n%s\n\n", (sz == 0 ? "The current stack is currently empty." : "[PRINT] string stack:"));
			while (!copy.empty()) {
				if (sz == copy.size())
					printf("%s <--- TOP\n", copy.top().c_str());
				else
					printf("%s\n", copy.top().c_str());

				printf("%s\n", copy.top().c_str());
				copy.pop();
			}
			break;
		}
	}
}

void handle_keywords(token tk) {
	if (tk.str == "int") {
		stacks::selected = 0;
		return;
	}

	if (tk.str == "float") {
		stacks::selected = 1;
		return;
	}

	if (tk.str == "string") {
		stacks::selected = 2;
		return;
	}

	if (tk.str == "print") {
		print_stack();
		return;
	}

	if (tk.str == "exit" || tk.str == "quit")
		exit(0);

	if (tk.str == "clear") {
		switch (stacks::selected) {
			case 0: while (!stacks::int_stack.empty()) stacks::int_stack.pop(); break;
			case 1: while (!stacks::double_stack.empty()) stacks::double_stack.pop(); break;
			case 2: while (!stacks::str_stack.empty()) stacks::str_stack.pop(); break;
		}
		return;
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
		return;
	}

	if (tk.str == "pop" || tk.str == "drop") {
		switch (stacks::selected) {
			case 0: {
				if (stacks::int_stack.size() == 0)
					error("could not drop/pop the top element", "stack is empty");
				stacks::int_stack.pop();
				break;
			}
			case 1: {
				if (stacks::double_stack.size() == 0)
					error("could not drop/pop the top element", "stack is empty");
				stacks::double_stack.pop();
				break;	
			}
			case 2: {
				if (stacks::str_stack.size() == 0)
					error("could not drop/pop the top element", "stack is empty");
				stacks::str_stack.pop();
				break;
			}
		}
		return;
	}

	if (tk.str == "dup") {
		switch (stacks::selected) {
			case 0: {
				if (stacks::int_stack.size() == 0)
					error("could not duplicate the top element", "stack is empty");

				stacks::int_stack.push(stacks::int_stack.top());
				break;
			}
			case 1: {
				if (stacks::double_stack.size() == 0)
					error("could not duplicate the top element", "stack is empty");

				stacks::double_stack.push(stacks::double_stack.top());
				break;
			}
			case 2: {
				if (stacks::str_stack.size() == 0)
					error("could not duplicate the top element", "stack is empty");

				stacks::str_stack.push(stacks::str_stack.top());
				break;
			}
		}
		return;
	}

	if (tk.str == "top") {
		switch (stacks::selected) {
			case 0: {
				if (stacks::int_stack.size() == 0)
					error("could not print the top element", "stack is empty");

				printf("%d\n", stacks::int_stack.top());
				break;
			}
			case 1: {
				if (stacks::double_stack.size() == 0)
					error("could not print the top element", "stack is empty");

				printf("%f\n", stacks::double_stack.top());
				break;
			}
			case 2: {
				if (stacks::str_stack.size() == 0)
					error("could not print the top element", "stack is empty");

				printf("%s\n", stacks::str_stack.top());
				break;
			}
		}
		return;
	}

	if (tk.str == ".") {
		switch (stacks::selected) {
			case 0: {
				if (stacks::int_stack.size() == 0)
					error("could not print the top element", "stack is empty");

				printf("%d\n", stacks::int_stack.top());
				stacks::int_stack.pop();
				break;
			}
			case 1: {
				if (stacks::double_stack.size() == 0)
					error("could not print the top element", "stack is empty");

				printf("%f\n", stacks::double_stack.top());
				stacks::double_stack.pop();
				break;
			}
			case 2: {
				if (stacks::str_stack.size() == 0)
					error("could not print the top element", "stack is empty");

				printf("%s\n", stacks::str_stack.top());
				stacks::str_stack.pop();
				break;
			}
		}
		return;
	}

	if (tk.str == "negate") {
		switch (stacks::selected) {
			case 0: {
				if (stacks::int_stack.size() == 0)
					error("could not negate the top element", "stack is empty");

				int top = stacks::int_stack.top();
				stacks::int_stack.pop();
				stacks::int_stack.push(-top);
				break;
			}
			case 1: {
				if (stacks::double_stack.size() == 0)
					error("could not negate the top element", "stack is empty");

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
		return;
	}

	if (tk.str == "abs") {
		switch (stacks::selected) {
			case 0: {
				if (stacks::int_stack.size() == 0)
					error("could not absolute the top element", "stack is empty");

				int top = stacks::int_stack.top();
				stacks::int_stack.pop();
				stacks::int_stack.push(std::abs(top));
				break;
			}
			case 1: {
				if (stacks::double_stack.size() == 0)
					error("could not absolute the top element", "stack is empty");

				double top = stacks::double_stack.top();
				stacks::double_stack.pop();
				stacks::double_stack.push(std::abs(top));
				break;
			}
			case 2: {
				error("math", "absolute is not allowed on strings."); 
				break;	
			}
		}
		return;
	}

	if (tk.str == "max") {
		switch (stacks::selected) {
			case 0: {
				if (stacks::int_stack.size() <= 1)
					error("could not max the top two elements", "not enough elements");

				int first = stacks::int_stack.top();
				stacks::int_stack.pop();
				int second = stacks::int_stack.top();
				stacks::int_stack.pop();
				stacks::int_stack.push(std::max(first, second));
				break;
			}
			case 1: {
				if (stacks::double_stack.size() <= 1)
					error("could not max the top two elements", "not enough elements");

				double first = stacks::double_stack.top();
				stacks::double_stack.pop();
				double second = stacks::double_stack.top();
				stacks::double_stack.pop();
				stacks::double_stack.push(std::max(first, second));
				break;
			}
			case 2: {
				if (stacks::str_stack.size() <= 1)
					error("could not max the top two elements", "not enough elements");

				std::string first = stacks::str_stack.top();
				stacks::str_stack.pop();
				std::string second = stacks::str_stack.top();
				stacks::str_stack.pop();

				stacks::str_stack.push((first.length() > second.length()) ? first : second);
				break;
			}
		}
		return;
	}

	if (tk.str == "min") {
		switch (stacks::selected) {
			case 0: {
				if (stacks::int_stack.size() <= 1)
					error("could not min the top two elements", "not enough elements");

				int first = stacks::int_stack.top();
				stacks::int_stack.pop();
				int second = stacks::int_stack.top();
				stacks::int_stack.pop();
				stacks::int_stack.push(std::min(first, second));
				break;
			}
			case 1: {
				if (stacks::double_stack.size() <= 1)
					error("could not min the top two elements", "not enough elements");

				double first = stacks::double_stack.top();
				stacks::double_stack.pop();
				double second = stacks::double_stack.top();
				stacks::double_stack.pop();
				stacks::double_stack.push(std::min(first, second));
				break;
			}
			case 2: {
				if (stacks::str_stack.size() <= 1)
					error("could not min the top two elements", "not enough elements");

				std::string first = stacks::str_stack.top();
				stacks::str_stack.pop();
				std::string second = stacks::str_stack.top();
				stacks::str_stack.pop();

				stacks::str_stack.push((first.length() < second.length()) ? first : second);
				break;
			}
		}
		return;
	}

	if (tk.str == "swap") {
				switch (stacks::selected) {
			case 0: {
				if (stacks::int_stack.size() <= 1)
					error("could not swap the top two elements", "not enough elements");

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
					error("could not swap the top two elements", "not enough elements");

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
					error("could not swap the top two elements", "not enough elements");

				std::string first = stacks::str_stack.top();
				stacks::str_stack.pop();
				std::string second = stacks::str_stack.top();
				stacks::str_stack.pop();

				stacks::str_stack.push(first);
				stacks::str_stack.push(second);
				break;
			}
		}
		return;
	}

	error("found unknown keyword", tk.str);
}