namespace Lab3.Models;

internal sealed class FiniteAutomata
{
    public string InitialState { get; set; }
    public List<string> Alphabet { get; set; }
    public List<string> States { get; set; }
    public List<string> FinalStates { get; set; }
    public List<Transition> Transitions { get; set; }

    public FiniteAutomata(string initialState, List<string> alphabet, List<string> states, List<string> finalStates, List<Transition> transitions)
    {
        States = states;
        Alphabet = alphabet;
        FinalStates = finalStates;
        Transitions = transitions;
        InitialState = initialState;
    }

    public bool IsDeterministic()
    {
        foreach (string state in States)
        {
            foreach (string symbol in Alphabet)
            {
                int paths = Transitions.Count(transition
                    => transition.SourceState == state
                    && transition.Symbol == symbol);

                if (paths > 1)
                {
                    return false;
                }
            }
        }
        return true;
    }

    public bool IsAcceptedSequence(string sequence)
    {
        string currentState = InitialState;

        foreach (char symbol in sequence)
        {
            if (!Alphabet.Contains(symbol.ToString()))
            {
                return false;
            }

            var transition = Transitions.FirstOrDefault(transition
                => transition.SourceState == currentState
                && transition.Symbol == symbol.ToString());

            if (transition == null)
            {
                return false;
            }

            currentState = transition.TargetState;
        }

        return FinalStates.Contains(currentState);
    }

    public bool IsValid()
        => States.Count > 0
        && Alphabet.Count > 0
        && FinalStates.Count > 0
        && Transitions.Count > 0
        && States.Contains(InitialState)
        && FinalStates.All(finalState => States.Contains(finalState))
        && Transitions.All(transition
            => States.Contains(transition.SourceState)
            && States.Contains(transition.TargetState)
            && Alphabet.Contains(transition.Symbol)
        );
}
