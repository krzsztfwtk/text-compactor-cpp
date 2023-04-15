#include "ArgsParser.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <unordered_map>

ArgsParser::ArgsParser(int argc, char** argv)
{
    this->argc_=argc;
    this->argv_=argv;
    loadArgs();
    //loadConfig();
}

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
        } else if (arg == "-h" && i + 1 < argc_) 
        {
            help_ = true;
        } else if (arg == "--help" && i + 1 < argc_) 
        {
            help_ = true;
        }
    }
}

void ArgsParser::loadConfig()
{
    std::ifstream config_file(config_filename_);
    std::string line;

    while (std::getline(config_file, line)) 
    {
        // Ignore comments and blank lines
        if (line.empty() || line[0] == '#') 
        {
            continue;
        }

        std::stringstream ss(line);
        std::string key, value;
        if (std::getline(ss, key, '=') && std::getline(ss, value)) 
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
            } else if (key == "capitalBoost")
            {
                capital_boost_ = std::stoi(value);
            } else if (key == "minTfidf")
            {
                minimum_tfidf_ = std::stoi(value);
            } else if (key == "taggs")
            {
                taggs_number_ = std::stoi(value);
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

std::vector<std::pair<std::string, int>> ArgsParser::getWordlistFilenames() const
{
    return wordlist_filenames_with_weights_;
}

bool ArgsParser::isHelp() const
{
    return help_;
}