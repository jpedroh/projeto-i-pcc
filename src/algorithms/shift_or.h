#include <algorithm.h>
#include <vector>
#include <string>

using namespace std;

class ShiftOr : public Algorithm
{
private:
  vector<vector<unsigned long long>> char_masks;

public:
  void initialize(vector<string> patterns, int max_error)
  {
    for (auto pattern : patterns)
    {
      int m = pattern.size();
      auto char_mask = vector<unsigned long long>(128, ~0LLU);

      for (int j = 0; j < m; j++)
      {
        char_mask[pattern[j]] &= ~(1LLU << j);
      }

      char_masks.emplace_back(char_mask);
    }
  };

  vector<vector<int>> search(vector<string> patterns, string text, int max_error)
  {
    auto response = vector<vector<int>>();
    int idx = 0;
    for (auto pattern : patterns)
    {
      auto char_mask = char_masks[idx];
      vector<int> occurrences;
      int m = pattern.size();
      int n = text.size();

      unsigned long long S = ~0LLU;

      for (int i = 0; i < n; i++)
      {
        S = (S << 1) | char_mask[text[i]];
        if ((S & (1LLU << m - 1)) == 0)
        {
          occurrences.push_back(i + 1 - m);
        }
      }
      response.emplace_back(occurrences);
      idx++;
    }
    return response;
  }
};
