#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/ArgsParser.h"


//basic
TEST_CASE("(1)ArgsParser initializes member variables correctly [basic]") {
    int argc = 7;
    char* argv[] = {(char*)"program_name", (char*)"-i", 
    (char*)"input_file.txt", (char*)"-o", (char*)"output_file.txt",
    (char*)"-c", (char*)"config_file.ini"};
    ArgsParser parser(argc, argv);

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
    ArgsParser parser(argc, argv);

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
    ArgsParser parser(argc, argv);

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
    ArgsParser parser(argc, argv);

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
    ArgsParser parser(argc, argv);

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
    ArgsParser parser(argc, argv);

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
    ArgsParser parser(argc, argv);

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
    ArgsParser parser(argc, argv);

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
    ArgsParser parser(argc, argv);

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
    ArgsParser parser(argc, argv);

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
    ArgsParser parser(argc, argv);

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
    ArgsParser parser(argc, argv);

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
    ArgsParser parser(argc, argv);

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
    ArgsParser parser(argc, argv);

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
    ArgsParser parser(argc, argv);

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
    ArgsParser parser(argc, argv);

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
    ArgsParser parser(argc, argv);

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
    ArgsParser parser(argc, argv);

    REQUIRE(parser.getInputFilename() == "file.in");
    REQUIRE(parser.getOutputFilename() == "file.out");
    REQUIRE(parser.getConfigFilename() == "file.config");
    REQUIRE(parser.isHelp() == true);
    REQUIRE(parser.isVerbose() == true);
}