#include "functions.h"

double calculate(const Sentence &sentence, const Measure &measure,
                 TextDocument &text) {
  double sum = 0;
  int words_number = 0;

  SentenceElement *words_it = sentence.getWords().get();

  if (words_it == nullptr) {
    return 0;
  } else {
    while (words_it->getNext() != nullptr) {
      words_it = words_it->getNext();
      sum += measure.calculate(*words_it->getWord(), text);
      words_number++;
    }
  }

  double average = sum / (double)words_number;

  return average;
}