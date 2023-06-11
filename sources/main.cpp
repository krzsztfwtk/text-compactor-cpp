#include <iostream>

#include "Dictionary.h"
#include "Parser.h"
#include "Sentence.h"
#include "StopWords.h"
#include "TextDocument.h"
#include "Word.h"
#include "Measure.h"
#include "Tfidf.h"
#include "functions.h"

int main(int argc, char** argv) {
  Parser arguments(argc, argv);

  Dictionary language_model(arguments.getWordlistFilenames());

  StopWords stop_words(arguments.getStopWordsFilename());

  language_model.removeStopWords(stop_words);

  TextDocument text(arguments.getInputFilename(), language_model);

  Tfidf model_tfidf(language_model);

  Sentence first_sentence = text.getSentences().front();
  Sentence last_sentence = text.getSentences().back();

  std::cout << first_sentence << '[' << 
  calculate(first_sentence, model_tfidf, text) <<']';

  std::cout << last_sentence << '[' << 
  calculate(last_sentence, model_tfidf, text) <<']';

  return 0;
}
