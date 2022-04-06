#include <algorithm.h>
#include <vector>
#include <string>

using namespace std;

class SlidingWindow : public Algorithm
{
public:
  void initialize(vector<string> patterns, int max_error){};
  vector<vector<int>> search(vector<string> patterns, string text, int max_error)
  {
    auto response = vector<vector<int>>();
    // cout << patterns.size() << '\t' << '\t' << text << endl;
    for (auto pattern : patterns)
    {
      vector<int> occurrences;
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
