#pragma once

#include "../Storage/SymbolTable.cpp"
#include "../Storage/ProgramInternalForm.cpp"

class Result {
public:
	SymbolTable* identifiersTable;
	SymbolTable* constantsTable;
	ProgramInternalForm* programInternalForm;

	Result(SymbolTable* identifiersTable, SymbolTable* constantsTable, ProgramInternalForm* programInternalForm) {
		this->identifiersTable = identifiersTable;
		this->constantsTable = constantsTable;
		this->programInternalForm = programInternalForm;
	}

	string toString() {
		return string("==SCAN RESULT==\n")
			+ string("Identifiers:\n")
			+ (*identifiersTable).toString() + "\n\n"
			+ string("Constants\n")
			+ (*constantsTable).toString() + "\n\n"
			+ string("Program Internal Form\n")
			+ (*programInternalForm).toString();
	}
};