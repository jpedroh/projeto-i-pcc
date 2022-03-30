#include <algorithm.h>
#include <vector>
#include <bitset>
#include <string>

class ShiftOr : public Algorithm
{
private:
  std::vector<std::bitset<1024>> char_mask;

public:
  void initialize(std::vector<std::string> patterns, int max_error)
  {
    auto pattern = patterns.at(0);
    int m = pattern.size();
    this->char_mask.resize(128);
    fill(this->char_mask.begin(), this->char_mask.end(), ~(0b0 << m));

    for (int j = 0; j < m; j++)
    {
      this->char_mask[pattern[j]][j] = 0;
    }
  };

  std::vector<std::vector<int>> search(std::vector<std::string> patterns, std::string text, int max_error)
  {
    auto pattern = patterns.at(0);
    std::vector<int> occurrences;
    int m = pattern.size();
    int n = text.size();

    std::bitset<1024> S;
    S = ~(0b0 << (m - 1));

    for (int i = 0; i < n; i++)
    {
      S = (S << 1) | this->char_mask[text[i]];
      if (S[m - 1] == 0)
      {
        occurrences.push_back(i + 1 - m);
      }
    }

    auto response = std::vector<std::vector<int>>();
    response.resize(1);
    response[0] = occurrences;
    return response;
  }
};
