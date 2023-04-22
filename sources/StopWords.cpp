#include "StopWords.h"
#include <fstream>
#include <sstream>

StopWords::StopWords() {}

StopWords::StopWords(const std::string& filename) {
    loadFromFile(filename);
}

void StopWords::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    std::string word;

    while (file >> word)
    {
        stop_words_.insert(word);
    }
    
    file.close();
}

bool StopWords::isStopWord(const std::string& word) const {
    return stop_words_.find(word) != stop_words_.end();
}

bool StopWords::operator()(const std::string& word) const {
    return isStopWord(word);
}

const std::unordered_set<std::string>& StopWords::getWords() const {
    return stop_words_;
}