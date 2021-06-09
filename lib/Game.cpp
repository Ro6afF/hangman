#include "Game.hpp"

#include "User.hpp"
#include "WordBank.hpp"
#include <algorithm>
#include <cstring>
#include <fstream>

Game::Game() {
    if (User::getUser() == nullptr)
        throw std::logic_error("User not logged in!");

    this->word = WordBank::getRandomWord();

    for (int i = 'A'; i <= 'Z'; i++) {
        this->guessed[i - 'A'] = false;
    }
    this->guessed[this->word[0] - 'A'] = true;
    this->won = false;
    this->lost = false;

    this->lives = 6;
}

Game::Game(const char *file) {
    if (User::getUser() == nullptr)
        throw std::logic_error("User not logged in!");

    std::string fileStr(file);
    if (fileStr.find(User::getUser()->getUsername()) == std::string::npos)
        throw std::logic_error("Not your game!");

    std::ifstream game(file);
    game.seekg(0, std::ios::beg);
    game.read(reinterpret_cast<char *>(&this->lives), sizeof(this->lives));

    game.read(reinterpret_cast<char *>(this->guessed), sizeof(this->guessed));

    int len;
    game.read(reinterpret_cast<char *>(&len), sizeof(len));

    char *c = new char[len];
    game.read(c, sizeof(char) * len);
    this->word = c;
    this->checkWin();

    delete[] c;
    game.close();
}

void Game::checkWin() {
    this->won = true;
    for (const char &x : this->word)
        this->won &= this->guessed[x - 'A'];

    if (won) {
        this->save();
        User::getUser()->addGuessed(this->word.c_str());
    }
}

void Game::guess(char c) {
    if (c >= 'a' && c <= 'z')
        c = c - 'a' + 'A';

    if (c < 'A' || c > 'Z')
        throw std::invalid_argument("Input not a letter");

    if (!won && !lost && !this->guessed[c - 'A']) {
        this->guessed[c - 'A'] = true;
        for (char &x : this->word) {
            if (x == c) {
                this->checkWin();
                return;
            }
        }

        this->lives--;
        lost = lives == 0;
    }
}

void Game::save() const {
    int sum = 0;
    for (const char &x : this->word)
        sum += x;

    std::ofstream game(std::string(User::getUser()->getUsername()) + "_" +
                           std::to_string(sum) + ".hang",
                       std::ios::binary);

    game.seekp(0, std::ios::beg);
    game.write(reinterpret_cast<const char *>(&this->lives),
               sizeof(this->lives));

    game.write(reinterpret_cast<const char *>(this->guessed),
               sizeof(this->guessed));

    int len = this->word.size();
    game.write(reinterpret_cast<char *>(&len), sizeof(len));

    game.write(this->word.c_str(), len * sizeof(char));

    game.close();
}

bool Game::isWon() const {
    return this->won;
}

bool Game::isLost() const {
    return this->lost;
}

std::ostream &operator<<(std::ostream &os, const Game &game) {
    for (const char &x : game.word)
        os << (game.guessed[x - 'A'] ? x : '_') << " ";

    os << std::endl;
    os << std::endl;
    os << "Guessed letters:";

    for (char i = 'A'; i <= 'Z'; i++)
        if (game.guessed[i - 'A'])
            os << " " << i;
    os << std::endl;
    os << ART[game.lives] << std::endl;
    return os;
}