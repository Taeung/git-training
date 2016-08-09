using System;
using System.Linq;
using System.Collections.Generic;



namespace BaseballGame_AI
{
    class BaseballGame
    {
        static Random RandomNumber = new Random();

        Queue<User> Turn = new Queue<User>();

        User Black;
        User White;
        int turncount { get; set; }

        public BaseballGame()
        {            
            Black = new Human(EffectivenessNum(), "Black");
            White = new Ai(EffectivenessNum(), "White");
            Turn.Enqueue(Black);
            Turn.Enqueue(White);
        }

        public void Start()
        {
            bool run = true;
            do
            {
                User player = Turn.Dequeue();
                Turn.Enqueue(player);

                Console.WriteLine($" === Turn {++turncount} === \n");
                Console.Write($"{player.Name} Turn: ");

                run = !player.Query();
                               
                Console.WriteLine();
            } while (run);

            Console.WriteLine($" === Answer === \n");
            Console.WriteLine($"{Black.Name}: {Black.Num}");
            Console.WriteLine($"{White.Name}: {White.Num}\n");
        }

        private string EffectivenessNum()
        {
            string temp;
            do
            {
                temp = RandomNumber.Next(1000, 10000).ToString();
            } while (!Number.Effectiveness(temp));
            return temp;
        }
                    
        public void Reset()
        {
            Black.ReSet(EffectivenessNum());
            White.ReSet(EffectivenessNum());
            turncount = 0;
            Turn.Clear();
            Turn.Enqueue(Black);
            Turn.Enqueue(White);
        }
    }  
}