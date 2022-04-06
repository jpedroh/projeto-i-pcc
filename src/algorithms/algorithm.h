#include <vector>
#include <string>

#ifndef Algorithm_H
#define Algorithm_H

using namespace std;

class Algorithm
{
public:
  virtual void initialize(vector<string> patterns, int max_error) = 0;
  virtual vector<vector<int>> search(vector<string> patterns, string line, int max_error) = 0;
};
#endif