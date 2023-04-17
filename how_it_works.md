# How does it work?

Explanation for newbies

## Let's understand 3 concepts

---
Stop words:
| Stop Words | Non-Stop Words |
|------------|----------------|
| the        | apple          |
| and        | book           |
| to         | car            |
| of         | movie          |
| a          | computer       |
| in         | music          |
---
Lemmatization:

| Word | Lemmatized Word |
|-----------|----------------|
| parts     | part           |
| called    | call           |
| found     | find           |
| years     | year           |
| made      | make           |
| was       | be             |
| being     | be             |
| them      | they           |

---

TF-IDF coefficient:

$$
\operatorname{tf-idf}(t, d) = \operatorname{tf}(t, d) \times \operatorname{idf}(t)
$$

where $\operatorname{tf}(t, d)$ is the term frequency of term $t$ in document $d$, and $\operatorname{idf}(t)$ is the inverse document frequency of term $t$.

**Simplified**: Important words are those that occur frequently in the analyzed text, but rarely in the language of the text.

---

## To build a simple text summarizer, follow these steps

1. Collect the input text that you want to summarize
2. Remove stop words
3. Apply stemming or lemmatization
4. Calculate TF-IDF
5. Select the top-ranked sentences based on their importance
score (TF-IDF)
6. Correct grammar, restore stop words
