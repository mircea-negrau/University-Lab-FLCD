using Lab3.Models;

namespace Lab3.Ui;

internal sealed class ConsoleUi
{
    private FiniteAutomata? FiniteAutomata { get; set; }

    public ConsoleUi() { }

    private static void PrintMenu()
    {
        Console.WriteLine("[1] Print menu");
        Console.WriteLine("[2] Read from file");
        Console.WriteLine("[3] Display states");
        Console.WriteLine("[4] Display alphabet");
        Console.WriteLine("[5] Display transitions");
        Console.WriteLine("[6] Display initial state");
        Console.WriteLine("[7] Display final states");
        Console.WriteLine("[8] Check if deterministic");
        Console.WriteLine("[9] Check sequence");
        Console.WriteLine("[10] Validate");
        Console.WriteLine("[0] Exit");
    }

    private static int? GetCommand()
    {
        try
        {
            return int.Parse(Console.ReadLine() ?? "");
        }
        catch (Exception)
        {
            return null;
        }
    }

    private void ReadFromFile()
    {
        Console.Write("Filepath: ");
        string filepath = Console.ReadLine()!;
        try
        {
            List<string> lines = File.ReadAllLines(filepath).ToList();
            if (lines.Count < 5)
            {
                throw new ArgumentException("Invalid file length");
            }

            List<string> states = lines[0].Trim().Split(" ").ToList();
            List<string> alphabet = lines[1].Trim().Split(" ").ToList();
            string initialState = lines[2].Trim();
            List<string> finalStates = lines[3].Trim().Split(" ").ToList();
            List<Transition> transitions = new();

            foreach (var line in lines.Skip(4))
            {
                string[] parts = line.Split(" ");
                if (parts.Length != 3)
                {
                    throw new ArgumentException($"Invalid transition: {line}");
                }

                var sourceState = parts[0];
                var symbol = parts[1];
                var targetState = parts[2];
                transitions.Add(new Transition(sourceState, symbol, targetState));
            }

            FiniteAutomata = new(initialState, alphabet, states, finalStates, transitions);
        }
        catch (Exception exception)
        {
            Console.WriteLine(exception.Message);
        }
    }

    private void CheckSequence()
    {
        Console.Write("Please enter the sequence: ");
        string sequence = Console.ReadLine()!;
        Console.WriteLine(FiniteAutomata!.IsAcceptedSequence(sequence));
    }

    private void IsFiniteAutomataValid()
    {
        Console.WriteLine(FiniteAutomata!.IsValid());
    }

    private void CheckIsDeterministic()
    {
        Console.WriteLine(FiniteAutomata!.IsDeterministic());
    }

    private void PrintFinalStates()
    {
        Console.WriteLine(string.Join(" ", FiniteAutomata!.FinalStates));
    }

    private void PrintInitialState()
    {
        Console.WriteLine(FiniteAutomata!.InitialState);
    }

    private void PrintTransitions()
    {
        Console.WriteLine(string.Join("\n", FiniteAutomata!.Transitions));
    }

    private void PrintAlphabet()
    {
        Console.WriteLine(string.Join(" ", FiniteAutomata!.Alphabet));
    }

    private void PrintStates()
    {
        Console.WriteLine(string.Join(" ", FiniteAutomata!.States));
    }

    private void Exit()
    {
        Environment.Exit(0);
    }

    private void ExecuteCommand(int command)
    {
        switch (command)
        {
            case 1: { PrintMenu(); break; }
            case 2: { ReadFromFile(); break; }
            case 3: { PrintStates(); break; }
            case 4: { PrintAlphabet(); break; }
            case 5: { PrintTransitions(); break; }
            case 6: { PrintInitialState(); break; }
            case 7: { PrintFinalStates(); break; }
            case 8: { CheckIsDeterministic(); break; }
            case 9: { CheckSequence(); break; }
            case 10: { IsFiniteAutomataValid(); break; }
            case 0: { Exit(); break; }
        }
    }

    public void Run()
    {
        PrintMenu();
        while (true)
        {
            Console.Write("Command: ");
            int? command = GetCommand();

            if (command == null || command < 0 || command > 10)
            {
                Console.WriteLine("Invalid command");
                continue;
            }

            if (FiniteAutomata == null && !new List<int>() { 0, 1, 2 }.Contains((int)command))
            {
                Console.WriteLine("No Finite Automata loaded!");
                continue;
            }

            ExecuteCommand((int)command);
        }
    }
}