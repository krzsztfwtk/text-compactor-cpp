#include "TextDocument.h"

#include <fstream>
#include <sstream>

TextDocument::TextDocument(const std::string& filename,
                           Dictionary& dictionary) {
  loadFromFile(filename, dictionary);
}

void TextDocument::loadFromFile(const std::string& filename,
                                Dictionary& dictionary) {
  std::ifstream file(filename);

  std::stringstream buffer;
  buffer << file.rdbuf();
  file.close();

  parseSentences(buffer.str(), dictionary);
  countWords();
}

std::string TextDocument::getText() const {
  std::string result;
  for (const auto& sentence : sentences_) {
    if (!result.empty()) {
      result += ' ';
    }
    result += sentence.getText();
  }
  return result;
}

unsigned int TextDocument::getWordCount(const Word& word) 
  { return word_count_[word.getLemmatization()]; }

// unsigned int TextDocument::getWordCount(const std::string& word)
//   { return word_count_[word]; }

unsigned int TextDocument::getTotalWordCount()
  { return total_word_count; }

std::list<Sentence> TextDocument::getSentences() const { return sentences_; }

void TextDocument::parseSentences(const std::string& text,
                                  Dictionary& dictionary) {
  sentences_.clear();
  std::string current_sentence;
  for (char c : text) {
    current_sentence.push_back(c);
    if (c == '.' || c == '!' || c == '?') {
      sentences_.emplace_back(current_sentence, dictionary);
      current_sentence.clear();
    }
  }
  if (!current_sentence.empty()) {
    sentences_.emplace_back(current_sentence, dictionary);
  }
}

void TextDocument::countWords() {
  for (const Sentence& sentence : sentences_)
  {
    SentenceElement* current = sentence.getWords().get();

    while (current->getNext() != nullptr) {
      word_count_[current->getWord()->getLemmatization()]++;
      total_word_count++;
      current = current->getNext();
    }
  }
}