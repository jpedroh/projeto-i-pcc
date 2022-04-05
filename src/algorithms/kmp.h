#include <algorithm.h>
#include <vector>
#include <string>

class KMP : public Algorithm
{
private:
  std::vector<std::vector<int>> nexts;

public:
  void initialize(std::vector<std::string> patterns, int max_error)
  {
    for (auto pattern : patterns)
    {
      int m = pattern.size();
      std::vector<int> next;
      next.resize(m + 1);
      std::fill(next.begin(), next.end(), 0);
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
        j = std::max(0, next[j]);
      }
      nexts.emplace_back(next);
    }
  };
  std::vector<std::vector<int>> search(std::vector<std::string> patterns, std::string text, int max_error)
  {
    auto response = std::vector<std::vector<int>>();
    int idx = 0;
    for (auto pattern : patterns)
    {
      auto next = nexts[idx];
      std::vector<int> occurrences;
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
        j = std::max(0, next[j]);
      }

      response.emplace_back(occurrences);
      idx++;
    }
    return response;
  }
};
