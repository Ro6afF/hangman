#include "User.hpp"

#include "exceptions.hpp"
#include <algorithm>
#include <cstring>
#include <fstream>

bool User::logedIn = false;
User User::user;

User::User() : User("", "", "") {}

User::User(const char *username, const char *email, const char *password) {
    strcpy(this->username, username);
    strcpy(this->email, email);
    strcpy(this->password, password);
}

void User::loadGuessed() {
    std::ifstream db(std::string(username) + "_guessed");
    int num;
    db >> num;

    if (!db.good())
        num = 0;

    std::string s;
    for (int i = 0; i < num; i++) {
        db >> s;
        this->guessedWords.insert(s);
    }

    db.close();
}

void User::signUp(const char *username, const char *email,
                  const char *password) {
    if (logedIn)
        throw UserException("Already loged in!");
    std::fstream db("users.db", std::ios::in | std::ios::binary);

    int cnt;

    db.seekg(0, std::ios::beg);
    db.read(reinterpret_cast<char *>(&cnt), sizeof(cnt));

    if (!db.good())
        cnt = 0;

    User u;
    for (int i = 0; i < cnt; i++) {
        db.seekg(sizeof(cnt) + i * sizeof(u), std::ios::beg);
        db.read(reinterpret_cast<char *>(&u), sizeof(u));

        // TODO: different exception types
        if (strcmp(username, u.username) == 0)
            throw UserException("User with this username exists!");

        if (strcmp(email, u.email) == 0)
            throw UserException("User with this email exists!");
    }

    db.close();

    u = User(username, email, password);
    cnt++;

    // create file if not exists
    db.open("users.db", std::ios::app);
    db.close();

    db.open("users.db", std::ios::out | std::ios::binary | std::ios::in);

    db.seekp(0, std::ios::beg);
    db.write(reinterpret_cast<char *>(&cnt), sizeof(cnt));

    // writes guessedWords too, but it is ignored when reading
    db.seekp(0, std::ios::end);
    db.write(reinterpret_cast<char *>(&u), sizeof(u));

    db.close();
}

void User::signIn(const char *username, const char *password) {
    if (logedIn)
        throw UserException("Already loged in!");

    std::fstream db("users.db", std::ios::in | std::ios::binary);

    int cnt;

    db.seekg(0, std::ios::beg);
    db.read(reinterpret_cast<char *>(&cnt), sizeof(cnt));

    if (!db.good())
        cnt = 0;

    User u;
    for (int i = 0; i < cnt; i++) {
        db.seekg(sizeof(cnt) + i * sizeof(u), std::ios::beg);
        db.read(reinterpret_cast<char *>(&u), sizeof(u));

        if (strcmp(username, u.username) != 0)
            continue;

        if (strcmp(password, u.password) == 0) {
            db.close();

            // ignore what is in guessedWords
            u.guessedWords = std::set<std::string>();
            u.guessedWords.clear();
            u.loadGuessed();

            logedIn = true;
            user = u;

            return;
        } else
            break;
    }

    db.close();
    throw UserException("Wrong username or password!");
}

void User::resetPassword(const char *username, const char *email,
                         const char *password) {
    if (logedIn)
        throw UserException("Already loged in!");

    std::fstream db("users.db",
                    std::ios::in | std::ios::binary | std::ios::out);

    int cnt;

    db.seekg(0, std::ios::beg);
    db.read(reinterpret_cast<char *>(&cnt), sizeof(cnt));

    if (!db.good())
        cnt = 0;

    User u;
    for (int i = 0; i < cnt; i++) {
        db.seekg(sizeof(cnt) + i * sizeof(u), std::ios::beg);
        db.read(reinterpret_cast<char *>(&u), sizeof(u));

        if (strcmp(username, u.username) != 0)
            continue;

        if (strcmp(email, u.email) != 0)
            continue;

        // ignore what is in guessedWords
        u.guessedWords = std::set<std::string>();
        u.guessedWords.clear();
        u.loadGuessed();

        strcpy(u.password, password);

        db.seekp(sizeof(cnt) + i * sizeof(u), std::ios::beg);
        db.write(reinterpret_cast<char *>(&u), sizeof(u));
        db.close();

        return;
    }
    db.close();
    throw UserException("No user found with the given mail and password!");
}

std::vector<std::pair<int, std::string>> User::getStanding() {
    if (!logedIn)
        throw UserException("User not logged in!");

    std::fstream db("users.db", std::ios::in | std::ios::binary);

    int cnt;

    db.seekg(0, std::ios::beg);
    db.read(reinterpret_cast<char *>(&cnt), sizeof(cnt));

    if (!db.good())
        cnt = 0;

    std::vector<std::pair<int, std::string>> standing;
    standing.reserve(cnt);

    User u;
    for (int i = 0; i < cnt; i++) {
        db.seekg(sizeof(cnt) + i * sizeof(u), std::ios::beg);
        db.read(reinterpret_cast<char *>(&u), sizeof(u));

        // ignore what is in guessedWords
        u.guessedWords = std::set<std::string>();
        u.loadGuessed();

        standing.push_back(std::make_pair(u.guessedWords.size(), u.username));
    }

    std::sort(standing.begin(), standing.end(),
              [](std::pair<int, std::string> a, std::pair<int, std::string> b) {
                  if (a.first == b.first)
                      return a.second < b.second;
                  return a.first > b.first;
              });

    return standing;
}

User *User::getUser() {
    if (!logedIn)
        return nullptr;

    return &user;
}

void User::addGuessed(const char *word) {
    std::ofstream file(std::string(this->username) + "_guessed");

    this->guessedWords.insert(word);

    file << this->guessedWords.size() << std::endl;

    for (const std::string &x : this->guessedWords)
        file << x << std::endl;

    file.close();
}

int User::guessedWordsCount() const {
    return this->guessedWords.size();
}

const char *User::getUsername() const {
    return this->username;
}

const char *User::getEmail() const {
    return this->email;
}

const char *User::getPassword() const {
    return this->password;
}
