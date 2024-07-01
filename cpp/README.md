# Text Compactor C++

Text Compactor C++ is a command line tool that summarizes given text.

By leveraging the zero overhead principle and using lightweight C++ code, you can use text summarization algorithms that are both fast and resource-efficient. This can lead to significant performance improvements in natural language processing applications, enabling them to handle large volumes of text data in real-time with minimal overhead.

## Usage

```bash
text_compactor -i <input_file> -o <output_file> -c <config_file> -q <query_file> [options]
```

```text
<input_file>    input file with text to be summarized  
<output_file>   output file with summarized text  
<config_file>   config file in .json or .ini format
<query_file>    optional argument for semantic search
```

The usage of the program requires the [-c \<config_file>] parameter, while [-i \<input_file>] and [-o \<output_file>] parameters are optional. If you do not specify an input file, the program will prompt you to enter text in the terminal window. If you do not specify an output file, the program will display the result in the terminal window. Parameter [-q <query_file>] is optional. Use only for semantic search.

## General Options

```bash
-h, --help      Show help.  
-v, --verbose   Give more output.
```

## Configuration

To specify the configuration, create a config.ini or config.json file with the following parameters:

```text
wordlist files: files which will be used to calculate term frequency by program.

Required

Files should be in format:
<word> <lemmatized> <number>
example:
caring care 158

you can specify one or more wordlist files
you should also specify their weights
example:
    "wordlist": {
        "file_0": 0, //file_0 will not be taken into account
        "file_1": 1, //
        "file_2": 2  //file_2 is 2 times more important than file_0
    },

you can check where to get such a file in /help
```

```text
capitalNamesBoost: boost importance of capital names.
[default=0]

Not required

is recommended to set value d: -1.00 < d < 1.00
```

```text
stopWordsList: file with separated stop words.

Not required

file should look like:
or the by in be and he are with ...
```

```text
selectivityRatio: how selective should be program while summarizing?
selectivityRatio = 1 means every sentence with importance below average will be ommited.

Value should be an double d: d > 0

Larger the coefficient, the longer the shorter text will be
and more sentences will be deleted.
```

```text
tags: number of tags which will be displayed next to summarized text
[default=0]

Not required

Value should be an integer i: i > 0

tags will be words with highest TF-IDF coefficient in text.
```

```text
measureType: type of measure algorithm to use.
[default=tfidf]

Required

Value should belong to {tfidf, pseudotfidf, bm25}
```

```json
//config.json
{
    "wordlist": {
        "file_0": 0,
        "file_1": 1,
        "file_2": 2
    },
    "capitalNamesBoost": 0.2,
    "stopWordsList": "stop_words_file",
    "selectivityRatio": 1,
    "tags": 5
}
```

```ini
# config.ini

wordlist=file_0 0 file_1 1 file_2 2
capitalNamesBoost=0.2
stopWordsList=file_with_stop_words
selectivityRatio=1
tags=5
```

Remember about the correct syntax for the .ini configuration file:

```ini
key=value #correct
key = value #incorrect
```

## Example setup

```text
//wordlist.txt

years year 102789
made make 224981
air air 102040
parts part 126654
called call 154533
most most 112266
many many 155628
see see 118853
water water 177624
only only 232340
body body 109562
king king 124390
number number 109630
year year 115896
great great 277788
...
```

```text
//stop_words.txt 

or the by in be and he are with 
is which it to that as of was a
```

```json
//config.json

{
  "wordlist": {
    "wordlist.txt": 1,
  },
  "capitalNamesBoost": 0.3,
  "stopWordsList": "stop_words.txt",
  "selectivityRaio": 1,
  "tags": 5
}

```

```text
//text.txt

Because the launch needed a deeper draught than a regular boat, 
it was difficult to land it on the shallow bank of the Ganga. 
The captain finally resorted to the expedient of nnooring it 
to a chain of boats, which he in effect commandeered. 
By the time the launch was moored, more than three-quarters 
of an hour had passed. The crowds at the main bathing areas 
on the Brahmpur side had thinned to almost nothing. 
The news of the disaster had spread swiftly. The bathing 
posts with their colourful signs—parrot, peacock, bear, 
scissors, mountain, trident and so on—were almost deserted. 
A few people, in a restrained, almost fearful way, 
were still dipping themselves in the river and hurrying away. 
```

```bash
#run in command line
text_compactor -i text.txt -o summary.out -c config.json
```

```text
//summary.out

#brahmpur #nnooring #colourful #commandeered #ganga

Because the launch needed a deeper draught than a regular boat,
it was difficult to land it on the shallow bank of the Ganga.
The captain finally resorted to the expedient of nnooring it
to a chain of boats, which he in effect commandeered. The crowds
at the main bathing areas on the Brahmpur side had thinned to
almost nothing. The news of the disaster had spread swiftly.
The bathing posts with their colourful signs—parrot, peacock,
bear, scissors, mountain, trident and so on—were almost deserted.

```
