#include "functions.h"
#include <mutex>
#include <regex>
#include <set>
#include <thread>
#include <ranges>

double calculate(const Sentence &sentence,
                 const std::shared_ptr<Measure> measure, TextDocument &text) {
  double sum = 0;
  const std::list words = sentence.getWords();
  int words_number = words.size();

  if (words_number < 1) {
    return 0.0;
  }

  for (const auto &word : sentence.getWords()) {
    sum += measure->calculate(*word, text);
  }

  double average = sum / (double)words_number;

  return average;
}

double calculate(const Sentence &sentence,
                 const std::shared_ptr<Measure> measure, TextDocument &text,
                 double capital_names_boost) {
  double sum = 0;
  const std::list words = sentence.getWords();
  int words_number = words.size();

  if (words_number < 1) {
    return 0.0;
  }

  int capitalized_words_count = 0;

  for (const auto &word : words) {
    sum += measure->calculate(*word, text);
  }

  double average = sum / (double)words_number;

  std::regex capital_name_regex("\\b[A-Z][a-z]*\\b");
  std::string sentence_text = sentence.getText();
  std::sregex_iterator words_begin = std::sregex_iterator(
      sentence_text.begin(), sentence_text.end(), capital_name_regex);
  std::sregex_iterator words_end = std::sregex_iterator();

  for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
    capitalized_words_count++;
  }

  if (capitalized_words_count > 0) {
    average *=
        (1 +
         (capital_names_boost * capitalized_words_count /
          words_number)); // Adjust average importance by a weighted percentage
  }

  return average;
}

std::vector<Word *>
getMostImportantWords(TextDocument &text,
                      const std::shared_ptr<Measure> measure,
                      unsigned int number_of_words) {
  std::set<std::pair<double, Word *>, std::greater<>> words_with_importance;
  std::mutex mtx;
  std::vector<std::thread> threads;

  std::list<Sentence> sentences = text.getSentences();
  size_t num_sentences = sentences.size();
  size_t num_threads = std::thread::hardware_concurrency();
  size_t chunk_size = num_sentences / num_threads;

  auto calculate_importance_chunk = [&](auto start_it, auto end_it) {
    std::set<std::pair<double, Word *>, std::greater<>>
        local_words_with_importance;
    for (auto it = start_it; it != end_it; ++it) {
      for (const auto &word : it->getWords()) {
        double importance = measure->calculate(*word, text);
        local_words_with_importance.insert({importance, word});
      }
    }

    std::lock_guard<std::mutex> lock(
        mtx); // will automatically release the lock when it goes out of scope
    words_with_importance.insert(local_words_with_importance.begin(),
                                 local_words_with_importance.end());
  };

  auto it = sentences.begin();
  for (size_t i = 0; i < num_threads; ++i) {
    auto start_it = it;
    std::advance(it, chunk_size);
    auto end_it = (i == num_threads - 1) ? sentences.end() : it;
    threads.emplace_back(calculate_importance_chunk, start_it, end_it);
  }

  for (auto &t : threads) {
    t.join();
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

std::string compact(TextDocument &text, const std::shared_ptr<Measure> measure,
                    double selectivity_ratio, double capital_names_boost) {
  std::string compacted_text;

  double sum_of_importance = 0;

  std::list<Sentence> sentences = text.getSentences();

  if (capital_names_boost != 0) {
    for (Sentence &sentence : sentences) {
      double importance =
          calculate(sentence, measure, text, capital_names_boost);
      sentence.importance = importance;
      sum_of_importance += importance;
    }
  } else {
    for (Sentence &sentence : sentences) {
      double importance = calculate(sentence, measure, text);
      sentence.importance = importance;
      sum_of_importance += importance;
    }
  }
  double average_importance = sum_of_importance / sentences.size();
  double minimum_importance_threshold = average_importance * selectivity_ratio;

  // for (auto it = sentences.begin(); it != sentences.end();) {
  //   if (it->importance > minimum_importance_threshold) {
  //     compacted_text += it->getText();
  //   }
  //   ++it;
  // }

  auto filtered_sentences = sentences
    | std::views::filter([minimum_importance_threshold](const Sentence &s) {
        return s.importance > minimum_importance_threshold;
    })
    | std::views::transform([](const Sentence &s) {
        return s.getText();
    });

  for (const auto &sentence_text : filtered_sentences) {
      compacted_text += sentence_text;
  }

  return compacted_text;
}