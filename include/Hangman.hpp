#ifndef __HANGMAN__HPP
#define __HANGMAN__HPP

#include "Game.hpp"
#include <fstream>

class Hangman {
    static std::istream *inp;
    static std::ostream *out;
    static Game *current;

    static void help();
    static void login();
    static void signUp();
    static void addWord();
    static void start();
    static void continueGame();
    static void save();
    static void exit();

  public:
    static void run(std::istream &inp, std::ostream &out);
};

#endif // __HANGMAN__HPP