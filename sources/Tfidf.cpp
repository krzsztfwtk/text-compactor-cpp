#include "Tfidf.h"
#include <cmath>

Tfidf::Tfidf(const Dictionary& dictionary) : dictionary_(dictionary) {}

double Tfidf::calculate(const Word& word, TextDocument& text) const {
    unsigned int word_count = text.getWordCount(word);
    unsigned int total_word_count = text.getTotalWordCount();

    double tf = (double)word_count / (double)total_word_count;

    double idf = log(1 / (double)word.getDF());

    return tf * idf;
}