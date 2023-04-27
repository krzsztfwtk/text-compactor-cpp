#pragma once

#include <string>
#include <utility>
#include <vector>

class Parser {
 public:
  Parser(int argc, char** argv);
  ~Parser();

  std::string getInputFilename() const;
  std::string getOutputFilename() const;
  std::string getConfigFilename() const;
  std::vector<std::pair<std::string, int>> getWordlistFilenames() const;
  std::string getStopWordsFilename() const;
  int getCapitalNamesBoost() const;
  unsigned int getMinimumTFIDF() const;
  unsigned int getNumberOfTags() const;
  bool isHelp() const;
  bool isVerbose() const;

 private:
  int argc_;
  char** argv_;
  void loadArgs();
  void loadIniConfig();
  void loadJsonConfig();

  std::string input_filename_;
  std::string output_filename_;
  std::string config_filename_;
  bool help_ = false;
  bool verbose_ = false;

  std::vector<std::pair<std::string, int>> wordlist_filenames_with_weights_;
  std::string stop_words_filename_ = "";
  int capital_names_boost_ = 0;
  unsigned int minimum_tfidf_ = 500;
  unsigned int tags_number_ = 0;

  std::string help_text_;

  void printUsage() const;
  void printHelp() const;
};
