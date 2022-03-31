#include <algorithm.h>
#include <vector>
#include <bitset>
#include <string>

class ShiftOr : public Algorithm
{
private:
  std::vector<unsigned long long> char_mask;

public:
  void initialize(std::vector<std::string> patterns, int max_error)
  {
    auto pattern = patterns.at(0);
    int m = pattern.size();
    this->char_mask = std::vector<unsigned long long>(128, ~0);

    for (int j = 0; j < m; j++)
    {
      this->char_mask[pattern[j]] &= ~(1 << j);
    }
  };

  std::vector<std::vector<int>> search(std::vector<std::string> patterns, std::string text, int max_error)
  {
    auto pattern = patterns.at(0);
    std::vector<int> occurrences;
    int m = pattern.size();
    int n = text.size();

    unsigned long long S = ~(0 << m);

    for (int i = 0; i < n; i++)
    {
      S = (S << 1) | this->char_mask[text[i]];
      if (!(S&(1<<m-1)))
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
