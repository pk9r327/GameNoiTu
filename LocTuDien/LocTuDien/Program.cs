using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LocTuDien
{
    class Program
    {
        static void Main(string[] args)
        {
            List<string> dic = new List<string>();

            string text = File.ReadAllText("vv30K.index.txt");
            var lines = text.Split('\n');
            for (int i = 0; i < lines.Length; i++)
            {
                lines[i] = lines[i].ToLower().Split('\t')[0].Trim();
                if (lines[i].Split(' ').Length == 2)
                {
                    dic.Add(lines[i].Split(' ')[0]);
                }
            }

            var frequencies = new Dictionary<string, int>();
            foreach (var item in dic)
            {
                int currentCount;
                // We don't care about the return value here, as if it's false that'll
                // leave currentCount as 0, which is what we want
                frequencies.TryGetValue(item, out currentCount);
                frequencies[item] = currentCount + 1;
            }
        }
    }
}
