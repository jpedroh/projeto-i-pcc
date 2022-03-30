#include <algorithm.h>
#include <vector>
#include <string>

class KMP : public Algorithm
{
private:
  std::vector<int> next;

public:
  void initialize(std::vector<std::string> patterns, int max_error)
  {
    auto pattern = patterns.at(0);
    int m = pattern.size();
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
  };
  std::vector<std::vector<int>> search(std::vector<std::string> patterns, std::string text, int max_error)
  {
    auto pattern = patterns.at(0);
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

    auto response = std::vector<std::vector<int>>();
    response.resize(1);
    response[0] = occurrences;
    return response;
  }
};
