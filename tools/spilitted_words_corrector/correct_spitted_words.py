# every line like:

# this is example senten-
# ce spilitted beet-
# wen lines

# should be corrected to:

# this is example sentence spilitted beetwen lines

import argparse

def correct_text(file_in, file_out):
    with open(file_in, 'r') as f_in, open(file_out, 'w') as f_out:
        prev_word = ''
        for line in f_in:
            words = line.strip().split()
            if not words:
                continue
            if prev_word:
                words[0] = prev_word + words[0]
                prev_word = ''
            if words[-1].endswith('-') or words[-1].endswith('¬'):
                prev_word = words[-1][:-1]
                words = words[:-1]
            f_out.write(' '.join(words) + '\n')
        if prev_word:
            f_out.write(prev_word)

def main():
    parser = argparse.ArgumentParser(description='Corrects words split between lines in a text file')
    parser.add_argument('file_in', help='Input text file path')
    parser.add_argument('-o', '--file_out', default='output.txt', help='Output text file path')
    args = parser.parse_args()
    correct_text(args.file_in, args.file_out)

if __name__ == '__main__':
    main()