#ifndef __USER_HPP
#define __USER_HPP

#include <set>
#include <string>
#include <utility>
#include <vector>

class User {
  private:
    char username[128];
    char email[128];
    char password[128];

    std::set<std::string> guessedWords;

    static bool logedIn;
    static User user;

    User(const char *username, const char *email, const char *password);

    void loadGuessed();

  public:
    User();

    static void signUp(const char *username, const char *email,
                       const char *password);
    static void signIn(const char *username, const char *password);
    static void resetPassword(const char *username, const char *email,
                              const char *password);

    static std::vector<std::pair<int, std::string>> getStanding();

    static User *getUser();

    const char *getUsername() const;
    const char *getEmail() const;
    const char *getPassword() const;

    void addGuessed(const char *word);
    int guessedWordsCount() const;
};

#endif // __USER_HPP