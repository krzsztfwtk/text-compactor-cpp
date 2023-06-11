#include "SentenceElement.h"

SentenceElement::SentenceElement(Word* word) : word_(word), next_(nullptr) {}

Word* SentenceElement::getWord() { 
  return word_; 
}

SentenceElement* SentenceElement::getNext() { 
  return next_.get(); 
}

void SentenceElement::setNext(SentenceElement* next) {
  next_ = std::unique_ptr<SentenceElement>(next); 
}