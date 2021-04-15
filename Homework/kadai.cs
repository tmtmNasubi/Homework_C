using System;

namespace kadai1
{
    class kadai
    {
        static void Main(string[] args)
        {
            int sum, add;
            sum = 0;
            add = 0;
            int max = int.Parse(Console.ReadLine());

            while(max > sum)
            {
                sum = sum + add;

                if (max > sum)
                {
                    add = int.Parse(Console.ReadLine());
                }
            }


            Console.WriteLine("すべてのaddの合計値(< max)は{0}です。", sum);
        }
    }
}
