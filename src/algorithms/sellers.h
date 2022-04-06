#include <algorithm.h>
#include <vector>
#include <string>

using namespace std;

class Sellers : public Algorithm
{
public:
  void initialize(vector<string> patterns, int max_error){};
  vector<vector<int>> search(vector<string> patterns, string text, int max_error)
  {
    auto response = vector<vector<int>>();
    response.resize(patterns.size());
    for (auto pattern : patterns)
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
      response.emplace_back(occurrences);
    }
    return response;
  }
};
