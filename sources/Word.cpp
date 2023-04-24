#include "Word.h"

Word::Word(const std::string& name, const std::string& lemmatization, unsigned int idf)
    : name_(name), lemmatization_(lemmatization), idf_(idf) {}

std::string Word::getName() const {
    return name_;
}

std::string Word::getLemmatization() const {
    return lemmatization_;
}

unsigned int Word::getIDF() const {
    return idf_;
}

void Word::setName(const std::string& name) {
    this->name_ = name;
}

void Word::setLemmatization(const std::string& lemmatization) {
    this->lemmatization_ = lemmatization;
}

void Word::setIDF(unsigned int idf) {
    this->idf_ = idf;
}

void Word::addIdf(unsigned int value) {
    this->idf_ += value;
}