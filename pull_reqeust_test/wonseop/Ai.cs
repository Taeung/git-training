using System;
using System.Linq;

namespace BaseballGame_AI
{
    partial class Ai : User
    {
        public const int Min = 1023;
        public const int Max = 9876;

        Number[] buffer = new Number[0];
        Random r1 = new Random();

        public Ai(string Num, string Name): base(Num, Name)
        {
            bufferSet();           
        }

        public void bufferSet()
        {
            for (int i = Min; i <= Max; i++)
            {
                if (Number.Effectiveness(i))
                {
                    addBuffer(ref buffer, i.ToString());
                }
            }
        }

        public override bool Query()
        {
            if (buffer.Length == 0) throw new ArgumentOutOfRangeException("경우의 수가 없습니다.");

            int QueryIndex = r1.Next(buffer.Length);
            Console.WriteLine(buffer[QueryIndex]);
            return Query(buffer[QueryIndex]);           
        }

        protected override bool Query(string Question)
        {
            bool flag = base.Query(Question);
            get(Question, Num.Ball(Question), Num.Strike(Question));
            return flag;
        }

        public override void ReSet(string Num)
        {
            bufferSet();
            base.ReSet(Num);
        }

        public void get(string str, int ballcount, int strikecount) 
        {
            Number[] temp = new Number[0];

            if (ballcount + strikecount == 0)
                ChageBuffer(str, (Number buffer, Number Num) => Num.ToString().Intersect(buffer.ToString()).Count() == 0);            
            else if(strikecount == 0)
                ChageBuffer(str, (Number buffer, Number Num) => !ComparePosition(buffer, Num));
                        
            if (strikecount > 0)
                getStrike(str, strikecount);
            if (ballcount > 0)
                ChageBuffer(str, (Number buffer, Number Num) => { return (buffer.ToString().Intersect(Num.ToString()).Count() == strikecount + ballcount && Num.CompareTo(buffer) != 0); });
        }

        public void getStrike(Number str, int strikecount)
        {
            Number[] temp = new Number[0];            

            foreach (var target in buffer)
            {
                int count = 0;
                for (int i = 0; i < 4; i++)
                {
                    if (target[i].CompareTo(str[i]) == 0)
                    {
                        count++;
                        if(count == strikecount && target.CompareTo(str) != 0 )
                        {
                            addBuffer(ref temp, target, !(i != 4 && ComparePosition(target,str, i + 1)));
                            break;
                        }
                    }
                }
            }
            buffer = temp;
        }

        public bool ComparePosition(string target, string Question, int startindex = 0)
        {
            for (int i = startindex; i < Number.Length; i++)
            {
                if (target[i] == Question[i]) return true;
            }
            return false;
        }

        public void addBuffer(ref Number[] buffer, Number num)
        {
            addBuffer(ref buffer, num, true);
        }

        public void addBuffer(ref Number[] buffer, Number num, bool expression)
        {
            if (expression)
            {
                Array.Resize(ref buffer, buffer.Length + 1);
                buffer[buffer.Length - 1] = num;
            }
        }

        public void ChageBuffer(Number num, Func<Number, Number, bool> expression)
        {
            Number[] temp = new Number[0];

            foreach (var item in buffer)
            {
                addBuffer(ref temp, item, expression(item, num));
            }
            buffer = temp;
        }
    }
}