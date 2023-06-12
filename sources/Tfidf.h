#pragma once

#include "Dictionary.h"
#include "Measure.h"

class Tfidf : public Measure {
public:
  Tfidf(const Dictionary &dictionary);

  double calculate(const Word &word, TextDocument &text) const override;

  // double calculate(const Sentence& sentence, TextDocument& text)
  // const override;

private:
  const Dictionary &dictionary_;
};