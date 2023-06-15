#pragma once

#include "Dictionary.h"
#include "Measure.h"

class PseudoTfidf : public Measure {
public:
  PseudoTfidf(const Dictionary &dictionary);

  double calculate(Word word, TextDocument &text) const override;

  // double calculate(const Sentence& sentence, TextDocument& text)
  // const override;

private:
  const Dictionary &dictionary_;
};