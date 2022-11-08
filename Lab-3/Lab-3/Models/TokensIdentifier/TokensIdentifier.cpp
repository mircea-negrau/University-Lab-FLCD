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
		auto textHelper = TextHelper();
		if (textHelper.contains(tokens.keywords, token))
			return Keyword;
		else if (textHelper.contains(tokens.operators, token)) {
			return Operator;
		}
		else if (textHelper.contains(tokens.separators, token)) {
			return Separator;
		}
		else if (matchesIdentifier(token)) {
			return Identifier;
		}
		else if (matchesConstant(token)) {
			return Constant;
		}
		return Unknown;
	}

private:
	static bool matchesIdentifier(string token) {
		return regex_match(token, regex("^[a-zA-Z]+[a-z|A-z|0-9]*$"));
	}

	static bool matchesConstant(string token) {
		return regex_match(token, regex("True|False")) 
			|| regex_match(token, regex("^0$"))
			|| regex_match(token, regex("^[1-9]+[0-9]*$")) 
			|| regex_match(token, regex("^\"[a-z|A-Z|0-9|_]+\"$")); 
	}
};