#include "Hangman.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    srand(time(0));
    Hangman::run(std::cin, std::cout);
}
