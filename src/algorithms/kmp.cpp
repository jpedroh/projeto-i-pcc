#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

auto init_next(string pattern)
{
  int m = pattern.size();
  vector<int> next(m + 1);
  fill(next.begin(), next.end(), 0);
  next[0] = -1;
  int i = 1, j = 0;

  while (i + j < m)
  {
    while (i + j < m && pattern[i + j] == pattern[j])
    {
      j++;
      next[i + j] = j;
    }
    i += j - next[j];
    j = max(0, next[j]);
  }

  return next;
}

vector<int> kmp(string pattern, string text, vector<int> next)
{
  vector<int> occurrences;
  int m = pattern.size();
  int n = text.size();
  int i = 0, j = 0;

  while (i <= n - m)
  {
    while (j < m && pattern[j] == text[i + j])
    {
      j++;
    }
    if (j == m)
    {
      occurrences.push_back(i);
    }
    i += j - next[j];
    j = max(0, next[j]);
  }

  return occurrences;
}

int main(int argc, char *argv[])
{
  string pattern = argv[1];
  string line;
  ifstream file(argv[2]);

  auto next = init_next(pattern);

  for (string line; getline(file, line);)
  {
    auto occurrences = kmp(pattern, line, next);
    if (!occurrences.empty())
    {
      cout << line << endl;
    }
  }

  return 0;
}