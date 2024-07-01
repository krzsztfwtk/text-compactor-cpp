#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <cctype>

const std::string manual =
"Incorrect use of the program.\n\n"
"-i input file\n"
"-o output file\n"

"example: text-to-wordlist-with-frequency -i \"book.txt\" -o \"wordcount.txt\"\n";


void fileToMap(std::ifstream& input_file, std::unordered_map<std::string, unsigned int>& wordlist) 
{
	std::string line, word;

	input_file.clear();
	input_file.seekg(0, std::ios::beg);

	while (std::getline(input_file, line)) 
	{
		// Convert all non-alpha characters to spaces and convert all alpha characters to lowercase
		std::transform(line.begin(), line.end(), line.begin(), [](char c)  -> char
		{
			if ((int)c < 1)
			{
				return ' ';
			}
			else if (std::isalpha(c)) {
				return std::tolower(c);
			}
			else {
				return ' ';
			}
		});

		std::stringstream ss(line);

		while (ss >> word) 
		{
			wordlist[word]++;
		}
	}
}

void mapToFile(std::ofstream& output_file, std::unordered_map<std::string, unsigned int>& wordlist) 
{
    for (const auto& pair : wordlist) 
    {
        output_file << pair.first << "\t" << pair.second << std::endl;
    }
}

int main(int n, char* argv[])
{
    std::string input_filename;
    std::string output_filename;
    std::string arg;

	for (int i = 1; i < n - 1; i++)
	{
		arg = argv[i];

		if (arg == "-i")
		{
			input_filename = argv[i + 1];
		}

		else if (arg == "-o")
		{
			output_filename = argv[i + 1];
		}
    }


    std::ifstream input_file(input_filename);
    std::ofstream output_file(output_filename);

	if (!input_file)
	{
		std::cout << "ERROR: There is no file: " << input_filename << std::endl;
		std::cout << manual;
		return 0;
	}

	if (!output_file)
	{
		std::cout << "ERROR: There is no file: " << output_filename << std::endl;
		std::cout << manual;
		return 0;
	}

    std::unordered_map<std::string, unsigned int> wordlist;

    fileToMap(input_file, wordlist);
    mapToFile(output_file, wordlist);
}