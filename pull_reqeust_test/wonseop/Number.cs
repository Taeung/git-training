using System;
using System.Collections;

namespace BaseballGame_AI
{
    class Number : IEnumerable, IComparable
    {
        public const int Length = 4;
        private string num;

        public string Num
        {
            get
            {
                return num;
            }
            set
            {
                if (Effectiveness(value)) num = value;
                else throw new ArgumentException("올바르지 않은 값입니다.", nameof(value));
            }
        }
                
        public char this[int index]
        {
            get
            {
                return Num[index];
            }
        }

        public Number(int Num) : this(Num.ToString()) { }
        public Number(string Num)
        {
            this.Num = Num;
        }

        public override string ToString()
        {
            return Num;
        }

        public int Strike(Number Question)
        {
            int count = 0;
            for (int i = 0; i < Length; i++)    
            {
                if (Question.Num[i] == Num[i]) count++;
            }
            return count;
        }

        public int Ball(Number Question)
        {
            int count = 0;
            for (int i = 0; i < Length; i++)
            {
                for(int j = 0; j < Length; j++)
                {
                    if (Num[i] == Question[j] && i != j) count++;
                }
            }
            return count;
        }
      
        public IEnumerator GetEnumerator()
        {
            return ((IEnumerable)Num).GetEnumerator();
        }

        public int CompareTo(object obj)
        {
            return Num.CompareTo(obj as string);
        }

        public static bool Effectiveness(int Num)
        {
            return Effectiveness(Num.ToString());
        }
        public static bool Effectiveness(string Num)
        {
            if (Num.Length != Length) return false;

            for (int i = 0; i < Length; i++)
            {
                if ('0' <= Num[i] && Num[i] <= '9')
                {
                    for (int j = i + 1; j < Length; j++)
                    {
                        if (Num[i] == Num[j]) return false;
                    }
                }
                else return false;
            }
            return true;
        }

        public static implicit operator string(Number Num)
        {
            return Num.Num;
        } 

        public static implicit operator Number(string Num)
        {
            return new Number(Num);
        }
    }
}
