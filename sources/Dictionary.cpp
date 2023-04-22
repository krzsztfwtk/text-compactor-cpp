#include "Dictionary.h"

Dictionary::Dictionary() {}

Dictionary::Dictionary(const std::string& filename) {
    loadFromFile(filename);
}

void Dictionary::loadFromFile(const std::string& filename) {
    words_.clear();
    std::ifstream file(filename);

    std::string name, lemmatization;
    unsigned int idf;

    while (file >> name >> lemmatization >> idf) {
        auto pWord = std::make_shared<Word>(name, lemmatization, idf);
        words_[name] = pWord;
    }
}

// https://stackoverflow.com/questions/13354394/reading-object-from-const-unordered-map
std::shared_ptr<Word> Dictionary::operator[](const std::string& key) {
    return words_[key];
}

Dictionary& Dictionary::operator+=(const Word& word) {
    auto word_ptr = std::make_shared<Word>(word);
    words_[word.getName()] = word_ptr;
    return *this;
}

void Dictionary::removeStopWords(const StopWords& stop_words) {
    for (const auto& stop_word : stop_words.getWords()) {
        words_.erase(stop_word);
    }
}