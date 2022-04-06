#include <algorithm.h>
#include <vector>
#include <bitset>
#include <string>

using namespace std;

class WuManber : public Algorithm
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

      vector<unsigned long long> S(1, ~0LLU);

      for (int q = 1; q < max_error + 1; q++)
      {
        S.push_back(S[q - 1] << 1);
      }

      for (int i = 0; i < n; i++)
      {
        vector<unsigned long long> auxS;
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
