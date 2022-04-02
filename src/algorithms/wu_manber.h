#include <algorithm.h>
#include <vector>
#include <bitset>
#include <string>

class WuManber : public Algorithm
{
private:
  std::vector<unsigned long long> char_mask;

public:
  void initialize(std::vector<std::string> patterns, int max_error)
  {
    auto pattern = patterns.at(0);
    int m = pattern.size();
    this->char_mask = std::vector<unsigned long long>(128, ~0LLU);

    for (int j = 0; j < m; j++)
    {
      this->char_mask[pattern[j]] &= ~(1LLU << j);
    }
  };

  std::vector<std::vector<int>> search(std::vector<std::string> patterns, std::string text, int max_error)
  {
    auto pattern = patterns.at(0);
    std::vector<int> occurrences;
    int m = pattern.size();
    int n = text.size();

    std::vector<unsigned long long> S(1, ~0LLU);

    for(int q = 1; q < max_error+1; q++)
    {
      S.push_back(S[q-1] << 1);
    }
  
    for (int i = 0; i < n; i++)
    {  
        std::vector<unsigned long long> auxS;
        auxS.push_back(((S[0] << 1) | this->char_mask[text[i]]));  
        
        for(int q = 1; q < max_error+1; q++)
        {
            auxS.push_back(((S[q] << 1) | this->char_mask[text[i]]) & (S[q-1] << 1) & (auxS[q-1] << 1) & (S[q - 1]));
        }
        
        S = auxS;
        
        if (!(S[max_error]&(1LLU<<m-1)))
        {
          occurrences.push_back(i);
        }
    }

    auto response = std::vector<std::vector<int>>();
    response.resize(1);
    response[0] = occurrences;
    return response;
  }
};
