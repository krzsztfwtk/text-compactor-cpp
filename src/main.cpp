#include <iostream>

#include "ArgsParser.h"

int main(int argc, char** argv)
{
    ArgsParser arguments(argc, argv);

    std::cout << arguments.getMinimumTFIDF();

    return 0;
}