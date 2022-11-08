#pragma once

#include "../Storage/SymbolTable.cpp"
#include "../Storage/ProgramInternalForm.cpp"
#include "Result.cpp"
#include "../Tokens/TokenType.cpp"
#include "../../Constants/Scanner.cpp"
#include "../Tokens/Tokens.cpp"
#include "../../Errors/LexicError.cpp"
#include "../../Utils/TextHelper.cpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <stdexcept>
#include "../TokensIdentifier/TokensIdentifier.cpp"
#include "../Core/Tuple.cpp"

using std::cout;
using std::tuple;
using std::runtime_error;
using std::ifstream;
using std::string;
using std::vector;

class Scanner {
private:
	SymbolTable* identifiers;
	SymbolTable* constants;
	ProgramInternalForm* programInternalForm;
	Tokens* tokens;

	vector<string> getContentFromPath(const string& path) {
		ifstream file(path);
		vector<string> lines = vector<string>();
		try {
			string line;
			while (std::getline(file, line)) {
				lines.push_back(line);
			}
			return lines;
		}
		catch (std::ifstream::failure ioException) {
			throw new runtime_error("Error reading the file " + path + ": " + *ioException.what());
		}
	}

	vector<string> getTokensFromLine(string line) {
		if (line.empty()) {
			return vector<string>();
		}

		TextHelper textHelper = TextHelper();
		vector<string> tokens = textHelper.split<vector>(line, ' ');

		return getMultipleSymbolOperators(
			textHelper.filter(tokens, [](string token) { return token.size() > 0; })
		);
	}

	vector<string> getMultipleSymbolOperators(vector<string> tokens) {
		auto textHelper = TextHelper();
		vector<string> equalPossibleOperators = vector<string>{ "=", "!", "<", ">" };

		if (tokens.size() < 2) {
			return tokens;
		}

		vector<string> rebuilt = vector<string>();

		int current = 1;

		while (current < tokens.size()) {
			int previous = current - 1;

			string previousChar = tokens[previous];
			string currentChar = tokens[current];

			if (currentChar == "=" && textHelper.contains(equalPossibleOperators, previousChar)) {
				rebuilt.push_back(previousChar + currentChar);
				current += 1;
			}
			else {
				rebuilt.push_back(previousChar);
			}

			current += 1;
			if (current == tokens.size()) {
				rebuilt.push_back(tokens[current - 1]);
			}
		}

		return rebuilt;
	}

	vector<string> separateLines(vector<string> fileContent) {
		auto textHelper = TextHelper();
		auto response = vector<string>();
		for (auto& element : fileContent) {
			string trimmed = textHelper.trim_copy(element);
			separateTokens(trimmed);
			response.push_back(trimmed);
		}

		return response;
	}

	void separateTokens(string& line) {
		if (line.empty()) {
			line = "";
		}

		auto textHelper = TextHelper();
		for (string& inputToken : (*tokens).initialTokens) {
			textHelper.ReplaceStringInPlace(inputToken, "\\", "");
			if (!textHelper.contains((*tokens).keywords, inputToken)) {
				textHelper.ReplaceStringInPlace(line, inputToken, " " + inputToken + " ");
			}
		}
	}

public:
	Scanner(SymbolTable* identifiers, SymbolTable* constants, ProgramInternalForm* programInternalForm, const string& tokensPath) {
		this->identifiers = identifiers;
		this->constants = constants;
		this->programInternalForm = programInternalForm;
		this->tokens = new Tokens(getContentFromPath(tokensPath));
	}


	Result* scan(string programSourceCodePath) {
		vector<string> lines = separateLines(getContentFromPath(programSourceCodePath));
		int lineCounter = 0;
		TokensIdentifier classifier = TokensIdentifier();

		auto scannerConstants = ScannerConstants();
		for (auto& line : lines) {
			lineCounter++;
			vector<string> lineTokens = getTokensFromLine(line);
			for (auto& token : lineTokens) {
				TokenType type = classifier.identify(token, *tokens);
				switch (type) {
				case TokenType::Identifier: {
					(*identifiers).Add(token);
					(*programInternalForm).Add(Tuple(scannerConstants.Identifier, (*identifiers).FindByValue(token)->key));
					break;
				}
				case TokenType::Constant: {
					(*constants).Add(token);
					(*programInternalForm).Add(Tuple(scannerConstants.Constant, (*constants).FindByValue(token)->key));
					break;
				}
				case TokenType::Unknown: {
					throw LexicError(
						"[ERROR] Could not identify token \"" + token + "\" (line " + std::to_string(lineCounter) + ")"
					);
					break;
				}
				default: {
					(*programInternalForm).Add(Tuple(token, scannerConstants.Other));
					break;
				}
				}
			}
		}
		return new Result(identifiers, constants, programInternalForm);
	}
};