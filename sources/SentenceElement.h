#pragma once

#include "Word.h"
#include <memory>

class SentenceElement {
public:
  explicit SentenceElement(Word *word);

  Word *getWord();
  SentenceElement *getNext();
  void setNext(SentenceElement *next);
  SentenceElement *getNext() const;

private:
  Word *word_;
  std::unique_ptr<SentenceElement> next_;
};
