#include "Dictionary.h"

#include <fstream>
#include <iostream>

Dictionary::Dictionary() {}

Dictionary::Dictionary(const std::string &filename) { loadFromFile(filename); }

Dictionary::Dictionary(const std::vector<std::pair<std::string, int>>
                           &wordlist_filenames_with_weights) {
  loadFromFilesVector(wordlist_filenames_with_weights);
}

void Dictionary::loadFromFile(const std::string &filename, int weight) {
  if (weight == 0) {
    return;
  }

  std::ifstream file(filename);

  std::string name, lemmatization;
  unsigned int df;

  while (file >> name >> lemmatization >> df) {
    if (words_.find(name) == words_.end()) {
      Word word(name, lemmatization, df * weight);
      words_[name] = word;
    } else {
      words_[name].addDF(df * weight);
    }
  }
}

void Dictionary::loadFromFilesVector(
    const std::vector<std::pair<std::string, int>>
        &wordlist_filenames_with_weights) {
  words_.clear();

  for (const auto &[filename, weight] : wordlist_filenames_with_weights) {
    loadFromFile(filename, weight);
  }
}

// https://stackoverflow.com/questions/13354394/reading-object-from-const-unordered-map
Word *Dictionary::operator[](const std::string &key) {
  auto it = words_.find(key);
  if (it != words_.end()) {
    return &it->second;
  }
  return nullptr;
}

Dictionary &Dictionary::operator+=(const Word &word) {
  words_[word.getName()] = word;
  return *this;
}

void Dictionary::removeStopWords(const StopWords &stop_words) {
  for (const auto &stop_word : stop_words.getWords()) {
    words_.erase(stop_word);
  }
}
