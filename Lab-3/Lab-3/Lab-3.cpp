#include <string>
#include <iostream>
#include <fstream>

#include "Errors/LexicError.cpp"
#include "Models/Storage/SymbolTable.cpp"
#include "Models/Storage/ProgramInternalForm.cpp"
#include "Models/Scanner/Scanner.cpp"

using std::fstream;
using std::cout;

int main() {
	const string PROGRAM_PATH = "C:\\Users\\PC\\Documents\\GitHub\\University-Lab-FLCD\\Lab-3\\Lab-3\\Data\\p3.txt";
	const string TOKENS_PATH = "C:\\Users\\PC\\Documents\\GitHub\\University-Lab-FLCD\\Lab-3\\Lab-3\\Data\\token.in";
	const string OUTPUT_FILE = "C:\\Users\\PC\\Documents\\GitHub\\University-Lab-FLCD\\Lab-3\\Lab-3\\Data\\PIF_ST.out";

	SymbolTable* identifiers = new SymbolTable();
	SymbolTable* constants = new SymbolTable();
	ProgramInternalForm* programInternalForm = new ProgramInternalForm();

	Scanner* scanner = new Scanner(identifiers, constants, programInternalForm, TOKENS_PATH);

	fstream output;
	output.open(OUTPUT_FILE);
	if (!output.is_open()) {
		cout << "Output file failed!";
		exit(1);
	}

	try {
		auto scanResult = scanner->scan(PROGRAM_PATH);
		output << scanResult->toString();
		output << "\n\nScanning successfully finished";
	}
	catch (LexicError& lexicalException) {
		output << "Scanning failed!\n";
		output << lexicalException.what();
	}
	catch (std::ifstream::failure ioException) {
		cout << "Error while writing to file: " + *ioException.what();
	}

	output.close();
}
