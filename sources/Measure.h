#pragma once

#include <string>

#include "Sentence.h"
#include "TextDocument.h"
#include "Word.h"

class Measure {
public:
  virtual ~Measure() = default;

  virtual double calculate(Word word, TextDocument &text) const = 0;

  //   virtual double calculate(const Sentence& sentence,
  //                          TextDocument& text) const = 0;
};
