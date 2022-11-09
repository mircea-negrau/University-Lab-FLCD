#pragma once

#include <vector>

#include "InputSymbol.cpp"
#include "State.cpp"
#include "TransitionFunction.cpp"

using std::vector;

class FiniteAutomata {
public:
	vector<State*> states;
	vector<InputSymbol*> symbols;
	State* initialState;
	vector<State*> finalStates;
	vector<TransitionFunction*> transitionFunctions;

	FiniteAutomata(vector<State*> states, vector<InputSymbol*> symbols, State* initialState, vector<State*> finalStates, vector<TransitionFunction*> transitionFunctions) :
		states(states), symbols(symbols), initialState(initialState), finalStates(finalStates), transitionFunctions(transitionFunctions) {}
};