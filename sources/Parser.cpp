#include "Parser.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <sstream>

Parser::Parser(int argc, char** argv)
{
    this->argc_=argc;
    this->argv_=argv;
    loadArgs();
    
    std::string config_file_extension = 
    config_filename_.substr(config_filename_.find_last_of(".") + 1);

    if (help_)
    {
        printHelp();
        return;
    }

    if (config_file_extension == "json") {
        // loadJsonConfig();
        ;
    } else if (config_file_extension == "ini") {
        loadIniConfig();
    } else {
        std::cout << "\nERROR: Config file format not recognized" << std::endl
        << "Use .json or .ini format\n\n";
        printUsage();
    }
}

Parser::~Parser() { ; }

void Parser::loadArgs()
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

void Parser::loadIniConfig()
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
        if (line.empty() || line[0] == '#' || line[0] == ';') 
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
            } else if (key == "tags")
            {
                tags_number_ = std::stoi(value);
            } else if (key == "stopWordsList")
            {
                stop_words_filename_ = value;
            }
        }
    }
}

void Parser::loadJsonConfig()
{
    ;
}

std::string Parser::getInputFilename() const 
{
    return input_filename_;
}

std::string Parser::getOutputFilename() const 
{
    return output_filename_;
}

std::string Parser::getConfigFilename() const 
{
    return config_filename_;
}

bool Parser::isHelp() const
{
    return help_;
}

bool Parser::isVerbose() const
{
    return verbose_;
}

std::vector<std::pair<std::string, int>> Parser::getWordlistFilenames() const
{
    return wordlist_filenames_with_weights_;
}

std::string Parser::getStopWordsFilename() const
{
    return stop_words_filename_;
}

int Parser::getCapitalNamesBoost() const
{
    return capital_names_boost_;
}

unsigned int Parser::getMinimumTFIDF() const
{
    return minimum_tfidf_;
}


unsigned int Parser::getNumberOfTags() const
{
    return tags_number_;
}

void Parser::printUsage() const
{
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

void Parser::printHelp() const
{
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
    -minTfidf
    -tags

    read README.md for more info


    General options:
    -h, --help       Show help.
    -v, --verbose    Give more output.


    Example usage:
    text_compactor text.txt -o out.txt -c config.json)";


    std::cout << help_text << std::endl << std::endl;
}