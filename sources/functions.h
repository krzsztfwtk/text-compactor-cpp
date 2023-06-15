#include <set>

#include "Measure.h"
#include "Sentence.h"
#include "SentenceElement.h"
#include "TextDocument.h"

double calculate(const Sentence &sentence,
                 const std::shared_ptr<Measure> measure, TextDocument &text);

std::vector<Word *>
getMostImportantWords(TextDocument &text,
                      const std::shared_ptr<Measure> measure,
                      const unsigned int number_of_words);

void saveTags(std::ofstream &output_file, const unsigned int number_of_tags,
              TextDocument &text, const std::shared_ptr<Measure> measure);

std::string compact(TextDocument &text, const std::shared_ptr<Measure> measure);