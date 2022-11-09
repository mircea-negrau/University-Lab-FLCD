#pragma once

#include <string>
#include <vector>

#include "../../Utils/TextHelper.cpp"
#include "../../Constants/Tokens.cpp"

using std::string;
using std::vector;

class Tokens {
private:
	void init() {
		auto listParser = TextHelper();
		auto constants = TokenConstants();

		populate(this->keywords,
			listParser.getIndex(initialTokens, constants.Keywords) + 1,
			listParser.getIndex(initialTokens, constants.KeywordsEnd));
		populate(this->operators,
			listParser.getIndex(initialTokens, constants.Operators) + 1,
			listParser.getIndex(initialTokens, constants.OperatorsEnd));
		populate(this->separators,
			listParser.getIndex(initialTokens, constants.Separators) + 1,
			listParser.getIndex(initialTokens, constants.SeparatorsEnd));
	}

	void populate(vector<string>& container, int start, int end) {
		for (int index = start; index < end; index++) {
			container.push_back(initialTokens[index]);
		}
	}

public:
	vector<string> initialTokens;
	vector<string> keywords;
	vector<string> operators;
	vector<string> separators;

	Tokens(vector<string> initialTokens) {
		this->initialTokens = initialTokens;
		this->keywords = vector<string>();
		this->operators = vector<string>();
		this->separators = vector<string>();
		init();
	}
};