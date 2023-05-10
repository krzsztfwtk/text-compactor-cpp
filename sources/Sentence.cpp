#include "Sentence.h"

#include <algorithm>
#include <cctype>
#include <sstream>

Sentence::Sentence(const std::string& text, Dictionary& dictionary)
    : text_(text) {
  tokenize(dictionary);
}

std::string Sentence::getText() const { return text_; }

std::vector<Word*> Sentence::getWords() const { return words_; }

std::ostream& operator<<(std::ostream& os, const Sentence& sentence) {
  os << sentence.text_;
  return os;
}

void Sentence::tokenize(Dictionary& dictionary) {
  words_.clear();
  std::string normalized_text;

  // Remove non-alpha characters and convert to lowercase
  for (unsigned char c : text_) {
    if (std::isalpha(c)) {
      normalized_text += std::tolower(c);
    } else {
      normalized_text += ' ';  // Replace non-alpha characters with spaces
    }
  }

  std::stringstream ss(normalized_text);
  std::string token;
  while (ss >> token) {
    Word* word = dictionary[token];

    if (word) {
      words_.push_back(word);
    }
  }
}
