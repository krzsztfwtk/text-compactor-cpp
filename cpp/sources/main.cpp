#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "BM25.h"
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

  std::unique_ptr<Query> pQuery = nullptr;
  if (!arguments.getQueryFilename().empty()) {
    pQuery = std::make_unique<Query>(arguments.getQueryFilename(),
                                     arguments.getQueryBoostFactor());
  }

  double selectivity_ratio = arguments.getSelectivityRatio();
  std::string measure_type = arguments.getMeasure();

  if (measure_type == "pseudotfidf") {
    if (pQuery) {
      pMeasure = std::make_shared<PseudoTfidf>(wordlist, pQuery.get());
    } else {
      pMeasure = std::make_shared<PseudoTfidf>(wordlist);
    }
  } else if (measure_type == "bm25") {
    if (pQuery) {
      pMeasure = std::make_shared<BM25>(wordlist, pQuery.get());
    } else {
      pMeasure = std::make_shared<BM25>(wordlist);
    }
  } else {
    if (pQuery) {
      pMeasure = std::make_shared<Tfidf>(wordlist, pQuery.get());
    } else {
      pMeasure = std::make_shared<Tfidf>(wordlist);
    }
  }

  std::ofstream output_file(arguments.getOutputFilename());

  unsigned int length_before = text.getLength();
  std::string compacted_text;

  compacted_text = compact(text, pMeasure, selectivity_ratio,
                           arguments.getCapitalNamesBoost());

  unsigned int length_after = compacted_text.length();

  if (output_file) {
    saveTags(output_file, arguments.getNumberOfTags(), text, pMeasure);
    output_file << compacted_text << "\n\nCompacted from " << length_before
                << " to " << length_after << " chars.\n\n";
  } else {
    std::cout << compacted_text << "\n\nCompacted from " << length_before
              << " to " << length_after << " chars.\n\n";
  }
  return 0;
}
