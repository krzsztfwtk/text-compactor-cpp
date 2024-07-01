#include "Tfidf.h"
#include <cmath>

Tfidf::Tfidf(Dictionary &dictionary, Query *query)
    : dictionary_(dictionary), query_(query) {}

double Tfidf::calculate(Word word, TextDocument &text) const {
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
  unsigned int total_word_count = text.getTotalWordCount();

  double tf =
      static_cast<double>(word_count) / static_cast<double>(total_word_count);

  double idf = log(static_cast<double>(dictionary_.getDfSum()) /
                   static_cast<double>(word.getDF()));

  double importance = tf * idf;

  importance *= importance_multiplier;

  return importance;
}
