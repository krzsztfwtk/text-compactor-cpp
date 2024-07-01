#include "BM25.h"
#include <cmath>

BM25::BM25(Dictionary &dictionary, Query *query, double k1, double b)
    : dictionary_(dictionary), query_(query), k1_(k1), b_(b) {}

double BM25::calculate(Word word, TextDocument &text) const {
  Word original_word = word;
  if (word.getLemmatization() != word.getName()) {
    Word *lemmatized_word = dictionary_[word.getLemmatization()];
    if (lemmatized_word) {
      word = *lemmatized_word;
    }
  }

  double importance_multiplier = 1.0;
  if (query_) {
    if (query_->contains(word)) {
      importance_multiplier *= (1 + query_->getBoostFactor());
    } else if (word.getLemmatization() != word.getName() 
                  && query_->contains(original_word)) {
      importance_multiplier *= (1 + query_->getBoostFactor());
    }
  }

  unsigned int word_count = text.getWordCount(word);
  // unsigned int total_word_count = text.getTotalWordCount();
  unsigned int doc_length = text.getTotalWordCount();
  unsigned int avg_doc_length =
      doc_length; // Assuming we don't have a collection of documents to compute
                  // avg length

  double idf = log(
      (dictionary_.getDfSum() - word.getDF() + 0.5) / (word.getDF() + 0.5) + 1);

  double tf =
      (word_count * (k1_ + 1)) /
      (word_count + k1_ * (1 - b_ + b_ * (doc_length / avg_doc_length)));

  double importance = idf * tf;

  if (!query_) {
    return importance;
  }

  if (query_->contains(word)) {
    importance *= (1 + query_->getBoostFactor());
  }

  importance *= importance_multiplier;

  return importance;
}
