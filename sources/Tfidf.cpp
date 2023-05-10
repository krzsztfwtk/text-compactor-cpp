#include "Tfidf.h"
#include <cmath>

Tfidf::Tfidf(const Dictionary& dictionary) : dictionary_(dictionary) {}

double Tfidf::calculate(const Word& word, TextDocument& text) const {
    unsigned int word_count = text.getWordCount(word);
    unsigned int total_word_count = text.getTotalWordCount();

    double tf = (double)word_count / (double)total_word_count;

    return tf;
}

// double Tfidf::calculate(const Sentence& sentence, TextDocument& text) const {
//     return (double)(sentence.getWords()[0]->getDF()) 
//     / (double)(text.getTotalWordCount());
// }