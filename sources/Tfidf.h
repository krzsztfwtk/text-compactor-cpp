#pragma once

#include "Dictionary.h"
#include "Measure.h"

class Tfidf : public Measure {
public:
  Tfidf(Dictionary &dictionary);

  double calculate(Word word, TextDocument &text) const override;

  // double calculate(const Sentence& sentence, TextDocument& text)
  // const override;

private:
  Dictionary &dictionary_;
};