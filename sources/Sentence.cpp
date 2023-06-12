#include "Sentence.h"

#include <algorithm>
#include <cctype>
#include <sstream>

Sentence::Sentence(const std::string &text, Dictionary &dictionary)
    : text_(text) {
  tokenize(dictionary);
}

std::string Sentence::getText() const { return text_; }

std::shared_ptr<SentenceElement> Sentence::getWords() const { return words_; }

std::ostream &operator<<(std::ostream &os, const Sentence &sentence) {
  os << sentence.text_;
  return os;
}

void Sentence::addWord(Word *word) {
  if (words_ == nullptr) {
    words_ = std::make_unique<SentenceElement>(word);
  } else {
    SentenceElement *current = words_.get();
    while (current->getNext() != nullptr) {
      current = current->getNext();
    }
    current->setNext(new SentenceElement(word));
  }
}

Sentence &Sentence::operator+=(Word *word) {
  addWord(word);
  return *this;
}

void Sentence::tokenize(Dictionary &dictionary) {
  std::string normalized_text;

  // Remove non-alpha characters and convert to lowercase
  for (unsigned char c : text_) {
    if (std::isalpha(c)) {
      normalized_text += std::tolower(c);
    } else {
      normalized_text += ' '; // Replace non-alpha characters with spaces
    }
  }

  std::stringstream ss(normalized_text);
  std::string token;
  while (ss >> token) {
    Word *word = dictionary[token];

    if (word) {
      *this += word;
    }
  }
}

// double Sentence::calculate(Measure& measure, TextDocument& text)
// {
//   double sum = 0;
//   int words_number = 0;

//   if (words_ == nullptr) {
//     return 0;
//   } else {
//     SentenceElement* current = words_.get();
//     while (current->getNext() != nullptr) {
//       current = current->getNext();
//     }
//     sum += measure.calculate(*current->getWord(), text);
//     words_number++;
//   }

//   double average = sum / (double)words_number;

//   return average;
// }