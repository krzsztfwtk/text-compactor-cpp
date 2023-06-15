#include "StopWords.h"

#include <fstream>
#include <sstream>

StopWords::StopWords() {}

StopWords::StopWords(const std::string &filename) { loadFromFile(filename); }

void StopWords::loadFromFile(const std::string &filename) {
  std::ifstream file(filename);

  file >> *this;

  file.close();
}

bool StopWords::isStopWord(const std::string &word) const {
  return stop_words_.find(word) != stop_words_.end();
}

bool StopWords::operator()(const std::string &word) const {
  return isStopWord(word);
}

const std::unordered_set<std::string> &StopWords::getWords() const {
  return stop_words_;
}

std::istream& operator>>(std::istream& is, StopWords& stopwords) {
  std::string word;
  
  while (is >> word) {
    stopwords.stop_words_.insert(word);
  }

  return is;
}