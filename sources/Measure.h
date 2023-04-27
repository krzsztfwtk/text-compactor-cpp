#pragma once

#include <string>

#include "TextDocument.h"
#include "Word.h"

class Measure {
 public:
  virtual ~Measure() = default;

  virtual double calculate(const Word& word,
                           const TextDocument& text) const = 0;
};
