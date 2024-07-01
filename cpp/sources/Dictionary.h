#pragma once

#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "StopWords.h"
#include "Word.h"

class Dictionary {
public:
  Dictionary();
  Dictionary(const std::string &filename);
  Dictionary(const std::vector<std::pair<std::string, int>>
                 &wordlist_filenames_with_weights);

  void loadFromFile(const std::string &filename, int weight = 1);

  void loadFromFilesVector(const std::vector<std::pair<std::string, int>>
                               &wordlist_filenames_with_weights);

  Word *operator[](const std::string &key);
  Dictionary &operator+=(const Word &word);

  void removeStopWords(const StopWords &stop_words);

  // void boostWordsBasedOnQuery(const Query &query, double boost_factor);

  unsigned int getDfSum() const;

private:
  std::unordered_map<std::string, Word> words_;
  unsigned int df_sum = 0;
};
