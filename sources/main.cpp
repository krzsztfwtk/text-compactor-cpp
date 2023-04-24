#include <iostream>

#include "Parser.h"
#include "Word.h"
#include "Dictionary.h"
#include "StopWords.h"
#include "Sentence.h"
#include "TextDocument.h"

int main(int argc, char** argv)
{
    Parser arguments(argc, argv);

    Dictionary language_model
    (arguments.getWordlistFilenames());

    StopWords stop_words(arguments.getStopWordsFilename());

    language_model.removeStopWords(stop_words);

    TextDocument text(arguments.getInputFilename(), language_model);

    return 0;
}