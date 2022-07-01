#pragma once
#include "enums.hpp"

#include <vector>
#include <string>

class token {
public:
	std::string str;
    double value;

    int type;
    
    token() : type(token_type::other) {};
    token(symbols sy) : type(sy) {};
    token(operations op) : type(op) {};
    token(token_type type_, double val = 0, std::string str = "") : type(type_), value(val), str(str) {};

    bool is_operation() {
    	return (this->type >= 0 && this->type <= 3);
    }

    bool is_str() {
    	return (str != "");
    }
};