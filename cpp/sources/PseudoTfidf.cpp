#include "PseudoTfidf.h"
#include <cmath>

PseudoTfidf::PseudoTfidf(const Dictionary &dictionary, Query *query)
    : dictionary_(dictionary), query_(query) {}

double PseudoTfidf::calculate(Word word, TextDocument &text) const {
  unsigned int word_count = text.getWordCount(word);
  unsigned int total_word_count = text.getTotalWordCount();

  double tf =
      static_cast<double>(word_count) / static_cast<double>(total_word_count);

  double idf = static_cast<double>(dictionary_.getDfSum()) /
               static_cast<double>(word.getDF());

  double importance = tf * idf;

  if (!query_) {
    return importance;
  }

  if (query_->contains(word)) {
    importance *= (1 + query_->getBoostFactor());
  }

  return importance;
}
