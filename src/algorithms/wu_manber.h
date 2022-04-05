#include <algorithm.h>
#include <vector>
#include <bitset>
#include <string>

class WuManber : public Algorithm
{
private:
  std::vector<std::vector<unsigned long long>> char_masks;

public:
  void initialize(std::vector<std::string> patterns, int max_error)
  {
    for (auto pattern : patterns)
    {
      int m = pattern.size();
      auto char_mask = std::vector<unsigned long long>(128, ~0LLU);

      for (int j = 0; j < m; j++)
      {
        char_mask[pattern[j]] &= ~(1LLU << j);
      }

      char_masks.emplace_back(char_mask);
    }
  };

  std::vector<std::vector<int>> search(std::vector<std::string> patterns, std::string text, int max_error)
  {
    auto response = std::vector<std::vector<int>>();
    int idx = 0;
    for (auto pattern : patterns)
    {
      auto char_mask = char_masks[idx];
      std::vector<int> occurrences;
      int m = pattern.size();
      int n = text.size();

      std::vector<unsigned long long> S(1, ~0LLU);

      for (int q = 1; q < max_error + 1; q++)
      {
        S.push_back(S[q - 1] << 1);
      }

      for (int i = 0; i < n; i++)
      {
        std::vector<unsigned long long> auxS;
        auxS.push_back(((S[0] << 1) | char_mask[text[i]]));

        for (int q = 1; q < max_error + 1; q++)
        {
          auxS.push_back(((S[q] << 1) | char_mask[text[i]]) & (S[q - 1] << 1) & (auxS[q - 1] << 1) & (S[q - 1]));
        }

        S = auxS;
        
        if (!(S[max_error]&(1LLU<<m-1)))
        {
          occurrences.push_back(i);
        }
      }

    response.emplace_back(occurrences);
    idx++;
    }
    return response;
  }
};
