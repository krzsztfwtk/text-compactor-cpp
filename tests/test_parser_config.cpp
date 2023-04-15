#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/ArgsParser.h"
#include <vector>

TEST_CASE("(1)ArgsParser loads config correctly [evrything specified]") {
    int argc = 8;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt",
    (char*)"-c", (char*)"example_config_1.ini", (char*)"-v"};
    ArgsParser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "input_file.txt");
    REQUIRE(parser.getOutputFilename() == "output_file.txt");
    REQUIRE(parser.getConfigFilename() == "example_config_1.ini");
    REQUIRE(parser.isHelp() == false);
    REQUIRE(parser.isVerbose() == true);

    REQUIRE(parser.getWordlistFilenames()[0].first == "file_0");
    REQUIRE(parser.getWordlistFilenames()[0].second == 0);
    REQUIRE(parser.getWordlistFilenames()[1].first == "file_1");
    REQUIRE(parser.getWordlistFilenames()[1].second == 1);
    REQUIRE(parser.getWordlistFilenames()[2].first == "file_2");
    REQUIRE(parser.getWordlistFilenames()[2].second == 2);

    REQUIRE(parser.getCapitalBoost() == 1);
    REQUIRE(parser.getMinimumTFIDF() == 600);
    REQUIRE(parser.getNumberOfTags() == 5);
}

TEST_CASE("(2)ArgsParser loads config correctly [defaults]") {
    int argc = 8;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt",
    (char*)"-c", (char*)"example_config_2.ini", (char*)"-v"};
    ArgsParser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "input_file.txt");
    REQUIRE(parser.getOutputFilename() == "output_file.txt");
    REQUIRE(parser.getConfigFilename() == "example_config_2.ini");
    REQUIRE(parser.isHelp() == false);
    REQUIRE(parser.isVerbose() == true);

    REQUIRE(parser.getWordlistFilenames()[0].first == "file_0");
    REQUIRE(parser.getWordlistFilenames()[0].second == 0);
    REQUIRE(parser.getWordlistFilenames()[1].first == "file_1");
    REQUIRE(parser.getWordlistFilenames()[1].second == 1);
    REQUIRE(parser.getWordlistFilenames()[2].first == "file_2");
    REQUIRE(parser.getWordlistFilenames()[2].second == 2);

    REQUIRE(parser.getCapitalBoost() == 0);
    REQUIRE(parser.getMinimumTFIDF() == 500);
    REQUIRE(parser.getNumberOfTags() == 0);
}