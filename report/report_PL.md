# Sprawozdanie Text Compactor c++

## Instrukcja

Instrukcja jak używać programu znajduje się w pliku `README.md`, oraz folderze `help/`.  
Program wyświetla też krótką instrukcję, kiedy jest uruchomiony z niepoprawnymi argumentami.

## Interfejs

Program używa interfejsu konsolowego. Pracuje na argumentach otrzymanych w wierszu poleceń oraz pliku konfiguracyjnym w standardzie `.ini` lub `.json` - wedle wyboru użytkownika. Rodzaj pliku konfiguracyjnego jest wykryty automatycznie i plik jest odpowiednio obsługiwany przez klasę `Parser`. Program z założenia przyjmuje dane z plików i wynik swojego działania też zapisuje w plikach, ale jeżeli użytkownik nie określi pliku wyjściowego, streszczony tekst zostanie wypisany w konsoli.

## Styl

Styl kodu jest zgodny z **Google C++ Style Guide**. **Cpplint** pozwala sprawdzić poprawność stylu. Aby zapewnić kompatybilność ze standardem, wykorzystałem **Clang-format**.

```bash
cpplint sources/*

clang-format -i sources/*
```

## Środowisko deweloperskie

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

## Struktura plików

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

Program do rysowania struktury plików: **tree**

```bash
tree
```

## Stworzenie wzorca językowego

Aby użyć pogramu potrzebowałem dużej bazy tekstów z języka, który ma być obsługiwany.  
Użyłem:  
do j. angielskiego - **Encyklopedia Britannica**  
do j. polskiego - internetowy zbiór książek  
lista stop words - [Perseus Collections](www.perseus.tufts.edu/hopper/stopwords)

Do stworzenia słownika ze zbiorów wykorzystałem własny program w c++ oraz krótki skrypt w **python-ie** wykorzystujący bibliotekę **SpaCy** do lematyzacji. Oba pomocnicze programy znajdują się w folderze `tools/`.

Pojawił się też ciekawy problem: podzielenie słów między liniami, w plikach `.txt` **Encyklopedia Britannica**. Unimożliwiało to poprawne odczynie słów do stworzenia słownika. Problem rozwiązałem pisząc prosty skrypt w **python-ie**, który koryguje te słowa, w taki sposób:

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

Skrypt umieszczony jest również w `tools/`.

Inny problem zaistniał przy pobieraniu książek w formacie `.txt` ze zbioru intenetowego. Zbiór nie udostępniał możliwości pobrania wszystkich książek na raz automatycznie, zatem musiałem wydobyć ze strony linki do książek, używając skryptu w **python-ie**. Do pobrania plików użyłem programu `wget`, a do ich książek `cat`:

```bash
wget -i links.txt

cat *.txt > merged.txt
```

## Struktura dynamiczna

Samodzielnie zaimplementowałem **listę jednokierunkową** przechowującą wkaźniki do obiektów klasy `Word`. Wskaźnik do pierwszego elementu listy zawiera klasa `Sentence`, a sama lista oparta jest na klasie `SentenceElement`, która ma 2 pola prywatne:  

1. Wskaźnik do obiektu klasy `Word`
2. Wskaźnik na następny element klasy `SentenceElement`

## Czego się nauczyłem

- **Obiektowość** w **C++**
- organizowanie pracy, struktura plików, **make**, testy
- podstawy **NLP**
- obsługa plików konfiguracyjnych w formacie `.ini` oraz `.json`
- **Make** > **CMake**
- zastosowanie struktur danych, których wcześniej nie używałem:  
`std::unordered_set<std::string>`  
`std::set<std::pair<double, Word *>, std::greater<>>`
- zastosowanie **inteligentnych wskaźników**

## Optymalizacja

Operacja dominująca algorytmu to wyszukiwanie słowa w słowniku. Dzięki zastosowaniu `std::unordered_map` czas wyszukiwania jest stały niezależnie od ilości danych, dzięki czemu program wykonuje się szybko. Podczas pisania programu starałem się przestrzegać zasady zerowego narzutu, czyli chciałem napisać taki kod, którego użytkownik nie mógłby już poprawić.

## Refleksje na temat tworzenia projektu

Na wstępie stworzyłem prosty program streszczający tekst używając prostego algorytmu opartego na **TF-IDF**. Pomimo, że działał sprawnie, rozszerzenie go o nowe funkcjonalności okazało się bardzo trudne i bardziej opłacało się napisać program od nowa.

Zrozumiałem, że wstępne zapoznanie się z teoretycznym opisem algorytmów jest kluczowe do zaplanowania pracy. Dokształciłem się na temat **NLP** i czytając książkowe opisy algorytmów, myślałem, jak można użyć mechanizmów abstraksji C++, takich jak klasy, dziedziczenie, polimorfizm, żeby zapisać te algorytmy w kodzie tak samo jak opisywane są w źródłach akademickich. Również postanowiłem napisać instrukcję do programu, jeszcze zanim zacząłem go pisać na nowo.

Pisanie instrukcji dla użytkownika przed rozpoczęciem kodowania okazało się wartościowym podejściem. Pojawiły się przy tym kolejne pomysły, które łatwiej było wdrożyć na wczesnym etapie tworzenia programu.

Napisanie kodu od nowa pozwoliło mi na stworzenie bardziej skalowalnej i elastycznej struktury. W rezultacie, chociaż program nie wykazywał znacząco więcej funkcji, jego potencjał do rozwoju znacznie wzrósł.

Z drugiej strony, warto podkreślić zalety szybkiego rozpoczęcia kodowania, ponieważ umożliwia to rozpoznanie potencjalnych problemów i pomysłów na dalszy rozwój. Nadmierny perfekcjonizm w planowaniu może opóźniać proces, a niektóre problemy i wyzwania są zauważalne tylko podczas praktycznej implementacji. Należy znaleźć balans między planowaniem, a pisaniem kodu.

## Przydatne źródła

- wikipedia
- Stuart Russell, Peter Norvig - Artificial Intelligence. A Modern Approach
- [Machine learning audio course](www.ocdevel.com/mlg)

## Możliwe sposoby rozwoju projektu

- **wyrazy wielowyrazowe**
- **BM25**
- **więcej, dużo więcej testów**
- **wielowątkość, korutyny**
- Capital names boost
- obsługa polskich znaków
- Cosinus similarity
- Summarization based on query (?)
- operator rzutowania
- page rank clustering
- przeprowadzić badanie i porównać program z innymi programami np. modelami transformers na losowej grupie osób, losowe wyrzucanie zdań jako próba kontrolna
