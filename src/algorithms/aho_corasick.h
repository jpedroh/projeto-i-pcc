#include <algorithm.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

class AhoCorasick : public Algorithm
{
public:
  void initialize(std::vector<std::string> patterns, int max_error)
  {
    std::vector<std::vector<int>> occurrences;

    auto go_to_out = make_go_to(patterns, &occurrences);
    auto fail_out = make_fail(patterns, go_to_out, &occurrences);

    fsm = FSM{
      go_to : go_to_out,
      occurrences : occurrences,
      fail : fail_out,
    };
  };

  std::vector<std::vector<int>> search(std::vector<std::string> patterns, std::string text, int max_error)
  {
    std::vector<std::vector<int>> occurrences;
    occurrences.resize(patterns.size());
    int n = text.size();
    int cur = 0;
    int i = 0;

    while (i < n)
    {
      while (fsm.go_to[cur].find(text[i]) == fsm.go_to[cur].end() && cur != 0)
      {
        cur = fsm.fail[cur];
      }

      cur = fsm.go_to[cur][text[i]];
      for (auto j : fsm.occurrences[cur])
      {
        occurrences[j].emplace_back(i - patterns[j].length() + 1);
      }

      i++;
    }

    return occurrences;
  }

private:
  struct FSM
  {
    std::vector<std::unordered_map<char, int>> go_to;
    std::vector<std::vector<int>> occurrences;
    std::vector<int> fail;
  };

  FSM fsm;

  std::vector<std::unordered_map<char, int>> make_go_to(std::vector<std::string> patterns, std::vector<std::vector<int>> *occurrences)
  {
    std::vector<std::unordered_map<char, int>> go_to;
    go_to.push_back(std::unordered_map<char, int>());
    occurrences->push_back(std::vector<int>());

    auto cur = 0;
    auto next = 1;

    int k = 0;
    for (auto pattern : patterns)
    {
      cur = 0;
      int j = 0;
      auto m = pattern.length();
      auto c = pattern[j];

      while (j < m && go_to[cur].find(c) != go_to[cur].end())
      {
        cur = go_to[cur][c];
        j++;
        c = pattern[j];
      }
      while (j < m)
      {
        c = pattern[j];
        go_to[cur][c] = next;
        go_to.push_back(std::unordered_map<char, int>());
        occurrences->push_back(std::vector<int>());
        cur = next;
        j++;
        next++;
      }
      occurrences->at(cur).push_back(k);
      k++;
    }

    return go_to;
  }

  std::vector<int> make_fail(std::vector<std::string> patterns, std::vector<std::unordered_map<char, int>> go_to, std::vector<std::vector<int>> *occurrences)
  {
    std::vector<int> fail;
    fail.resize(go_to.size());
    std::fill(fail.begin(), fail.end(), -1);
    std::queue<int> queue;

    for (auto node : go_to[0])
    {
      queue.push(node.second);
      fail[go_to[0][node.first]] = 0;
    }
    while (!queue.empty())
    {
      auto cur = queue.front();
      for (auto suc : go_to[cur])
      {
        queue.push(suc.second);
        auto brd = fail[cur];
        while (brd != 0 && go_to[brd].find(suc.first) == go_to[brd].end())
        {
          brd = fail[brd];
        }
        fail[suc.second] = go_to[brd][suc.first];
        // Adicionar as ocorrencias da falha
        occurrences->at(suc.second).insert(occurrences->at(suc.second).end(), occurrences->at(fail[suc.second]).begin(), occurrences->at(fail[suc.second]).end());
      }
      queue.pop();
    }

    return fail;
  }
};
