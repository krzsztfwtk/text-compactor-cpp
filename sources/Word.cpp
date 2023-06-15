#include <istream>

#include "Word.h"

Word::Word(const std::string &name, const std::string &lemmatization,
           unsigned int df)
    : name_(name), lemmatization_(lemmatization), df_(df) {}

std::string Word::getName() const { return name_; }

std::string Word::getLemmatization() const { return lemmatization_; }

unsigned int Word::getDF() const { return df_; }

void Word::setName(const std::string &name) { this->name_ = name; }

void Word::setLemmatization(const std::string &lemmatization) {
  this->lemmatization_ = lemmatization;
}

void Word::setDF(unsigned int df) { this->df_ = df; }

void Word::addDF(unsigned int value) { this->df_ += value; }

std::ostream &operator<<(std::ostream &os, const Word &word) {
  os << word.getName();
  return os;
}

std::istream& operator>>(std::istream& is, Word& word) {
  std::string name, lemmatization;
  unsigned int df = 0;

  if (is >> name >> lemmatization >> df) {
    word.name_ = name;
    word.lemmatization_ = lemmatization;
    word.df_ = df;
  }

  return is;
}