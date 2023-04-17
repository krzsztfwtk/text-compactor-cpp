# Text Compactor C++

Text Compactor C++ is a command line tool that summarizes given text.

By leveraging the zero overhead principle and using lightweight C++ code, you can use text summarization algorithms that are both fast and resource-efficient. This can lead to significant performance improvements in natural language processing applications, enabling them to handle large volumes of text data in real-time with minimal overhead.

## Usage

```bash
text_compactor -i <input_file> -o <output_file> -c <config_file> [options]
```

```text
<input_file>    input file with text to be summarized  
<output_file>   output file with summarized text  
<config_file>   config file in .ini format
```

## General Options

```bash
-h, --help      Show help.  
-v, --verbose   Give more output.
```

## Configuration

To specify the configuration, create a config.ini file with the following parameters:

```ini
# <config_file>
#
# files with wordlist
# n is the number of files 
# w0, w1, ..., wn are the weights of the files
# files should be in format:
# <word> <lemmatized_word> <count>
# example:
# caring care 102
wordlist=n file_0 w0 file_1 w1 ... file_n wn

# boost importance of capital names -100<i<100 [default=0]
capitaNamesBoost=i

# file with separated stop words
# example:
# then that a an has  
#
# not required to specify
stopWordsList=file_with_stop_words

# number of minimum tfidf: higher number the shorter output text will [default=500]
minTfidf=500

# taggs of tags about text to be printed [default=0]
taggs=0
```

Remember about the correct syntax for the configuration file:

```ini
key=value #correct
key = value #incorrect
```

## Example setup

```text
#wordlist.txt

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
#stop_words.txt 

or the by in be and he are with 
is which it to that as of was a
```

```ini
#config.ini

wordlist=1 wordlist.txt
capitaNamesBoost=3
stopWordsList=stop_words.txt
minTfidf=1000
taggs=5
```

```text
#text.txt

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
text_compactor -i text.txt -o summary.out -c config.ini
```

```text
#summary.out

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
