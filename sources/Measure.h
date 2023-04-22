#pragma once

#include <string>
#include "Word.h"
#include "TextDocument.h"

class Measure {
public:
    virtual ~Measure() = default;

    virtual double calculate(const Word& word, const TextDocument& text) const = 0;
};
