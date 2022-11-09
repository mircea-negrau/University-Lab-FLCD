#pragma once

#include <string>
#include <regex>
#include <vector>

#include "../Tokens/TokenType.cpp"
#include "../Tokens/Tokens.cpp"
#include "../../Utils/TextHelper.cpp"

using std::string;
using std::vector;
using std::regex_match;
using std::regex;

class TokensIdentifier {
public:
	static TokenType identify(string token, Tokens tokens) {
		if (isKeyword(token, tokens))
			return Keyword;
		else if (isOperator(token, tokens))
			return Operator;
		else if (isSeparator(token, tokens))
			return Separator;
		else if (isIdentifier(token))
			return Identifier;
		else if (isConstant(token))
			return Constant;
		return Unknown;
	}

private:
	static bool isSeparator(string token, Tokens tokens) {
		auto textHelper = TextHelper();
		return textHelper.contains(tokens.separators, token);
	}

	static bool isKeyword(string token, Tokens tokens) {
		auto textHelper = TextHelper();
		return textHelper.contains(tokens.keywords, token);
	}

	static bool isOperator(string token, Tokens tokens) {
		auto textHelper = TextHelper();
		return textHelper.contains(tokens.operators, token);
	}

	static bool isIdentifier(string token) {
		return regex_match(token, regex("^[a-zA-Z]+[a-z|A-z|0-9]*$"));
	}

	static bool isConstant(string token) {
		return regex_match(token, regex("True|False"))
			|| regex_match(token, regex("^0$"))
			|| regex_match(token, regex("^[1-9]+[0-9]*$"))
			|| regex_match(token, regex("^\"[a-z|A-Z|0-9|_]+\"$"));
	}
};