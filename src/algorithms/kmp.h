#include <algorithm.h>
#include <vector>
#include <string>

using namespace std;

class KMP : public Algorithm
{
private:
  vector<vector<int>> nexts;

public:
  void initialize(vector<string> patterns, int max_error)
  {
    for (auto pattern : patterns)
    {
      int m = pattern.size();
      vector<int> next;
      next.resize(m + 1);
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
      nexts.emplace_back(next);
    }
  };
  vector<vector<int>> search(vector<string> patterns, string text, int max_error)
  {
    auto response = vector<vector<int>>();
    int idx = 0;
    for (auto pattern : patterns)
    {
      auto next = nexts[idx];
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

      response.emplace_back(occurrences);
      idx++;
    }
    return response;
  }
};
