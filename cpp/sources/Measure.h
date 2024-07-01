#pragma once

#include "Query.h"
#include "Sentence.h"
#include "TextDocument.h"
#include "Word.h"
#include <string>

class Measure {
public:
  virtual ~Measure() = default;
  virtual double calculate(Word word, TextDocument &text) const = 0;
};
