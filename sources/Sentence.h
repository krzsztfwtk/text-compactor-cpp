#pragma once

#include <string>
#include <vector>
#include <memory>
#include <ostream>
#include "Word.h"
#include "Dictionary.h"

class Sentence {
public:
    Sentence(const std::string& text, Dictionary& dictionary);

    std::string getText() const;

    friend std::ostream& operator<<(std::ostream& os, const Sentence& sentence); 
    //odczyt zapis symetrycznie

private:
    std::string text_;
    std::vector<Word*> words_;

    void tokenize(Dictionary& dictionary);
};
