#include "Parser.h"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;

Parser::Parser(int argc, char **argv) {
  this->argc_ = argc;
  this->argv_ = argv;
  loadArgs();

  if (help_) {
    printHelp();
    return;
  }

  std::string config_file_extension =
      config_filename_.substr(config_filename_.find_last_of(".") + 1);

  if (config_file_extension == "json") {
    if (fs::exists(config_filename_)) {
      loadJsonConfig();
    } else {
      std::cout << "ERROR: There is no file: " << config_filename_ << std::endl;
      return;
    }
  } else if (config_file_extension == "ini") {
    if (fs::exists(config_filename_)) {
      loadIniConfig();
    } else {
      std::cout << "ERROR: There is no file: " << config_filename_ << std::endl;
      return;
    }
  } else {
    std::cout << "\nERROR: Config file format not recognized" << std::endl
              << "Use .json or .ini format\n\n";
    printUsage();
  }

  if (!fs::exists(input_filename_)) {
    std::cerr << "ERROR: Input file does not exist: " << input_filename_
              << std::endl;
    return;
  }

  for (const auto &[path, weight] : wordlist_filenames_with_weights_) {
    if (!fs::exists(path)) {
      std::cerr << "ERROR: Wordlist file does not exist: " << path << std::endl;
      return;
    }
  }

  if (!stop_words_filename_.empty() && !fs::exists(stop_words_filename_)) {
    std::cerr << "ERROR: Stop words file does not exist: "
              << stop_words_filename_ << std::endl;
    return;
  }
}

Parser::~Parser() { ; }

void Parser::loadArgs() {
  for (int i = 1; i < argc_; i++) {
    const std::string arg = argv_[i];

    if (arg == "-i" && i + 1 < argc_) {
      input_filename_ = argv_[++i];
    } else if (arg == "-o" && i + 1 < argc_) {
      output_filename_ = argv_[++i];
    } else if (arg == "-c" && i + 1 < argc_) {
      config_filename_ = argv_[++i];
    } else if (arg == "-q" && i + 1 < argc_) {
      query_filename_ = argv_[++i];
    } else if (arg == "-h") {
      help_ = true;
    } else if (arg == "--help") {
      help_ = true;
    } else if (arg == "-v") {
      verbose_ = true;
    } else if (arg == "--verbose") {
      verbose_ = true;
    }
  }
}

void Parser::loadIniConfig() {
  std::ifstream config_file(config_filename_);
  std::string line;

  if (isVerbose()) {
    std::cout << "loading config:" << config_filename_ << std::endl;
  }

  while (std::getline(config_file, line)) {
    // Ignore comments and blank lines
    if (line.empty() || line[0] == '#' || line[0] == ';') {
      continue;
    }

    std::stringstream ss(line);
    std::string key, value;
    if (std::getline(ss, key, '=') && ss >> value) {
      if (key == "wordlist") {
        int wordlist_number = std::stoi(value);

        for (int i = 0; i < wordlist_number; i++) {
          std::string wordlist_filename;
          ss >> wordlist_filename;
          std::string weight_str;
          ss >> weight_str;
          int weight = std::stoi(weight_str);

          wordlist_filenames_with_weights_.push_back(
              {wordlist_filename, weight});
        }
      } else if (key == "capitalNamesBoost") {
        capital_names_boost_ = std::stod(value);
      } else if (key == "selectivityRatio") {
        selectivity_ratio_ = std::stod(value);
      } else if (key == "queryBoostFactor") {
        query_boost_factor_ = std::stod(value);
      } else if (key == "tags") {
        tags_number_ = std::stoi(value);
      } else if (key == "stopWordsList") {
        stop_words_filename_ = value;
      } else if (key == "measure") {
        measure_ = value;
      }
    }
  }
}

void Parser::loadJsonConfig() {
  std::ifstream config_file(config_filename_);

  if (isVerbose()) {
    std::cout << "Loading config: " << config_filename_ << std::endl;
  }

  std::string line;
  std::string key, value;

  while (std::getline(config_file, line)) {
    // Remove whitespaces from the line
    line.erase(remove_if(line.begin(), line.end(), isspace), line.end());

    // Ignore comments and empty lines
    if (line.empty() || line[0] == '/' || line[0] == '*') {
      continue;
    }

    // Extract key-value pairs
    size_t colon_pos = line.find(':');
    size_t comma_pos = line.find(',');

    if (colon_pos != std::string::npos) {
      key = line.substr(0, colon_pos);
      value = line.substr(colon_pos + 1, comma_pos - colon_pos - 1);

      // Remove quotes if present
      if (value.front() == '"' && value.back() == '"') {
        value = value.substr(1, value.length() - 2);
      }

      if (key == "\"wordlist\"") {
        wordlist_filenames_with_weights_.clear();

        // Handle the opening brace possibly being on a new line
        bool foundOpeningBrace = false;
        if (line.back() == '{') {
          foundOpeningBrace = true;
        }

        while (std::getline(config_file, line)) {
          line.erase(remove_if(line.begin(), line.end(), isspace), line.end());

          // If we haven't found the opening brace, check this line for it.
          if (!foundOpeningBrace) {
            if (line.front() == '{') {
              foundOpeningBrace = true;
            }
            continue; // Skip to the next line since this doesn't contain
                      // key-value data
          }

          // Once we have the opening brace, we proceed as before
          if (line.empty() || line[0] == '}' || line[0] == ',' ||
              line[0] == '/') {
            if (line[0] == '}') {
              break; // End of the wordlist object
            }
            continue; // Skip comments, empty lines, or trailing commas
          }

          size_t colon_pos = line.find(':');
          size_t comma_pos = line.find(',');

          if (colon_pos != std::string::npos) {
            std::string file_key = line.substr(0, colon_pos);
            int weight = std::stoi(line.substr(
                colon_pos + 1,
                (comma_pos != std::string::npos ? comma_pos : line.length()) -
                    colon_pos - 1));

            wordlist_filenames_with_weights_.push_back(
                {file_key.substr(1, file_key.length() - 2), weight});
          }
        }
      } else if (key == "\"capitalNamesBoost\"") {
        capital_names_boost_ = std::stod(value);
      } else if (key == "\"stopWordsList\"") {
        stop_words_filename_ = value;
      } else if (key == "\"measure\"") {
        measure_ = value;
      } else if (key == "\"selectivityRatio\"") {
        selectivity_ratio_ = std::stod(value);
      } else if (key == "\"queryBoostFactor\"") {
        query_boost_factor_ = std::stod(value);
      } else if (key == "\"tags\"") {
        tags_number_ = std::stoi(value);
      }
    }
  }
}

std::string Parser::getInputFilename() const { return input_filename_; }

std::string Parser::getOutputFilename() const { return output_filename_; }

std::string Parser::getConfigFilename() const { return config_filename_; }

std::string Parser::getQueryFilename() const { return query_filename_; }

bool Parser::isHelp() const { return help_; }

bool Parser::isVerbose() const { return verbose_; }

std::string Parser::getMeasure() const { return measure_; }

std::vector<std::pair<std::string, int>> Parser::getWordlistFilenames() const {
  return wordlist_filenames_with_weights_;
}

std::string Parser::getStopWordsFilename() const {
  return stop_words_filename_;
}

double Parser::getCapitalNamesBoost() const { return capital_names_boost_; }

double Parser::getSelectivityRatio() const { return selectivity_ratio_; }

double Parser::getQueryBoostFactor() const { return query_boost_factor_; }

unsigned int Parser::getNumberOfTags() const { return tags_number_; }

void Parser::printUsage() const {
  std::string usage_text = R"(Summarizes the given text

    Usage:
        text_compactor -i <input_file> -o <output_file> -c <config_file> [options]


    <input_file>	input file with text to be summarized
    <output_file>	output file with summarized text
    <config_file>	config file in .ini format, see help for more details


    General options:
    -h, --help	Show help.
    -v, --verbose	Give more output.)";

  std::cout << usage_text << std::endl << std::endl;
}

void Parser::printHelp() const {
  std::string help_text = R"(Summarizes the given text

    Usage:
            text_compactor -i <input_file> -o <output_file> -c <config_file> [options]


    <input_file>    input file with text to be summarized
    <output_file>    output file with summarized text
    <config_file>    config file in format key=value in each line, use # or ; for comments, lines starting with # will be ignored


    to specify in config.json or config.ini:
    -wordlist
    -capitaNamesBoost
    -stopWordsList
    -selectivityRatio
    -tags

    read README.md for more info


    General options:
    -h, --help       Show help.
    -v, --verbose    Give more output.


    Example usage:
    text_compactor text.txt -o out.txt -c config.json)";

  std::cout << help_text << std::endl << std::endl;
}