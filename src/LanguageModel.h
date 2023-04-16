#include <string>
#include <unordered_map>
#include "Word.h"


class LanguageModel{
public:
    double calculateTFIDF(std::string);

private:
    std::unordered_map<std::string, Word> words;
};