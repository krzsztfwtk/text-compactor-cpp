#pragma once

#include "Dictionary.h"
#include "Measure.h"
#include "Query.h"

class BM25 : public Measure {
public:
  BM25(Dictionary &dictionary, Query *query = nullptr, double k1 = 1.5,
       double b = 0.75);

  double calculate(Word word, TextDocument &text) const override;

private:
  Dictionary &dictionary_;
  const Query *query_;
  double k1_;
  double b_;
};
