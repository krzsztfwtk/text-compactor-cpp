#pragma once

#include <string>
#include <list>
#include <memory>
#include <ostream>
#include "Word.h"
#include "Dictionary.h"

class Sentence {
public:
    Sentence(const std::string& text, Dictionary& dictionary);

    std::string getText() const;

    friend std::ostream& operator<<(std::ostream& os, const Sentence& sentence);

private:
    std::string text_;
    std::list<std::shared_ptr<const Word>> words_;

    void tokenize(Dictionary& dictionary);
};
