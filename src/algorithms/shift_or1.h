#include <algorithm.h>
#include <vector>
#include <bitset>
#include <string>

using namespace std;

class ShiftOr : public Algorithm
{
private:
  vector<bitset<64>> char_mask;

public:
  void initialize(vector<string> patterns, int max_error)
  {
    auto pattern = patterns.at(0);
    int m = pattern.size();
    this->char_mask = vector<bitset<64>>(128, ~(0b0 << m));

    for (int j = 0; j < m; j++)
    {
      this->char_mask[pattern[j]][j] = 0;
    }

  };

  vector<vector<int>> search(vector<string> patterns, string text, int max_error)
  {
    auto pattern = patterns.at(0);
    vector<int> occurrences;
    int m = pattern.size();
    int n = text.size();

    bitset<64> S;
    S = ~(0b0 << (m - 1));
  
    for (int i = 0; i < n; i++)
    {
      S = (S << 1) | this->char_mask[text[i]];
      if (S[m - 1] == 0)
      {
        occurrences.push_back(i + 1 - m);
      }
    }

    auto response = vector<vector<int>>();
    response.resize(1);
    response[0] = occurrences;
    return response;
  }
};
