#pragma once

#include <string>

#include "TextDocument.h"
#include "Word.h"
#include "Sentence.h"

class Measure {
 public:
  virtual ~Measure() = default;

  virtual double calculate(const Word& word,
                         TextDocument& text) const = 0;

  virtual double calculate(const Sentence& sentence,
                         TextDocument& text) const = 0;
};
