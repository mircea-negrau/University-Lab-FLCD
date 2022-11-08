#pragma once

#include <string>

using std::string;

class Tuple {
private:
	string first;
	string second;
public:
	Tuple() = default;
	Tuple(string first, string second) : first(first), second(second) {}

	string toString() {
		return this->first + ": " + this->second;
	}

	operator std::string() const {
		return this->first + ": " + this->second;
	}

	bool operator==(Tuple& other) {
		return this->first == other.first && this->second == other.second;
	}
};