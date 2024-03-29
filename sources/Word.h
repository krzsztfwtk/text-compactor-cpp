#pragma once

#include <string>

class Word {
public:
  Word() = default;
  Word(const std::string &name, const std::string &lemmatization,
       unsigned int df);

  std::string getName() const;
  std::string getLemmatization() const;
  unsigned int getDF() const;

  void setName(const std::string &name);
  void setLemmatization(const std::string &lemmatization);
  void setDF(unsigned int df);
  void addDF(unsigned int value);
  friend std::ostream &operator<<(std::ostream &os, const Word &word);
  friend std::istream &operator>>(std::istream &is, Word &word);

private:
  std::string name_;
  std::string lemmatization_;
  unsigned int df_;
};
