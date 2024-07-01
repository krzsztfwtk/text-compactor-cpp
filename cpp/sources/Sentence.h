#pragma once

#include <list>
#include <memory>
#include <ostream>
#include <string>

#include "Dictionary.h"
#include "Word.h"

class Sentence {
public:
  Sentence(const std::string &text, Dictionary &dictionary);

  std::string getText() const;
  const std::list<Word *> &getWords() const;

  void addWord(Word *word);
  Sentence &operator+=(Word *word);

  friend std::ostream &operator<<(std::ostream &os, const Sentence &sentence);

  double importance = 0;

private:
  std::string text_;
  std::list<Word *> words_;

  void tokenize(Dictionary &dictionary);
};
