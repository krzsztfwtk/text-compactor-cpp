#pragma once

#include "Word.h"
#include <string>
#include <vector>

class Query {
public:
  Query(const std::string &filename, double boost_factor = 1.0);

  bool contains(const Word &word) const;
  unsigned int getWordCount(const Word &word) const;
  double getBoostFactor() const;

private:
  std::vector<std::string> query_words_;
  std::vector<unsigned int> word_counts_;
  double boost_factor_;

  void loadFromFile(const std::string &filename);
};
