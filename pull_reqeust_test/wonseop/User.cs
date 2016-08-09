using System;

namespace BaseballGame_AI
{
    abstract class User
    {
        public string Name { get; set; }
        public Number Num { get; set; }

        public User(string Num, string Name)
        {
            this.Name = Name;
            this.Num = Num;
        }

        public virtual bool Query()
        {            
            return Query(Console.ReadLine());
        }

        protected virtual bool Query(string Question)
        {
            Console.WriteLine($"Strike: {Num.Strike(Question)}, Ball: {Num.Ball(Question)}");
            if (Num.Strike(Question) == 4) return true;
            else return false;
        }
        

        public virtual void ReSet(string Num)
        {
            ReSet(Num, this.Name);
        }

        public void ReSet(string Num, string Name)
        {
            this.Num = Num;
            this.Name = Name;
        }

    }

    class Human : User
    {
        public Human(string Num, string Name) : base(Num, Name) { }

        protected sealed override bool Query(string Question)
        {
            if(Number.Effectiveness(Question)) return base.Query(Question);
            else
            {
                Console.Write("유효한 숫자를 입력해주세요: ");
                return Query(Console.ReadLine());
            }
        }
    }
}