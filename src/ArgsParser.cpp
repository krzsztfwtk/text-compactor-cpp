#include "ArgsParser.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <sstream>

ArgsParser::ArgsParser(int argc, char** argv)
{
    this->argc_=argc;
    this->argv_=argv;
    loadArgs();
    loadConfig();
}

ArgsParser::~ArgsParser() { ; }

void ArgsParser::loadArgs()
{
    for (int i = 1; i < argc_; i++) 
    {
        const std::string arg = argv_[i];

        if (arg == "-i" && i + 1 < argc_) 
        {
            input_filename_ = argv_[++i];
        } else if (arg == "-o" && i + 1 < argc_) 
        {
            output_filename_ = argv_[++i];
        } else if (arg == "-c" && i + 1 < argc_) 
        {
            config_filename_ = argv_[++i];
        } else if (arg == "-h") 
        {
            help_ = true;
        } else if (arg == "--help") 
        {
            help_ = true;
        } else if (arg == "-v") 
        {
            verbose_ = true;
        } else if (arg == "--verbose") 
        {
            verbose_ = true;
        }
    }
}

void ArgsParser::loadConfig()
{
    std::ifstream config_file(config_filename_);
    std::string line;

    if(isVerbose())
    {
        std::cout << "loading config:" << config_filename_;
    }

    while (std::getline(config_file, line)) 
    {
        // Ignore comments and blank lines
        if (line.empty() || line[0] == '#') 
        {
            continue;
        }

        std::stringstream ss(line);
        std::string key, value;
        if (std::getline(ss, key, '=') && ss >> value) 
        {
            if (key == "wordlist")
            {
                int wordlist_number = std::stoi(value);

                for (int i = 0; i < wordlist_number; i++)
                {
                    std::string wordlist_filename;
                    ss >> wordlist_filename;
                    std::string weight_str;
                    ss >> weight_str;
                    int weight = std::stoi(weight_str);

                    wordlist_filenames_with_weights_.
                    push_back({wordlist_filename, weight});
                }
            } else if (key == "capitalNamesBoost")
            {
                capital_names_boost_ = std::stoi(value);
            } else if (key == "minTfidf")
            {
                minimum_tfidf_ = std::stoi(value);
            } else if (key == "taggs")
            {
                taggs_number_ = std::stoi(value);
            } else if (key == "stopWordsList")
            {
                stop_words_filename_ = value;
            }
        }
    }
}


std::string ArgsParser::getInputFilename() const 
{
    return input_filename_;
}

std::string ArgsParser::getOutputFilename() const 
{
    return output_filename_;
}

std::string ArgsParser::getConfigFilename() const 
{
    return config_filename_;
}

bool ArgsParser::isHelp() const
{
    return help_;
}

bool ArgsParser::isVerbose() const
{
    return verbose_;
}

std::vector<std::pair<std::string, int>> ArgsParser::getWordlistFilenames() const
{
    return wordlist_filenames_with_weights_;
}

std::string ArgsParser::getStopWordsFilename() const
{
    return stop_words_filename_;
}

int ArgsParser::getCapitalNamesBoost() const
{
    return capital_names_boost_;
}

unsigned int ArgsParser::getMinimumTFIDF() const
{
    return minimum_tfidf_;
}


unsigned int ArgsParser::getNumberOfTags() const
{
    return taggs_number_;
}
