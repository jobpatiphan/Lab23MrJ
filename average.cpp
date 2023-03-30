#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;


int main(int argc, char *argv[])
{
   double sum = 0;
   double count = 0;
   if (argc == 1)
   {
      cout << "Please input numbers to find average." << endl;
      return 0;
   }
   if (argc > 1)
   {
      for (int i = 1; i < argc; i++)
      {
         sum += atoi(argv[i]);
         count++;
      }
      cout << "---------------------------------" << endl;
      cout << "Average of " << count << " numbers = " << sum / count << endl;
      cout << "---------------------------------" << endl;
   }
}
