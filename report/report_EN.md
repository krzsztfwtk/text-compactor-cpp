# Text Compactor C++ Report

## Instructions

Instructions on how to use the program can be found in the `README.md` file and the `help/` folder.  
The program also displays a brief instruction when run with incorrect arguments.

## Interface

The program uses a console interface. It operates on command-line arguments and a configuration file in either `.ini` or `.json` format - as chosen by the user. The type of configuration file is automatically detected, and the file is handled accordingly by the `Parser` class. The program is designed to take input from files and save its output in files as well, but if the user does not specify an output file, the summarized text will be printed to the console.

## Style

The code style follows the **Google C++ Style Guide**. **Cpplint** can be used to check the style correctness. To ensure compatibility with the standard, **Clang-format** is used.

```bash
cpplint sources/*

clang-format -i sources/*
```

## Development Environment

- OS: **Ubuntu** 22.04.2 LTS x86_64
- IDE: **Visual Studio Code** 1.79.2
- Building system: **Make**

```bash
make
```

- Unit testing: **Catch2**

```bash
make -C tests
```

- Memory debugging: **Valgrind**

```bash
Valgrind --leak-check=full ./main <options>
```

## File structure

```bash
├── Doxyfile
├── LICENSE
├── README.md
├── TODO.md
├── bin
│   └── main
├── example
│   ├── config.json
│   ├── list_of_wordcount_in_wolnelektury_pseudo_lemmatized.txt
│   ├── list_of_wordcount_with_lemmatized_in_encyclopaedia_britannica.txt
│   ├── more_configs
│   │   ├── config.json
│   │   ├── config3.json
│   │   └── config_test.json
│   ├── resources
│   │   ├── list_of_wordcount_with_lemmatized_in_encyclopaedia_britannica.txt
│   │   ├── output.txt
│   │   ├── stop_words.txt
│   │   ├── text.txt
│   │   ├── wordlist.txt
│   │   └── words.txt
│   ├── stop_words.txt
│   └── text.txt
├── help
│   ├── help.txt
│   ├── how_it_works.md
│   └── usage.txt
├── makefile
├── report
│   ├── class_diagram.png
│   ├── report_EN.md
│   └── report_PL.md
├── sources
│   ├── Dictionary.cpp
│   ├── Dictionary.h
│   ├── Measure.h
│   ├── Parser.cpp
│   ├── Parser.h
│   ├── PseudoTfidf.cpp
│   ├── PseudoTfidf.h
│   ├── Sentence.cpp
│   ├── Sentence.h
│   ├── SentenceElement.cpp
│   ├── SentenceElement.h
│   ├── StopWords.cpp
│   ├── StopWords.h
│   ├── TextDocument.cpp
│   ├── TextDocument.h
│   ├── Tfidf.cpp
│   ├── Tfidf.h
│   ├── Word.cpp
│   ├── Word.h
│   ├── functions.cpp
│   ├── functions.h
│   └── main.cpp
├── tests
│   ├── TestParser.cpp
│   ├── TestStopWords.cpp
│   ├── catch.hpp
│   ├── makefile
│   └── test_input_files
│       ├── test_config_1.ini
│       ├── test_config_1.json
│       ├── test_config_2.ini
│       ├── test_config_2.json
│       ├── test_config_3.json
│       ├── test_config_4.json
│       ├── test_config_5.json
│       ├── test_config_6.json
│       ├── test_config_7.json
│       └── test_stop_words_1.txt
└── tools
    ├── add_lemmatized_wordlist
    │   ├── add_lemmatized_wordlist.py
    │   ├── lemmatize.py
    │   ├── output.txt
    │   └── text.txt
    ├── spilitted_words_corrector
    │   ├── correct_spitted_words.py
    │   ├── output.txt
    │   └── text.txt
    └── text_to_wordlist_with_frequency
        └── main.cpp
```

Program for drawing file structure: **tree**

```bash
tree
```

## Creating a language model

To use the program, I needed a large text corpus in the language to be supported.  
I used:  
for English - **Encyclopedia Britannica**  
for Polish - an online collection of books  
stop words list - [Perseus Collections](www.perseus.tufts.edu/hopper/stopwords)

To create a dictionary from the datasets, I used my own C++ program and a short script in **Python** using the **SpaCy** library for lemmatization. Both auxiliary programs can be found in the `tools/` folder.

There was also an interesting problem: word splitting across lines in the `.txt` files from **Encyclopedia Britannica**. This prevented proper reading of words to create the dictionary. I solved the problem by writing a simple script in **Python** that corrects these words in the following way:

```input
#input
To diffufe the knowledge of Science, is the profefled defign of the fol-
lowing work. What methods, it may be alked, have the compilers em-
ployed
```

```output
#output
To diffufe the knowledge of Science, is the profefled defign of the
following work. What methods, it may be alked, have the compilers
employed
```

The script is also located in `tools/`.

Another problem occurred when downloading books in `.txt` format from the internet collection. The collection did not provide the option to download all books at once automatically, so I had to extract the links to the books from the website using a script in **Python**. I used the `wget` program to download the files and `cat` to merge them into books:

```bash
wget -i links.txt

cat *.txt > merged.txt
```

## Dynamic structure

I implemented a **singly linked list** that stores pointers to objects of the `Word` class. The pointer to the first element of the list is held by the `Sentence` class, and the list itself is based on the `SentenceElement` class, which has 2 private fields:

1. Pointer to an object of the `Word` class
2. Pointer to the next element of the `SentenceElement` class

## What I learned

- Object-oriented programming in C++
- Work organization, file structure, make, testing
- Basics of NLP
- Handling configuration files in `.ini` and `.json` formats
- Make > CMake
- Using data structures I hadn't used before:
- `std::unordered_set<std::string>`
- `std::set<std::pair<double, Word *>, std::greater<>>`
- Using smart pointers

## Optimization

The dominant operation of the algorithm is searching for a word in the dictionary. By using `std::unordered_map`, the search time is constant regardless of the amount of data, resulting in fast program execution. While writing the program, I aimed to follow the zero-overhead principle, meaning I wanted to write code that the user couldn't improve any further.

## Reflections on project development

Initially, I created a simple text summarization program using a basic algorithm based on TF-IDF. The program had only one class. Although it worked efficiently, extending it with new functionalities proved to be very difficult, and it was more cost-effective to rewrite the program from scratch.

I realized that familiarizing myself with the theoretical description of algorithms is crucial for planning the work. I educated myself about NLP and, while reading book descriptions of algorithms, I thought about how to use C++ abstraction mechanisms such as classes, inheritance, and polymorphism to write these algorithms in code in the same way they are described in academic sources. I also decided to write the program's documentation even before starting to rewrite it.

Writing user documentation before starting coding turned out to be a valuable approach. It led to new ideas that were easier to implement at the early stage of program development.

Rewriting the code allowed me to create a more scalable and flexible structure. As a result, although the program did not have significantly more features, its potential for further development increased significantly.

On the other hand, it is worth emphasizing the benefits of starting coding quickly, as it allows for the identification of potential problems and ideas for further improvement. Excessive perfectionism in planning can delay the process, and some problems and challenges are only noticeable during practical implementation. It is important to find a balance between planning and writing code.

## Useful resources

- Wikipedia
- Stuart Russell, Peter Norvig - Artificial Intelligence. A Modern Approach
- [Machine learning audio course](www.ocdevel.com/mlg)

## Possible ways to further develop the project

- **Multi-word expressions**
- **BM25**
- **More, much more tests**
- **Concurrency, coroutines**
- Capital names boost
- Handling Polish characters
- Cosine similarity
- Summarization based on query (?)
- Casting operator
- Page rank clustering
- Conduct a study and compare the program with other programs, e.g., transformer models, on a random group of people, with random sentence removal as a control group
