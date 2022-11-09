#include "Lab-4.h"

#include <string>
#include <fstream>
#include <vector>
#include "Models/FiniteAutomata.cpp"
#include "Models/InputSymbol.cpp"
#include "Models/State.cpp"
#include "Models/TransitionFunction.cpp"

using std::string;
using std::ifstream;
using std::vector;

using namespace std;

template< template<typename, typename> class Container, typename Separator >
static Container<string, allocator<string> > split(const string& line, Separator sep) {
	size_t pos = 0;
	size_t next = 0;
	Container<string, allocator<string> > fields;
	while (next != string::npos) {
		next = line.find_first_of(sep, pos);
		string field = next == string::npos ? line.substr(pos) : line.substr(pos, next - pos);
		fields.push_back(field);
		pos = next + 1;
	}
	return fields;
}

int main()
{
	string path = "C:\\Users\\PC\\Documents\\GitHub\\University-Lab-FLCD\\Lab-4\\Lab-4\\in.txt";
	ifstream file(path);
	vector<string> lines = vector<string>();

	try {
		string line;
		int index = 0;
		while (std::getline(file, line)) {
			if (index != 0)lines.push_back(line);
			index++;
		}
	}
	catch (std::ifstream::failure ioException) {
		throw new runtime_error("Error reading the file " + path + ": " + *ioException.what());
	}

	vector<State*> states = vector<State*>();
	vector<InputSymbol*> symbols = vector<InputSymbol*>();
	State* initialState;
	vector<State*> finalStates = vector<State*>();
	vector<TransitionFunction*> transitionFunctions = vector<TransitionFunction*>();
	for (auto& line : lines) {
		if (line[0] == 'Q') {
			string text = line.substr(3, line.size() - 1);
			vector<string> statesString = split<vector>(text, ",");
			for (string& stateString : statesString) {
				states.push_back(new State(stateString));
			}
		}
		else if (line[0] == 'S') {
			string text = line.substr(3, line.size() - 1);
			vector<string> inputSymbolsString = split<vector>(text, ",");
			for (string& inputSymbolString : inputSymbolsString) {
				symbols.push_back(new InputSymbol(inputSymbolString));
			}
		}
		else if (line[0] == 'q') {
			bool isFound = false;
			string text = line.substr(2, line.size());
			for (State* state : states) {
				if (state->Symbol == text) {
					initialState = state;
					isFound = true;
					break;
				}
			}
			if (!isFound) {
				throw std::exception();
			}
		}
		else if (line[0] == 'F') {
			string text = line.substr(3, line.size() - 1);
			vector<string> elements = split<vector>(text, ",");
			for (string& element : elements) {
				bool isFound = false;
				for (State* state : states) {
					if (state->Symbol == element) {
						finalStates.push_back(state);
						isFound = true;
						break;
					}
				}
				if (!isFound) {
					throw std::exception();
				}
			}
		}
		else if (line[0] == 'T') {
			string text = line.substr(3, line.size() - 4);
			vector<string> elements = split<vector>(text, ",");
			for (string& element : elements) {
				string sourceState = split<vector>(split<vector>(element, "(")[1], ";")[0];
				string throughSymbol = split<vector>(split<vector>(split<vector>(element, "(")[1], ";")[1], ')')[0];
				string targetState = split<vector>(split<vector>(split<vector>(element, "(")[1], ";")[1], '=')[1];

				State* sourceStateRef;
				InputSymbol* throughSymbolRef;
				State* targetStateRef;

				bool isFound = false;
				for (State* state : states) {
					if (state->Symbol == sourceState) {
						sourceStateRef = state;
						isFound = true;
						break;
					}
				}
				if (!isFound) {
					throw std::exception();
				}

				isFound = false;
				for (State* state : states) {
					if (state->Symbol == targetState) {
						targetStateRef = state;
						isFound = true;
						break;
					}
				}
				if (!isFound) {
					throw std::exception();
				}

				isFound = false;
				for (InputSymbol* inputSymbolCurrent : symbols) {
					if (inputSymbolCurrent->Symbol == throughSymbol) {
						throughSymbolRef = inputSymbolCurrent;
						isFound = true;
						break;
					}
				}
				if (!isFound) {
					throw std::exception();
				}

				transitionFunctions.push_back(new TransitionFunction(sourceStateRef, throughSymbolRef, targetStateRef));
			}
		}
		else {
			throw std::exception();
		}
	}

	auto finiteAutomata = FiniteAutomata(states, symbols, initialState, finalStates, transitionFunctions);
	return 0;
}
