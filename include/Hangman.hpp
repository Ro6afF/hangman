#ifndef __HANGMAN__HPP
#define __HANGMAN__HPP

#include <fstream>

class Hangman {
    static std::istream *inp;
    static std::ostream *out;
    
    static void help();
    static void login();
    static void signUp();
    static void addWord();

  public:
    static void run(std::istream &inp, std::ostream &out);
};

#endif // __HANGMAN__HPP