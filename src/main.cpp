#include "User.hpp"

#include <iostream>

int main() {
    User::signUp("asdfg", "asdf", "asd");
    std::cout << User::getUser() << std::endl;
    User::signIn("asdfg", "asd");
    std::cout << User::getUser() << std::endl;
}