#ifndef __USER_HPP
#define __USER_HPP

class User {
  private:
    char username[128];
    char email[128];
    char password[128];
    static bool logedIn;
    static User user;

    User(const char *username, const char *email, const char *password);

  public:
    User();

    static void signUp(const char *username, const char *email,
                       const char *password);
    static void signIn(const char *username, const char *password);

    static User *getUser();

    const char *getUsername() const;
    const char *getEmail() const;
    const char *getPassword() const;

    void setUsername(const char *password, const char *newUsername);
    void setEmail(const char *password, const char *newEmail);
    void setPassword(const char *password, const char *newUsername);
};

#endif // __USER_HPP