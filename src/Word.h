#pragma once

#include <string>

class Word {
public:
    Word(unsigned int df);
    ~Word();
    std::string word_str_;
    unsigned int df_;
    double idf_;
    unsigned int tf;
    unsigned int tf_idf;
    // bool is_stop_word_;
    Word* lemmatization_;
};