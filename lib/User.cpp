#include "User.hpp"

#include <cstring>
#include <fstream>
#include <stdexcept>

bool User::logedIn = false;
User User::user;

User::User() : User("", "", "") {}

User::User(const char *username, const char *email, const char *password) {
    strcpy(this->username, username);
    strcpy(this->email, email);
    strcpy(this->password, password);
}

void User::signUp(const char *username, const char *email,
                  const char *password) {
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
            throw std::invalid_argument("User with this username exists!");

        if (strcmp(email, u.email) == 0)
            throw std::invalid_argument("User with this email exists!");
    }

    db.close();

    u = User(username, email, password);
    cnt++;

    db.open("users.db", std::ios::out | std::ios::binary);

    db.seekp(0, std::ios::beg);
    db.write(reinterpret_cast<char *>(&cnt), sizeof(cnt));

    db.seekp(0, std::ios::end);
    db.write(reinterpret_cast<char *>(&u), sizeof(u));

    db.close();
}

void User::signIn(const char *username, const char *password) {
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

            logedIn = true;
            user = u;

            return;
        } else
            break;
    }

    db.close();
    throw std::invalid_argument("Wrong username or password!");
}

User *User::getUser() {
    if (!logedIn)
        return nullptr;

    return &user;
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

// TODO: setters