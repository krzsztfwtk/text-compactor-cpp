#pragma once

#include <string>
#include <unordered_set>

class StopWords {
public:
    StopWords();
    StopWords(const std::string& filename);

    void loadFromFile(const std::string& filename);
    bool isStopWord(const std::string& word) const;
    bool operator()(const std::string& word) const;

    const std::unordered_set<std::string>& getWords() const;

private:
    std::unordered_set<std::string> stop_words_;
};
