#ifndef __GAME_HPP
#define __GAME_HPP

#include <fstream>
#include <string>

class Game {
  private:
    std::string word;
    bool guessed['Z' - 'A' + 1];
    int lives;

  public:
    Game();
    Game(const char *file);

    void guess(char c);
    void save() const;

    friend std::ostream &operator<<(std::ostream &os, const Game &game);
};

const std::string ART[] = {"7", "6", "5", "4", "3", "2", "1"};

#endif // __GAME_HPP
