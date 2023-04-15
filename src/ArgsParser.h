#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class ArgsParser {
public:
    ArgsParser(int argc, char** argv);
    bool parseArgs();

    std::string getInputFilename() const;
    std::string getOutputFilename() const;
    std::string getConfigFilename() const;
    std::vector<std::pair<std::string, int>> getWordlistFilenames() const;
    int getCapitalBoost() const;
    unsigned int getMinimumTfidf() const;
    unsigned int getTaggs() const;
    bool isHelp() const;

private:
    int argc_;
    char** argv_;
    void loadArgs();
    void loadConfig();

    std::string input_filename_;
    std::string output_filename_;
    std::string config_filename_;
    bool help_ = false;

    std::vector<std::pair<std::string, int>> wordlist_filenames_with_weights_;
    int capital_boost_ = 0;
    unsigned int minimum_tfidf_ = 500;
    unsigned int taggs_number_ = 0;

    std::string usage_text_;
    std::string help_text_;

    void printUsage() const;
    void printHelp() const;
};
