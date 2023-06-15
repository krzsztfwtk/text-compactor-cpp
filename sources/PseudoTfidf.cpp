#include "PseudoTfidf.h"
#include <cmath>

PseudoTfidf::PseudoTfidf(const Dictionary &dictionary)
    : dictionary_(dictionary) {}

double PseudoTfidf::calculate(Word word, TextDocument &text) const {
  unsigned int word_count = text.getWordCount(word);
  unsigned int total_word_count = text.getTotalWordCount();

  double tf = (double)word_count / (double)total_word_count;

  double idf = dictionary_.getDfSum() / (double)word.getDF();

  return tf * idf;
}