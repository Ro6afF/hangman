#ifndef __HANGMAN_EXCEPTIONS_HPP
#define __HANGMAN_EXCEPTIONS_HPP

#include <stdexcept>

class UserException : public std::logic_error {
  public:
    UserException(const std::string &arg) : std::logic_error(arg){};
    virtual ~UserException() = default;
};

class GameException : public std::logic_error {
  public:
    GameException(const std::string &arg) : std::logic_error(arg){};
    virtual ~GameException() = default;
};

class WordBankException : public std::logic_error {
  public:
    WordBankException(const std::string &arg) : std::logic_error(arg){};
    virtual ~WordBankException() = default;
};

#endif // __HANGMAN_EXCEPTIONS_HPP