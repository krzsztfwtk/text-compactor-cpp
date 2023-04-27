#pragma once

#include <string>

class Word {
 public:
  Word() = default;
  Word(const std::string& name, const std::string& lemmatization,
       unsigned int idf);

  std::string getName() const;
  std::string getLemmatization() const;
  unsigned int getIDF() const;

  void setName(const std::string& name);
  void setLemmatization(const std::string& lemmatization);
  void setIDF(unsigned int idf);
  void addIdf(unsigned int value);

 private:
  std::string name_;
  std::string lemmatization_;
  unsigned int idf_;
};
