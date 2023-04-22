#pragma once

#include <list>
#include <string>
#include "Sentence.h"

class TextDocument {
public:
    TextDocument(const std::string& filename, Dictionary& dictionary);

    void loadFromFile(const std::string& filename, Dictionary& dictionary);
    std::string getText() const;

    std::list<Sentence> getSentences() const;

private:
    std::list<Sentence> sentences_;

    void parseSentences(const std::string& text, Dictionary& dictionary);
};
