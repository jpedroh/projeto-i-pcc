std::vector<int> sliding_window(std::string pattern, std::string text)
{
  std::vector<int> occurrences;
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

  return occurrences;
}
