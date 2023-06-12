#pragma once

#include <list>
#include <string>
#include <unordered_map>

#include "Sentence.h"

class TextDocument {
public:
  TextDocument(const std::string &filename, Dictionary &dictionary);

  void loadFromFile(const std::string &filename, Dictionary &dictionary);
  std::string getText() const;
  unsigned int getWordCount(const Word &word);
  // unsigned int getWordCount(const std::string& word);
  unsigned int getTotalWordCount();

  std::list<Sentence> getSentences() const;

private:
  std::list<Sentence> sentences_;
  std::unordered_map<std::string, unsigned int> word_count_;
  unsigned int total_word_count = 0;

  void parseSentences(const std::string &text, Dictionary &dictionary);
  void countWords();
};
