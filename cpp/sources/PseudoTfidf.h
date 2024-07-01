#pragma once

#include "Dictionary.h"
#include "Measure.h"
#include "Query.h"

class PseudoTfidf : public Measure {
public:
  PseudoTfidf(const Dictionary &dictionary, Query *query = nullptr);

  double calculate(Word word, TextDocument &text) const override;

private:
  const Dictionary &dictionary_;
  const Query *query_;
};
