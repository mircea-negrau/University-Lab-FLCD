#pragma once

#include <stdexcept>
#include <string>

using std::runtime_error;
using std::string;

class LexicError : public runtime_error {
public:
	LexicError(string message) :runtime_error(message.c_str()) {}
};