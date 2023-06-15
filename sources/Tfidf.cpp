#include "Tfidf.h"
#include <cmath>

Tfidf::Tfidf(Dictionary &dictionary) : dictionary_(dictionary) {}

double Tfidf::calculate(Word word, TextDocument &text) const {
  if (word.getLemmatization() != word.getName()) {
    Word *lemmatized_word = dictionary_[word.getLemmatization()];
    if (lemmatized_word) {
      word = *lemmatized_word;
    }
  }

  unsigned int word_count = text.getWordCount(word);
  unsigned int total_word_count = text.getTotalWordCount();

  double tf = (double)word_count / (double)total_word_count;

  double idf = log((double)dictionary_.getDfSum() / (double)word.getDF());

  return tf * idf;
}