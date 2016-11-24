using System;

namespace BaseballGame_AI
{
    class Program
    { 
        static void Main(string[] args)
        {
            BaseballGame game = new BaseballGame();
            game.Start();
            do
            {                
                Console.Write("Retry(y/n)? ");
                ConsoleKeyInfo key = Console.ReadKey();
                Console.WriteLine();
                if (key.Key == ConsoleKey.Y)
                {
                    Console.WriteLine();
                    game.Reset();
                    game.Start();
                }
                if (key.Key == ConsoleKey.N) break;
            } while (true);            
        }
    }
}
    