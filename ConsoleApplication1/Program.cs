using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace ConsoleApplication1
{
    class Program
    {
        static int P_Fib(int n)
        {
            int x = 0, y = 0;
            if(n <= 1)
            {
                return n;
            }
            else
            {
                Task mytask = Task.Run(() =>
                {
                    x = P_Fib(n - 1);
                });
                y = P_Fib(n - 2);
                mytask.Wait();
                return (x + y);
            }
        }
        static int[] initializeArray(int[] array)
        {
            for(int i = 0; i < array.Length; i++)
            {
                array[i] = 5;
            }
            return array;
        }
        static int[] parallelInitV1(int[] array)
        {
            Parallel.For(0, array.Length,
                  index => {
                      array[index] = 5;
                  });
            return array;
        }
        static int[] initializeArrayCnC(int[] array, int index) //pass in index of array.length - 1 on initial non-recursive call
        {  
            if(index == 0)
            {
                array[index] = 5;
                return array;
            }
            else {
                array[index] = 5;
                index--;
                array = initializeArrayCnC(array, index);
                return array;
            }
        }
        static int[] parallelInitV2(int[] array, int index)
        {
            if(index < 0)
            {
                return array;
            }
            Task mytask = Task.Run(() => parallelInitV2(array, index - 1));
            array[index] = 5;
            mytask.Wait();


            return array;
        }
        static void initializeArrayDnC(ref int[] array, int left, int right)
        {
            if(left == right)
            {
                array[left] = 5;
            }
            if(right > left) { 
                int mid = (left + right) / 2;
                initializeArrayDnC(ref array, left, mid);
                initializeArrayDnC(ref array, mid + 1, right);
            }            
        }
        static void parallelInitV3(int[] array, int left, int right)
        {
            if (left == right)
            {
                array[left] = 5;
            }
            if (right > left)
            {
                int mid = (left + right) / 2;
                Task mytask = Task.Run(() => parallelInitV3(array, left, mid));
                parallelInitV3(array, mid + 1, right);
                mytask.Wait();
            }
        }
        static void Main(string[] args)
        {
            int[] intarray = new int[1000000];
            //intarray = initializeArray(intarray);
            //intarray = initializeArrayCnC(intarray, intarray.Length -1);
            //initializeArrayDnC(ref intarray, 0, intarray.Length -1);
            //intarray = parallelInitV1(intarray);
            //intarray = parallelInitV2(intarray, intarray.Length - 1);
            parallelInitV3(intarray, 0, intarray.Length - 1);
            /*for(int i = 0; i < intarray.Length; i++)
            {
                Console.Write(intarray[i]);
            }
            Console.WriteLine();*/

            /*int combinationPizzaHutAndTacoBell = 12;
            int total = 0;
            total = P_Fib(combinationPizzaHutAndTacoBell);
            Console.Write(total);*/
        }
    }
}
