#include "Game.hpp"
#include "User.hpp"
#include "WordBank.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    srand(time(0));

    User::signIn("banan", "banan");

    Game g("banan_519.hang");
    char c;
    do {
        std::cout << g;
        std::cin >> c;
        g.guess(c);
        g.save();
    } while (true);
}