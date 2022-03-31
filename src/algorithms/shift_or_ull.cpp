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
  vector<unsigned long long> char_mask(128, ~(0));

  for (int j = 0; j < m; j++)
  {
    char_mask[pattern[j]] &= ~(1 << j);
  }

  return char_mask;
}

vector<int> shift_or(string pattern, string text, vector<unsigned long long> C)
{
  vector<int> occurrences;
  int m = pattern.size();
  int n = text.size();

  unsigned long long S = ~(0 << m);

  for (int i = 0; i < n; i++)
  {
    S = (S << 1) | C[text[i]];
    if (!(S&(1<<m-1)))
    {
      occurrences.push_back(i + 1 - m);
    }
  }

  return occurrences;
}

int main(int argc, char *argv[])
{
  time_t start, end;
  string pattern = argv[1];
  string line;
  ifstream file(argv[2]);

  auto char_mask = build_char_mask(pattern);

  for (string line; getline(file, line);)
  {
    auto occurrences = shift_or(pattern, line, char_mask);
    if (!occurrences.empty())
    {
      cout << line << '\n';
    }
  }

  return 0;
}