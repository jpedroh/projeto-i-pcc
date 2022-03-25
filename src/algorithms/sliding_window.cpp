#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<int> sliding_window(string pattern, string text)
{
  vector<int> occurrences;
  int m = pattern.size();
  int n = text.size();

  for (int i = 0; i < n - m + 1; i++)
  {
    for (int j = 0; j < m; j++)
    {
      if (pattern[j] != text[j + i])
      {
        break;
      }
      else if (j == m - 1)
      {
        occurrences.push_back(i);
      }
    }
  }

  return occurrences;
}

int main(int argc, char *argv[])
{
  string pattern = argv[1];
  string line;
  ifstream file(argv[2]);

  for (string line; getline(file, line);)
  {
    auto occurrences = sliding_window(pattern, line);
    if (!occurrences.empty())
    {
      cout << line << endl;
    }
  }

  return 0;
}