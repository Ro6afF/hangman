#include "Game.hpp"

#include "User.hpp"
#include "WordBank.hpp"
#include <fstream>

Game::Game() {
    this->word = WordBank::getRandomWord();

    for (int i = 'A'; i <= 'Z'; i++) {
        this->guessed[i - 'A'] = false;
    }
    guessed[word[0] - 'A'] = true;

    this->lives = 7;
}

Game::Game(const char *file) {
    std::ifstream game(file);
    game.seekg(0, std::ios::beg);
    game.read(reinterpret_cast<char *>(&this->lives), sizeof(this->lives));

    game.read(reinterpret_cast<char *>(this->guessed), sizeof(this->guessed));

    int len;
    game.read(reinterpret_cast<char *>(&len), sizeof(len));

    char *c = new char[len];
    game.read(c, sizeof(char) * len);
    this->word = c;

    delete[] c;
    game.close();
}

void Game::guess(char c) {
    this->guessed[c - 'A'] = true;
    for (char &x : this->word) {
        if (x == c) {
            return;
        }
    }

    this->lives--;
}

void Game::save() const {
    int sum = 0;
    for (const char &x : this->word)
        sum += x;

    std::ofstream game(std::string(User::getUser()->getUsername()) + "_" +
                           std::to_string(sum) + ".hang",
                       std::ios::binary);

    game.seekp(0, std::ios::beg);
    game.write(reinterpret_cast<const char *>(&this->lives), sizeof(this->lives));

    game.write(reinterpret_cast<const char *>(this->guessed),
               sizeof(this->guessed));

    int len = this->word.size();
    game.write(reinterpret_cast<char *>(&len), sizeof(len));

    game.write(this->word.c_str(), len * sizeof(char));

    game.close();
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
    os << ART[game.lives - 1] << std::endl;
    return os;
}