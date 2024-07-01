#pragma once

#include "Dictionary.h"
#include "Measure.h"
#include "Query.h"

class Tfidf : public Measure {
public:
  Tfidf(Dictionary &dictionary, Query *query = nullptr);

  double calculate(Word word, TextDocument &text) const override;

private:
  Dictionary &dictionary_;
  const Query *query_;
};
