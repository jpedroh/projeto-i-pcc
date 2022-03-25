#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <string>

using namespace std;

auto build_char_mask(string pattern)
{
  int m = pattern.size();
  vector<std::bitset<10>> char_mask;
  char_mask.resize(128);
  fill(char_mask.begin(), char_mask.end(), ~(0b0 << m));

  for (int j = 0; j < m; j++)
  {
    char_mask[pattern[j]][j] = 0;
  }

  return char_mask;
}

vector<int> shift_or(string pattern, string text, vector<std::bitset<10>> C)
{
  vector<int> occurrences;
  int m = pattern.size();
  int n = text.size();

  std::bitset<10> S;
  S = ~(0b0 << (m - 1));

  for (int i = 0; i < n; i++)
  {
    S = (S << 1) | C[text[i]];
    if (S[m - 1] == 0)
    {
      occurrences.push_back(i + 1 - m);
    }
  }

  return occurrences;
}

int main(int argc, char *argv[])
{
  string pattern = argv[1];
  string line;
  ifstream file(argv[2]);

  auto char_mask = build_char_mask(pattern);

  for (string line; getline(file, line);)
  {
    auto occurrences = shift_or(pattern, line, char_mask);
    if (!occurrences.empty())
    {
      cout << line << endl;
    }
  }

  return 0;
}