#pragma once

#include <string>

using std::string;

class State {
public:
	string Symbol;
	State(string Symbol) : Symbol(Symbol) {}
};