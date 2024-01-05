import argparse
import spacy

nlp = spacy.load("en_core_web_sm")

def main(input_file, output_file):
    with open(input_file, "r", encoding="utf-8") as f_input, open(output_file, "w", encoding="utf-8") as f_output:
        for line in f_input:
            word, count = line.strip().split()
            lemma = nlp(word)[0].lemma_
            f_output.write(f"{word}\t{lemma}\t{count}\n")

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("input_file", help="path to input file")
    parser.add_argument("-o", "--output_file", default="output.txt", help="path to output file")
    args = parser.parse_args()
    main(args.input_file, args.output_file)

