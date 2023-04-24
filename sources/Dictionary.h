#pragma once

#include <unordered_map>
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include <utility>

#include "Word.h"
#include "StopWords.h"

class Dictionary {
public:
    Dictionary();
    Dictionary(const std::string& filename);
    Dictionary(const std::vector<std::pair<std::string, int>>
    & wordlist_filenames_with_weights);

    void loadFromFile(const std::string& filename, int weight = 1);
    void loadFromFilesVector(const std::vector<std::pair<std::string, int>>
    & wordlist_filenames_with_weights);

    Word* operator[](const std::string& key);
    Dictionary& operator+=(const Word& word);

    void removeStopWords(const StopWords& stop_words);

private:
    std::unordered_map<std::string, Word> words_;
};
