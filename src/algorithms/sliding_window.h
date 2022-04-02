#include <algorithm.h>
#include <vector>
#include <string>

class SlidingWindow : public Algorithm
{
public:
  void initialize(std::vector<std::string> patterns, int max_error){};
  std::vector<std::vector<int>> search(std::vector<std::string> patterns, std::string text, int max_error)
  {
    auto response = std::vector<std::vector<int>>();
    // std::cout << patterns.size() << '\t' << '\t' << text << std::endl;
    for (auto pattern : patterns)
    {
      std::vector<int> occurrences;
      int m = pattern.size();
      int n = text.size();

      for (int i = 0; i < n - m + 1; i++)
      {
        for (int j = 0; j < m; j++)
        {
          if (pattern[j] != text[j + i])
          {
            break;
          }
          else if (j == m - 1)
          {
            occurrences.push_back(i);
          }
        }
      }
      response.push_back(occurrences);
    }
    return response;
  }
};
