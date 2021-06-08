#ifndef __GAME_HPP
#define __GAME_HPP

#include <fstream>
#include <string>

class Game {
  private:
    std::string word;
    bool guessed['Z' - 'A' + 1];
    int lives;
    bool won;
    bool lost;

    void checkWin();

  public:
    Game();
    Game(const char *file);

    void guess(char c);
    void save() const;

    bool isWon() const;
    bool isLost() const;

    friend std::ostream &operator<<(std::ostream &os, const Game &game);
};

const std::string ART[] = {
    "  +---+  \n"
    "  |   |  \n"
    "  O   |  \n"
    " /|\\  |  \n"
    " / \\  |  \n"
    "      |  \n"
    "=========\n",

    "  +---+  \n"
    "  |   |  \n"
    "  O   |  \n"
    " /|\\  |  \n"
    " /    |  \n"
    "      |  \n"
    "=========\n",

    "  +---+  \n"
    "  |   |  \n"
    "  O   |  \n"
    " /|\\  |  \n"
    "      |  \n"
    "      |  \n"
    "=========\n",

    "  +---+  \n"
    "  |   |  \n"
    "  O   |  \n"
    " /|   |  \n"
    "      |  \n"
    "      |  \n"
    "=========\n",

    "  +---+  \n"
    "  |   |  \n"
    "  O   |  \n"
    "  |   |  \n"
    "      |  \n"
    "      |  \n"
    "=========\n",

    "  +---+  \n"
    "  |   |  \n"
    "  O   |  \n"
    "      |  \n"
    "      |  \n"
    "      |  \n"
    "=========\n",

    "  +---+  \n"
    "  |   |  \n"
    "      |  \n"
    "      |  \n"
    "      |  \n"
    "      |  \n"
    "=========\n",
};

#endif // __GAME_HPP
