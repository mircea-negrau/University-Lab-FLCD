namespace Lab3.Models;

internal sealed class Transition
{
    public string SourceState { get; set; }
    public string Symbol { get; set; }
    public string TargetState { get; set; }

    public Transition(string sourceState, string symbol, string targetState)
    {
        SourceState = sourceState;
        Symbol = symbol;
        TargetState = targetState;
    }

    public override string ToString() =>
        $"({SourceState}, {Symbol}) => {TargetState}";
}