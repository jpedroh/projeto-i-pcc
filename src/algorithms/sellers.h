#include <algorithm.h>
#include <vector>
#include <string>

class Sellers : public Algorithm
{
public:
  void initialize(std::vector<std::string> patterns, int max_error){};
  std::vector<int> search(std::vector<std::string> patterns, std::string text, int max_error)
  {
    auto pattern = patterns.at(0);
    std::vector<int> occurrences;
    std::vector<std::vector<int>> dp(pattern.length() + 1);
    std::fill(dp.begin(), dp.end(), std::vector<int>(text.length() + 1));
    std::fill(dp[0].begin(), dp[0].end(), 0);

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
        dp[i][j] = std::min(distance_one, std::min(distance_two, distance_three));
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
};
