#pragma once

#include "State.cpp"
#include "InputSymbol.cpp"

class TransitionFunction {
public:
	State* sourceState;
	InputSymbol* throughSymbol;
	State* finalState;

	TransitionFunction(State* sourceState, InputSymbol* throughSymbol, State* finalState) :
		sourceState(sourceState), throughSymbol(throughSymbol), finalState(finalState) {}
};