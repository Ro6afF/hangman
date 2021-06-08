#include "Hangman.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    srand(time(0));
    Hangman::run(std::cin, std::cout);

    // User::signUp("banan", "banan", "banan");
    // User::signUp("kartof", "kartof", "kartof");
    // User::signUp("chushka", "chushka", "chushka");

    // WordBank::addWord("banan");
    // WordBank::addWord("kartof");
    // WordBank::addWord("chushka");

    // User::signIn("banan", "banan");

    // Game g;
    // char c;
    // do {
    //     std::cout << g;
    //     std::cin >> c;
    //     g.guess(c);
    // } while (!g.isWon());

    // User::signIn("kartof", "kartof");
    // g = Game();
    // do {
    //     std::cout << g;
    //     std::cin >> c;
    //     g.guess(c);
    // } while (!g.isWon());

    // for (auto &x : User::getStanding()) {
    //     std::cout << x.second << " " << x.first << std::endl;
    // }
}