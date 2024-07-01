#include "Query.h"
#include <algorithm>
#include <fstream>
#include <iostream>

Query::Query(const std::string &filename, double boost_factor)
    : boost_factor_(boost_factor) {
  loadFromFile(filename);
}

bool Query::contains(const Word &word) const {
  std::string word_str = word.getName();
  return std::find(query_words_.begin(), query_words_.end(), word_str) !=
         query_words_.end();
}

unsigned int Query::getWordCount(const Word &word) const {
  std::string word_str = word.getName();
  auto it = std::find(query_words_.begin(), query_words_.end(), word_str);
  if (it != query_words_.end()) {
    size_t index = std::distance(query_words_.begin(), it);
    return word_counts_[index];
  }
  return 0;
}

double Query::getBoostFactor() const { return boost_factor_; }

void Query::loadFromFile(const std::string &filename) {
  std::ifstream file(filename);
  std::string word;

  while (file >> word) {
    auto it = std::find(query_words_.begin(), query_words_.end(), word);
    if (it != query_words_.end()) {
      size_t index = std::distance(query_words_.begin(), it);
      word_counts_[index]++;
    } else {
      query_words_.push_back(word);
      word_counts_.push_back(1);
    }
  }
}
