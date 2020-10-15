using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DistribuzioneArm
{
	class Program
	{
		static void Main(string[] args)
		{
			new Arm();
		}
	}

	class Arm
	{
		static int[] dist   = new int[] {3,2};
		double[] freq       = new double[dist.Length];
		int[] final         = new int[dist.Sum()];

		double segment = 1.0;

		public Arm()
		{
			Initialize();
			Armonize();
			PrintResult();
			Console.ReadKey();
			Distances();
			Console.ReadKey();
		}

		void Initialize()
		{
			for(int i = 0; i < dist.Length; i++)
			{
				freq[i] = segment / dist[i];
			}
		}

		void Armonize()
		{
			var rand = new Random();
			int k = rand.Next(0,final.Length-1);
			var origFreq = new double[freq.Length];
			freq.CopyTo(origFreq, 0);
			
			for (int i=0;i<final.Length;i++)
			{ 
				final[k] = GetMinIndex();
				freq[GetMinIndex()] += origFreq[GetMinIndex()];

				if (++k >= final.Length)
					k = 0;
			}
		}
	   
		void PrintResult()
		{
			for (int i = 0; i < final.Length; i++)
			{
				Console.SetCursorPosition(i, final[i]);
				Console.BackgroundColor = (ConsoleColor)final[i]+1;
				Console.Write((char)(final[i]+65));
			}
		}

		void Distances()
		{
			int count, currDist, k;
			int[] coef = new int[dist.Length];
			Array.Clear(coef,0,coef.Length);

			for (int i=0;i<dist.Length;i++)
			{
				currDist = 0;
				k = 0;
				count = 0;
				while ((count < dist[i]+1)&&(dist[i]!=1))
				{
					if ((final[k] == i) && (count == 0)) //prima volta che trovo qulla lettera
						count++;
					else if ((count > 0) && (final[k] == i)) //se ritrovo la lettera
					{
						currDist++;
						coef[i] += (int)Math.Pow(currDist, 2);
						currDist = 0;
						count++;
					}else if ((count > 0) && (final[k] != i))
						currDist++;
					
					if (++k >= final.Length)
						k = 0;
				}
			}
			Console.ResetColor();
			Console.Clear();
			Console.WriteLine(" m = {0}", coef.Sum());
		}

		int GetMinIndex() 
		{  
			return Array.IndexOf(freq, freq.Min());
		}
	}
}
