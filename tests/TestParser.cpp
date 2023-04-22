#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../sources/Parser.h"
#include <vector>

/////////////////////////////////////////////////////////////////////
//////////////////////ARGS ASSIGNMENT////////////////////////////////
/////////////////////////////////////////////////////////////////////

//basic
TEST_CASE("(1)ArgsParser initializes member variables correctly [basic]") {
    int argc = 7;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt",
    (char*)"-c", (char*)"config_file.ini"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "input_file.txt");
    REQUIRE(parser.getOutputFilename() == "output_file.txt");
    REQUIRE(parser.getConfigFilename() == "config_file.ini");
    REQUIRE(parser.isHelp() == false);
    REQUIRE(parser.isVerbose() == false);
}

//different names
TEST_CASE("(2)ArgsParser initializes member variables correctly [different names]") {
    int argc = 7;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"file.in", (char*)"-o", (char*)"file.out",
    (char*)"-c", (char*)"file.config"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "file.in");
    REQUIRE(parser.getOutputFilename() == "file.out");
    REQUIRE(parser.getConfigFilename() == "file.config");
    REQUIRE(parser.isHelp() == false);
    REQUIRE(parser.isVerbose() == false);
}

//different names and order
TEST_CASE("(3)ArgsParser initializes member variables correctly [different order]") {
    int argc = 7;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"file.in", (char*)"-o", (char*)"file.out",
    (char*)"-c", (char*)"file.config"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "file.in");
    REQUIRE(parser.getOutputFilename() == "file.out");
    REQUIRE(parser.getConfigFilename() == "file.config");
    REQUIRE(parser.isHelp() == false);
    REQUIRE(parser.isVerbose() == false);
}

//different names and order, redundants
TEST_CASE("(4)ArgsParser initializes member variables correctly [redundants]") {
    int argc = 9;
    char* argv[] = {(char*)"program_name", (char*)"-o", 
    (char*)"file.out", (char*)"hello", (char*)"world",
    (char*)"-i", (char*)"file.in",
    (char*)"-c", (char*)"file.config"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "file.in");
    REQUIRE(parser.getOutputFilename() == "file.out");
    REQUIRE(parser.getConfigFilename() == "file.config");
    REQUIRE(parser.isHelp() == false);
    REQUIRE(parser.isVerbose() == false);
}

//duplicates
TEST_CASE("(5)ArgsParser initializes member variables correctly [duplicates]") {
    int argc = 13;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt", 
    (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt", 
    (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt", 
    (char*)"-c", (char*)"config_file.ini"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "input_file.txt");
    REQUIRE(parser.getOutputFilename() == "output_file.txt");
    REQUIRE(parser.getConfigFilename() == "config_file.ini");
    REQUIRE(parser.isHelp() == false);
    REQUIRE(parser.isVerbose() == false);
}

//ends with -i
TEST_CASE("(6)ArgsParser initializes member variables correctly [-i last]") {
    int argc = 11;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt", 
    (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt", 
    (char*)"-c", (char*)"config_file.ini", (char*)"-i"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "input_file.txt");
    REQUIRE(parser.getOutputFilename() == "output_file.txt");
    REQUIRE(parser.getConfigFilename() == "config_file.ini");
    REQUIRE(parser.isHelp() == false);
    REQUIRE(parser.isVerbose() == false);
}

//ends with -o
TEST_CASE("(7)ArgsParser initializes member variables correctly [-o last]") {
    int argc = 11;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt", 
    (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt", 
    (char*)"-c", (char*)"config_file.ini", (char*)"-o"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "input_file.txt");
    REQUIRE(parser.getOutputFilename() == "output_file.txt");
    REQUIRE(parser.getConfigFilename() == "config_file.ini");
    REQUIRE(parser.isHelp() == false);
    REQUIRE(parser.isVerbose() == false);
}

//ends with -c
TEST_CASE("(8)ArgsParser initializes member variables correctly [-c last]") {
    int argc = 11;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt", 
    (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt", 
    (char*)"-c", (char*)"config_file.ini", (char*)"-c"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "input_file.txt");
    REQUIRE(parser.getOutputFilename() == "output_file.txt");
    REQUIRE(parser.getConfigFilename() == "config_file.ini");
    REQUIRE(parser.isHelp() == false);
    REQUIRE(parser.isVerbose() == false);
}

//ends with -z
TEST_CASE("(9)ArgsParser initializes member variables correctly [-z last]") {
    int argc = 11;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt", 
    (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt", 
    (char*)"-c", (char*)"config_file.ini", (char*)"-z"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "input_file.txt");
    REQUIRE(parser.getOutputFilename() == "output_file.txt");
    REQUIRE(parser.getConfigFilename() == "config_file.ini");
    REQUIRE(parser.isHelp() == false);
    REQUIRE(parser.isVerbose() == false);
}

//-h last
TEST_CASE("(10)ArgsParser initializes member variables correctly [-h last]") {
    int argc = 8;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"file.in", (char*)"-o", (char*)"file.out",
    (char*)"-c", (char*)"file.config", (char*)"-h"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "file.in");
    REQUIRE(parser.getOutputFilename() == "file.out");
    REQUIRE(parser.getConfigFilename() == "file.config");
    REQUIRE(parser.isHelp() == true);
    REQUIRE(parser.isVerbose() == false);
}

//-h middle
TEST_CASE("(11)ArgsParser initializes member variables correctly [-h middle]") {
    int argc = 8;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"file.in", (char*)"-o", (char*)"file.out", (char*)"-h",
    (char*)"-c", (char*)"file.config"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "file.in");
    REQUIRE(parser.getOutputFilename() == "file.out");
    REQUIRE(parser.getConfigFilename() == "file.config");
    REQUIRE(parser.isHelp() == true);
    REQUIRE(parser.isVerbose() == false);
}

//--help last
TEST_CASE("(12)ArgsParser initializes member variables correctly [--help last]") {
    int argc = 8;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"file.in", (char*)"-o", (char*)"file.out",
    (char*)"-c", (char*)"file.config", (char*)"--help"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "file.in");
    REQUIRE(parser.getOutputFilename() == "file.out");
    REQUIRE(parser.getConfigFilename() == "file.config");
    REQUIRE(parser.isHelp() == true);
    REQUIRE(parser.isVerbose() == false);
}

//--help middle
TEST_CASE("(13)ArgsParser initializes member variables correctly [--help middle]") {
    int argc = 8;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"file.in", (char*)"-o", (char*)"file.out", (char*)"--help",
    (char*)"-c", (char*)"file.config"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "file.in");
    REQUIRE(parser.getOutputFilename() == "file.out");
    REQUIRE(parser.getConfigFilename() == "file.config");
    REQUIRE(parser.isHelp() == true);
    REQUIRE(parser.isVerbose() == false);
}

//-v last
TEST_CASE("(14)ArgsParser initializes member variables correctly [-v last]") {
    int argc = 8;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"file.in", (char*)"-o", (char*)"file.out",
    (char*)"-c", (char*)"file.config", (char*)"-v"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "file.in");
    REQUIRE(parser.getOutputFilename() == "file.out");
    REQUIRE(parser.getConfigFilename() == "file.config");
    REQUIRE(parser.isHelp() == false);
    REQUIRE(parser.isVerbose() == true);
}

//-v middle
TEST_CASE("(15)ArgsParser initializes member variables correctly [-v middle]") {
    int argc = 8;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"file.in", (char*)"-o", (char*)"file.out", (char*)"-v",
    (char*)"-c", (char*)"file.config"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "file.in");
    REQUIRE(parser.getOutputFilename() == "file.out");
    REQUIRE(parser.getConfigFilename() == "file.config");
    REQUIRE(parser.isHelp() == false);
    REQUIRE(parser.isVerbose() == true);
}

//--verbose last
TEST_CASE("(16)ArgsParser initializes member variables correctly [--verbose last]") {
    int argc = 8;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"file.in", (char*)"-o", (char*)"file.out",
    (char*)"-c", (char*)"file.config", (char*)"--verbose"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "file.in");
    REQUIRE(parser.getOutputFilename() == "file.out");
    REQUIRE(parser.getConfigFilename() == "file.config");
    REQUIRE(parser.isHelp() == false);
    REQUIRE(parser.isVerbose() == true);
}

//--verbose and --help
TEST_CASE("(17)ArgsParser initializes member variables correctly [---verbose and --help]") {
    int argc = 9;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"file.in", (char*)"-o", (char*)"file.out", (char*)"--verbose",
    (char*)"-c", (char*)"file.config", (char*)"--help"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "file.in");
    REQUIRE(parser.getOutputFilename() == "file.out");
    REQUIRE(parser.getConfigFilename() == "file.config");
    REQUIRE(parser.isHelp() == true);
    REQUIRE(parser.isVerbose() == true);
}

//--v and --h
TEST_CASE("(18)ArgsParser initializes member variables correctly [--v and --h]") {
    int argc = 9;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"file.in", (char*)"-o", (char*)"file.out", (char*)"-h",
    (char*)"-c", (char*)"file.config", (char*)"-v"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "file.in");
    REQUIRE(parser.getOutputFilename() == "file.out");
    REQUIRE(parser.getConfigFilename() == "file.config");
    REQUIRE(parser.isHelp() == true);
    REQUIRE(parser.isVerbose() == true);
}

/////////////////////////////////////////////////////////////////////
//////////////////////CONFIG ASSIGNMENT//////////////////////////////
/////////////////////////////////////////////////////////////////////

TEST_CASE("(1)ArgsParser loads config correctly .ini [evrything specified]") {
    int argc = 8;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt",
    (char*)"-c", (char*)"test_input_files/test_config_1.ini", (char*)"-v"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "input_file.txt");
    REQUIRE(parser.getOutputFilename() == "output_file.txt");
    REQUIRE(parser.getConfigFilename() == "test_input_files/test_config_1.ini");
    REQUIRE(parser.isHelp() == false);
    REQUIRE(parser.isVerbose() == true);

    REQUIRE(parser.getWordlistFilenames()[0].first == "file_0");
    REQUIRE(parser.getWordlistFilenames()[0].second == 0);
    REQUIRE(parser.getWordlistFilenames()[1].first == "file_1");
    REQUIRE(parser.getWordlistFilenames()[1].second == 1);
    REQUIRE(parser.getWordlistFilenames()[2].first == "file_2");
    REQUIRE(parser.getWordlistFilenames()[2].second == 2);

    REQUIRE(parser.getCapitalNamesBoost() == 1);
    REQUIRE(parser.getMinimumTFIDF() == 600);
    REQUIRE(parser.getNumberOfTags() == 5);
    REQUIRE(parser.getStopWordsFilename() == "stop_words.txt");
}

TEST_CASE("(2)ArgsParser loads config correctly .ini [defaults]") {
    int argc = 8;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt",
    (char*)"-c", (char*)"test_input_files/test_config_2.ini", (char*)"-v"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "input_file.txt");
    REQUIRE(parser.getOutputFilename() == "output_file.txt");
    REQUIRE(parser.getConfigFilename() == "test_input_files/test_config_2.ini");
    REQUIRE(parser.isHelp() == false);
    REQUIRE(parser.isVerbose() == true);

    REQUIRE(parser.getWordlistFilenames()[0].first == "file_0");
    REQUIRE(parser.getWordlistFilenames()[0].second == 0);
    REQUIRE(parser.getWordlistFilenames()[1].first == "file_1");
    REQUIRE(parser.getWordlistFilenames()[1].second == 1);
    REQUIRE(parser.getWordlistFilenames()[2].first == "file_2");
    REQUIRE(parser.getWordlistFilenames()[2].second == 2);

    REQUIRE(parser.getCapitalNamesBoost() == 0);
    REQUIRE(parser.getMinimumTFIDF() == 500);
    REQUIRE(parser.getNumberOfTags() == 0);
    REQUIRE(parser.getStopWordsFilename() == "");
}

TEST_CASE("(3)ArgsParser loads config correctly .json [everything specified]") {
    int argc = 8;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt",
    (char*)"-c", (char*)"test_input_files/test_config_1.json", (char*)"-v"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "input_file.txt");
    REQUIRE(parser.getOutputFilename() == "output_file.txt");
    REQUIRE(parser.getConfigFilename() == "test_input_files/test_config_1.json");
    REQUIRE(parser.isHelp() == false);
    REQUIRE(parser.isVerbose() == true);

    REQUIRE(parser.getWordlistFilenames()[0].first == "file_0");
    REQUIRE(parser.getWordlistFilenames()[0].second == 0);
    REQUIRE(parser.getWordlistFilenames()[1].first == "file_1");
    REQUIRE(parser.getWordlistFilenames()[1].second == 1);
    REQUIRE(parser.getWordlistFilenames()[2].first == "file_2");
    REQUIRE(parser.getWordlistFilenames()[2].second == 2);

    REQUIRE(parser.getCapitalNamesBoost() == 1);
    REQUIRE(parser.getMinimumTFIDF() == 600);
    REQUIRE(parser.getNumberOfTags() == 5);
    REQUIRE(parser.getStopWordsFilename() == "stop_words.txt");
}

TEST_CASE("(4)ArgsParser loads config correctly .json [defaults]") {
    int argc = 8;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt",
    (char*)"-c", (char*)"test_input_files/test_config_2.json", (char*)"-v"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "input_file.txt");
    REQUIRE(parser.getOutputFilename() == "output_file.txt");
    REQUIRE(parser.getConfigFilename() == "test_input_files/test_config_2.json");
    REQUIRE(parser.isHelp() == false);
    REQUIRE(parser.isVerbose() == true);

    REQUIRE(parser.getWordlistFilenames()[0].first == "file_0");
    REQUIRE(parser.getWordlistFilenames()[0].second == 0);
    REQUIRE(parser.getWordlistFilenames()[1].first == "file_1");
    REQUIRE(parser.getWordlistFilenames()[1].second == 1);
    REQUIRE(parser.getWordlistFilenames()[2].first == "file_2");
    REQUIRE(parser.getWordlistFilenames()[2].second == 2);

    REQUIRE(parser.getCapitalNamesBoost() == 0);
    REQUIRE(parser.getMinimumTFIDF() == 500);
    REQUIRE(parser.getNumberOfTags() == 0);
    REQUIRE(parser.getStopWordsFilename() == "");
}

TEST_CASE("(5)ArgsParser loads config correctly .json [everything specified, different order]") {
    int argc = 8;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt",
    (char*)"-c", (char*)"test_input_files/test_config_3.json", (char*)"-v"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "input_file.txt");
    REQUIRE(parser.getOutputFilename() == "output_file.txt");
    REQUIRE(parser.getConfigFilename() == "test_input_files/test_config_3.json");
    REQUIRE(parser.isHelp() == false);
    REQUIRE(parser.isVerbose() == true);

    REQUIRE(parser.getWordlistFilenames()[0].first == "file_0");
    REQUIRE(parser.getWordlistFilenames()[0].second == 0);
    REQUIRE(parser.getWordlistFilenames()[1].first == "file_1");
    REQUIRE(parser.getWordlistFilenames()[1].second == 1);
    REQUIRE(parser.getWordlistFilenames()[2].first == "file_2");
    REQUIRE(parser.getWordlistFilenames()[2].second == 2);

    REQUIRE(parser.getCapitalNamesBoost() == 1);
    REQUIRE(parser.getMinimumTFIDF() == 600);
    REQUIRE(parser.getNumberOfTags() == 5);
    REQUIRE(parser.getStopWordsFilename() == "stop_words.txt");
}

TEST_CASE("(6)ArgsParser loads config correctly .json [different worlist filer order]") {
    {
        int argc = 8;
        char* argv[] = {(char*)"program_name", (char*)"-i", 
        (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt",
        (char*)"-c", (char*)"test_input_files/test_config_4.json", (char*)"-v"};
        Parser parser(argc, argv);

        REQUIRE(parser.getInputFilename() == "input_file.txt");
        REQUIRE(parser.getOutputFilename() == "output_file.txt");
        REQUIRE(parser.getConfigFilename() == "test_input_files/test_config_4.json");
        REQUIRE(parser.isHelp() == false);
        REQUIRE(parser.isVerbose() == true);

        REQUIRE(parser.getWordlistFilenames()[0].first == "file_2");
        REQUIRE(parser.getWordlistFilenames()[0].second == 2);

        REQUIRE(parser.getCapitalNamesBoost() == 1);
        REQUIRE(parser.getMinimumTFIDF() == 600);
        REQUIRE(parser.getNumberOfTags() == 5);
        REQUIRE(parser.getStopWordsFilename() == "stop_words.txt");
    }

    {
        int argc = 8;
        char* argv[] = {(char*)"program_name", (char*)"-i", 
        (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt",
        (char*)"-c", (char*)"test_input_files/test_config_5.json", (char*)"-v"};
        Parser parser(argc, argv);

        REQUIRE(parser.getInputFilename() == "input_file.txt");
        REQUIRE(parser.getOutputFilename() == "output_file.txt");
        REQUIRE(parser.getConfigFilename() == "test_input_files/test_config_5.json");
        REQUIRE(parser.isHelp() == false);
        REQUIRE(parser.isVerbose() == true);

        REQUIRE(parser.getWordlistFilenames()[0].first == "file_0");
        REQUIRE(parser.getWordlistFilenames()[0].second == 0);
        REQUIRE(parser.getWordlistFilenames()[1].first == "file_1");
        REQUIRE(parser.getWordlistFilenames()[1].second == 1);
        REQUIRE(parser.getWordlistFilenames()[2].first == "file_2");
        REQUIRE(parser.getWordlistFilenames()[2].second == 2);
        REQUIRE(parser.getWordlistFilenames()[3].first == "file_3");
        REQUIRE(parser.getWordlistFilenames()[3].second == 3);
        REQUIRE(parser.getWordlistFilenames()[4].first == "file_4");
        REQUIRE(parser.getWordlistFilenames()[4].second == 4);
        REQUIRE(parser.getWordlistFilenames()[5].first == "next_file");
        REQUIRE(parser.getWordlistFilenames()[5].second == 137);

        REQUIRE(parser.getCapitalNamesBoost() == 1);
        REQUIRE(parser.getMinimumTFIDF() == 600);
        REQUIRE(parser.getNumberOfTags() == 5);
        REQUIRE(parser.getStopWordsFilename() == "stop_words.txt");
    }

    {
        int argc = 8;
        char* argv[] = {(char*)"program_name", (char*)"-i", 
        (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt",
        (char*)"-c", (char*)"test_input_files/test_config_6.json", (char*)"-v"};
        Parser parser(argc, argv);

        REQUIRE(parser.getInputFilename() == "input_file.txt");
        REQUIRE(parser.getOutputFilename() == "output_file.txt");
        REQUIRE(parser.getConfigFilename() == "test_input_files/test_config_6.json");
        REQUIRE(parser.isHelp() == false);
        REQUIRE(parser.isVerbose() == true);

        REQUIRE(parser.getWordlistFilenames()[0].first == "file_0");
        REQUIRE(parser.getWordlistFilenames()[0].second == 0);
        REQUIRE(parser.getWordlistFilenames()[1].first == "file_1");
        REQUIRE(parser.getWordlistFilenames()[1].second == 1);
        REQUIRE(parser.getWordlistFilenames()[2].first == "file_2");
        REQUIRE(parser.getWordlistFilenames()[2].second == 2);
        REQUIRE(parser.getWordlistFilenames()[3].first == "file_3");
        REQUIRE(parser.getWordlistFilenames()[3].second == 3);
        REQUIRE(parser.getWordlistFilenames()[4].first == "file_4");
        REQUIRE(parser.getWordlistFilenames()[4].second == 4);
        REQUIRE(parser.getWordlistFilenames()[5].first == "next_file");
        REQUIRE(parser.getWordlistFilenames()[5].second == 137);

        REQUIRE(parser.getCapitalNamesBoost() == 1);
        REQUIRE(parser.getMinimumTFIDF() == 600);
        REQUIRE(parser.getNumberOfTags() == 5);
        REQUIRE(parser.getStopWordsFilename() == "stop_words.txt");
    }
}

TEST_CASE("(7)ArgsParser loads config correctly .json [diverent values]") {
    int argc = 8;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt",
    (char*)"-c", (char*)"test_input_files/test_config_7.json", (char*)"-v"};
    Parser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "input_file.txt");
    REQUIRE(parser.getOutputFilename() == "output_file.txt");
    REQUIRE(parser.getConfigFilename() == "test_input_files/test_config_7.json");
    REQUIRE(parser.isHelp() == false);
    REQUIRE(parser.isVerbose() == true);

    REQUIRE(parser.getWordlistFilenames()[0].first == "wikipedia-en.txt");
    REQUIRE(parser.getWordlistFilenames()[0].second == 1);
    REQUIRE(parser.getWordlistFilenames()[1].first == "gutenberg.in");
    REQUIRE(parser.getWordlistFilenames()[1].second == 2);

    REQUIRE(parser.getCapitalNamesBoost() == 7);
    REQUIRE(parser.getMinimumTFIDF() == 1);
    REQUIRE(parser.getNumberOfTags() == 1);
    REQUIRE(parser.getStopWordsFilename() == "words.stop");
}