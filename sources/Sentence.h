#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "Dictionary.h"
#include "SentenceElement.h"
#include "Word.h"
// #include "Measure.h"
// #include "TextDocument.h"

class Sentence {
public:
  Sentence(const std::string &text, Dictionary &dictionary);

  std::string getText() const;
  std::shared_ptr<SentenceElement> getWords() const;

  void addWord(Word *word);
  Sentence &operator+=(Word *word);

  friend std::ostream &operator<<(std::ostream &os, const Sentence &sentence);
  // odczyt zapis symetrycznie

  double importance = 0;

private:
  std::string text_;
  std::shared_ptr<SentenceElement> words_;

  void tokenize(Dictionary &dictionary);
};
