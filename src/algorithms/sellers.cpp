#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

vector<int> sellers(string pattern, string text, int max_error)
{
  vector<int> occurrences;
  vector<vector<int>> dp(pattern.length() + 1);
  fill(dp.begin(), dp.end(), vector<int>(text.length() + 1));
  fill(dp[0].begin(), dp[0].end(), 0);

  for (int i = 0; i < dp.size(); i++)
  {
    dp[i][0] = i;
  }

  for (int i = 1; i < dp.size(); i++)
  {
    for (int j = 1; j < dp[i].size(); j++)
    {
      auto distance_one = dp[i - 1][j - 1] + (pattern.at(i - 1) == text.at(j - 1) ? 0 : 1);
      auto distance_two = dp[i - 1][j] + 1;
      auto distance_three = dp[i][j - 1] + 1;
      dp[i][j] = min(distance_one, min(distance_two, distance_three));
    }
  }

  for (int i = 0; i < text.size() + 1; i++)
  {
    auto distance = dp[pattern.size()][i];
    if (distance <= max_error)
    {
      occurrences.push_back(i);
    }
  }

  return occurrences;
}

int main(int argc, char *argv[])
{
  string pattern = "cada";
  string text = "abadac";
  int max_error = 2;

  cin >> pattern >> max_error >> text;

  auto occurrences = sellers(pattern, text, max_error);
  for (auto ocurrence : occurrences)
  {
    cout << ocurrence << endl;
  }

  return 0;
}