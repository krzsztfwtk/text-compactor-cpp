#pragma once

#include <unordered_map>
#include <string>
#include <fstream>
#include <memory>

#include "Word.h"
#include "StopWords.h"

class Dictionary {
public:
    Dictionary();
    Dictionary(const std::string& filename);

    void loadFromFile(const std::string& filename);
    std::shared_ptr<Word> operator[](const std::string& key);
    Dictionary& operator+=(const Word& word);

    void removeStopWords(const StopWords& stop_words);

private:
    std::unordered_map<std::string, std::shared_ptr<Word>> words_;
};
