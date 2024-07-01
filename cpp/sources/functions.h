#include <set>

#include "Measure.h"
#include "Query.h"
#include "Sentence.h"
#include "TextDocument.h"

double calculate(const Sentence &sentence,
                 const std::shared_ptr<Measure> measure, TextDocument &text);

double calculate(const Sentence &sentence,
                 const std::shared_ptr<Measure> measure, TextDocument &text,
                 double capital_names_boost);

std::vector<Word *>
getMostImportantWords(TextDocument &text,
                      const std::shared_ptr<Measure> measure,
                      const unsigned int number_of_words);

void saveTags(std::ofstream &output_file, const unsigned int number_of_tags,
              TextDocument &text, const std::shared_ptr<Measure> measure);

// std::string compact(TextDocument &text, const std::shared_ptr<Measure>
// measure,
//                     double selectivity_ratio = 1.0);

std::string compact(TextDocument &text, const std::shared_ptr<Measure> measure,
                    double selectivity_ratio = 1.0,
                    double capital_names_boost = 0);

// std::string compact(TextDocument &text, const std::shared_ptr<Measure>
// measure,
//                     double selectivity_ratio, double capital_names_boost,
//                     const Query &query);