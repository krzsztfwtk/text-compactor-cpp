#include <iostream>

#include "Dictionary.h"
#include "Parser.h"
#include "Sentence.h"
#include "StopWords.h"
#include "TextDocument.h"
#include "Word.h"

int main(int argc, char** argv) {
  Parser arguments(argc, argv);

  Dictionary language_model(arguments.getWordlistFilenames());

  StopWords stop_words(arguments.getStopWordsFilename());

  language_model.removeStopWords(stop_words);

  TextDocument text(arguments.getInputFilename(), language_model);

  return 0;
}
