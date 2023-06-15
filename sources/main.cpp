#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Dictionary.h"
#include "Measure.h"
#include "Parser.h"
#include "PseudoTfidf.h"
#include "Sentence.h"
#include "StopWords.h"
#include "TextDocument.h"
#include "Tfidf.h"
#include "Word.h"
#include "functions.h"

int main(int argc, char **argv) {
  Parser arguments(argc, argv);

  Dictionary wordlist(arguments.getWordlistFilenames());

  StopWords stop_words(arguments.getStopWordsFilename());

  wordlist.removeStopWords(stop_words);

  TextDocument text(arguments.getInputFilename(), wordlist);

  std::shared_ptr<Measure> pMeasure;

  if (arguments.isPseudo()) {
    pMeasure = std::make_shared<PseudoTfidf>(wordlist);
  } else {
    pMeasure = std::make_shared<Tfidf>(wordlist);
  }

  std::ofstream output_file(arguments.getOutputFilename());

  saveTags(output_file, arguments.getNumberOfTags(), text, pMeasure);

  std::string compacted_text = compact(text, pMeasure);

  output_file << compacted_text;

  return 0;
}
