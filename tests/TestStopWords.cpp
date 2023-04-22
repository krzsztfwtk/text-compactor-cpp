#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../sources/StopWords.h"
#include <vector>
#include <string>

TEST_CASE("Test StopWords class with example file", "[StopWords]") {
    StopWords stopWords;
    stopWords.loadFromFile("test_input_files/test_stop_words_1.txt");

    SECTION("Check if the stop words are loaded correctly and operator() works") {
        std::vector<std::string> wordsFromFile = {"a", "an", "the", 
        "and", "it", "for", "or", "but", "in", "my", "your", "our", "their"};

        for (const auto& w : wordsFromFile) {
            REQUIRE(stopWords(w));
        }
    }

    SECTION("Check if the StopWords class works correctly with words not in the file") {
        std::vector<std::string> nonStopWords = {"apple", "banana", 
        "car", "dog", "elephant"};

        for (const auto& w : nonStopWords) {
            REQUIRE(!stopWords(w));
        }
    }
}
