#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/ArgsParser.h"



TEST_CASE("ArgsParser initializes member variables correctly") {
    int argc = 7;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt", 
    (char*)"-c", (char*)"config_file.ini"};
    ArgsParser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "input_file.txt");
    REQUIRE(parser.getOutputFilename() == "output_file.txt");
    REQUIRE(parser.getConfigFilename() == "config_file.ini");
    REQUIRE(parser.isHelp() == false);
}