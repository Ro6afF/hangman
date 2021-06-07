#include "User.hpp"
#include "WordBank.hpp"

#include <iostream>

int main() {
    User::signUp("asdfg", "asdf", "asd");
    std::cout << User::getUser() << std::endl;
    User::signIn("asdfg", "asd");
    std::cout << User::getUser() << std::endl;

    WordBank::addWord("banan");
    WordBank::addWord("portokal");
    WordBank::addWord("banan");
}