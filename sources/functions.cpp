#include "functions.h"

double calculate(const Sentence &sentence,
                 const std::shared_ptr<Measure> measure, TextDocument &text) {
  double sum = 0;
  int words_number = 0;

  SentenceElement *words_it = sentence.getWords().get();

  if (words_it == nullptr) {
    return 0;
  } else {
    while (words_it->getNext() != nullptr) {
      words_it = words_it->getNext();
      sum += measure->calculate(*words_it->getWord(), text);
      words_number++;
    }
  }

  double average = sum / (double)words_number;

  if (words_number < 1) return 0.0;

  return average;
}

std::vector<Word *>
getMostImportantWords(TextDocument &text,
                      const std::shared_ptr<Measure> measure,
                      unsigned int number_of_words) {
  std::set<std::pair<double, Word *>, std::greater<>> words_with_importance;

  for (const Sentence &sentence : text.getSentences()) {
    SentenceElement *current = sentence.getWords().get();

    while (current) {
      Word *p_word = current->getWord();
      if (p_word) {
        double importance = measure->calculate(*p_word, text);
        words_with_importance.insert({importance, p_word});
      }
      current = current->getNext();
    }
  }

  std::vector<Word *> most_important_words;

  for (auto it = words_with_importance.begin();
       it != words_with_importance.end() &&
       most_important_words.size() < number_of_words;
       ++it) {
    most_important_words.push_back(it->second);
  }

  return most_important_words;
}

void saveTags(std::ofstream &output_file, const unsigned int number_of_tags,
              TextDocument &text, const std::shared_ptr<Measure> measure) {
  if (number_of_tags > 0) {
    std::vector<Word *> tags =
        getMostImportantWords(text, measure, number_of_tags);

    output_file << "\n\n";

    for (Word *pWord : tags) {
      output_file << " #" << *pWord;
    }

    output_file << "\n\n";
  }
}

std::string compact(TextDocument &text, const std::shared_ptr<Measure> measure) {
  std::string compacted_text;

  double sum_of_importance = 0;

  std::list<Sentence> sentences = text.getSentences(); 

  for (Sentence& sentence : sentences) {
    double importance = calculate(sentence, measure, text);
    sentence.importance = importance; 
    sum_of_importance += importance;
  }

  double average_importance = sum_of_importance / sentences.size();

  for (auto it = sentences.begin(); it != sentences.end();) {
    if (it->importance > average_importance) {
        compacted_text += it->getText();
    }
    ++it;
  }

  return compacted_text;
}