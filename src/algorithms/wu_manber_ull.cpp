#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <string>
#include <set>

using namespace std;

auto build_char_mask(string pattern)
{
  int m = pattern.size();
  vector<unsigned long long> char_mask(128, ~0);

  for (int j = 0; j < m; j++)
  {
    char_mask[pattern[j]] &= ~(1 << j);
  }

  return char_mask;
}

vector<int> wu_manber(string pattern, string text, int r, vector<unsigned long long> C)
{
  vector<int> occurrences;
  int m = pattern.size();
  int n = text.size();

  vector<unsigned long long> S(1, ~0);

  for(int q = 1; q < r+1; q++)
  {
    S.push_back(S[q-1] << 1);
  }

  for (int i = 0; i < n; i++)
  {  
      vector<unsigned long long> auxS;
      auxS.push_back(((S[0] << 1) | C[text[i]]));  
      
      for(int q = 1; q < r+1; q++)
      {
          auxS.push_back(((S[q] << 1) | C[text[i]]) & (S[q-1] << 1) & (auxS[q-1] << 1) & (S[q - 1]));
      }
      
      S = auxS;
      
      if (!(S[r]&(1<<m-1)))
      {
        occurrences.push_back(i);
      }
  }

  return occurrences;
}

int main(int argc, char *argv[])
{

  string pattern = argv[1];
  string line;
  int r = 2;
  ifstream file(argv[2]);

  auto char_mask = build_char_mask(pattern);

  for (string line; getline(file, line);)
  {
    auto occurrences = wu_manber(pattern, line, r, char_mask);
    if (!occurrences.empty())
    {
      cout << line << '\n';
    }
  }

  return 0;
}