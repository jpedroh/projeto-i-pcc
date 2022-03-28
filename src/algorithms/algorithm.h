#include <vector>
#include <string>

class Algorithm
{
public:
  virtual void initialize(std::vector<std::string> patterns, int max_error) = 0;
  virtual std::vector<int> search(std::vector<std::string> patterns, std::string line, int max_error) = 0;
};