#ifndef __WORD_BANK_HPP
#define __WORD_BANK_HPP

#include <string>

class WordBank {
  private:
    static int wordCount(std::ifstream &db);

  public:
    static void addWord(const char *word);
    static std::string getRandomWord();
};

#endif // __WORD_BANK_HPP