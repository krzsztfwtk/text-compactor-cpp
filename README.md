# NLP Toolkit

## Usage of the program

NLP Toolkit is a program that provides tools to solve some natural language processing tasks:

- Text summarization - Text Compactor
- Semantic search - Insight Search

The program is cross-platform, meaning it can operate on both Windows and Linux systems.

Before running the program, it's essential to compile the C++ subprogram. If the C++ subprogram is not compiled, the Python WebUI will try to compile it using the `subprocess` library. Nevertheless, it is recommended to compile it previously to avoid errors.

To build a C++ subprogram, go to the `cpp` directory and build it using the Make system.

For Linux users, execute the following command:

```bash
make
```

For Windows users, use the following command, assuming you have MinGW installed:

```bash
mingw64-make
```

or

```bash
mingw32-make
```

To run the program, use the command:

```bash
python webui.py
```

Then, in your browser, go to the address `http://127.0.0.1:5000/` where you will see the user interface for the program. On the home page, you will see a list of all available tools.

### Parameters

Using the interface in the browser, you will need to set the following parameters that affect the result of the program:

- Wordlist
  - Default
  - English
  - Polish
  - Polish-English
- Stop Word List
  - Default
  - English
  - Polish
  - Polish-English
- Capital Names Boost
  - boost importance of capital names.
  - Value should be a float number
  - it is recommended to set values between -1 and 2.
- Selectivity Radio
  - Larger the coefficient, the shorter the summarized text will be
and more sentences will be deleted.
  - it is recommended to set values between 1 and 4.
- Tags Number
  - Number of tags displayed on the result.
- Measure Mode
  - TF-IDF
  - Pseudo TF-IDF (simplified version od TF-IDF)
  - BM25

Select all settings according to your needs then click "Submit" button.

## Project Structure

The `cpp` directory contains a C++ program designed to tackle NLP tasks provided the command-line parameters and configuration file. Layered above this is a web user interface developed in Python using the `flask` module. This interface gathers necessary parameters from the user, after which the Python code generates an appropriate configuration file and executes the C++ program with the relevant parameters usign `subprocess` module. Subsequently, it presents the results to the user.

## Explanation of the Algorithm for Newbies

### Understanding 3 Key Concepts

---

**Stop Words**:
A table illustrating the difference between stop words, which are commonly removed before processing natural language data, and non-stop words, which carry more meaning in text.

| Stop Words | Non-Stop Words |
|------------|----------------|
| the        | apple          |
| and        | book           |
| to         | car            |
| of         | movie          |
| a          | computer       |
| in         | music          |

---

**Lemmatization**:
This table shows examples of words before and after lemmatization, a process that reduces words to their base or dictionary form.

| Word       | Lemmatized Word |
|------------|-----------------|
| parts      | part            |
| called     | call            |
| found      | find            |
| years      | year            |
| made       | make            |
| was        | be              |
| being      | be              |
| them       | they            |

---

**TF-IDF Coefficient**:

The formula for calculating the TF-IDF (Term Frequency-Inverse Document Frequency) coefficient is given by:

*tf-idf(t, d) = tf(t, d) * idf(t)*

where *tf(t, d)* represents the term frequency of term *t* in document *d*, and *idf(t)* signifies the inverse document frequency of term *t*.

**Simplified Explanation**: Words that are deemed important are those that appear frequently in the text being analyzed but are rare in the general language.

---

### Building a Simple Text Summarizer: Steps to Follow

1. Gather the input text you wish to summarize.
2. Eliminate stop words from the text.
3. Apply stemming or lemmatization to condense words to their root forms.
4. Calculate the TF-IDF values for words in the text to evaluate their importance.
5. Select the sentences with the highest importance scores (based on TF-IDF) for inclusion in the summary.
6. Perform grammar corrections and potentially restore some stop words to ensure the summary reads naturally.

## Usage of C++ program

By leveraging the zero overhead principle and using lightweight C++ code, you can use natural language processing algorithms that are both fast and resource-efficient. This can lead to significant performance improvements in natural language processing applications, enabling them to handle large volumes of text data in real-time with minimal overhead.

At the same time, the user-friendly web interface in Python makes the program easy to use. It does not significantly reduce performance, since most of the calculation is not a graphical interface, but an algorithm executed through a C++ program.

For the average user, detailed knowledge of how the C++ program runs is not necessary, but for reference, here is the command-line command to run the program:

```bash
main -i <input_file> -o <output_file> -c <config_file> [options]
```

```text
<input_file>    input file with text to be summarized  
<output_file>   output file with summarized text  
<config_file>   config file in .json or .ini format
```

The usage of the program requires the [-c \<config_file>] parameter, while [-i \<input_file>] and [-o \<output_file>] parameters are optional. If you do not specify an input file, the program will prompt you to enter text in the terminal window. If you do not specify an output file, the program will display the result in the terminal window.

For detailed instructions on creating the configuration file, please refer to the `README.md` file located in the `cpp` directory.
