#include "WordBank.hpp"

#include "User.hpp"
#include "exceptions.hpp"
#include <cstdlib>
#include <fstream>

int WordBank::wordCount(std::ifstream &db) {
    int cnt = 0;

    db.seekg(0, std::ios::beg);

    std::string s;
    while (db >> s)
        cnt++;

    return cnt;
}

void WordBank::addWord(const char *word) {
    if (User::getUser() == nullptr)
        throw WordBankException("User not logged in!");

    std::fstream db("words.db", std::ios::in);
    std::string w(word);

    for (size_t i = 0; i < w.size(); i++) {
        if (w[i] >= 'a' && w[i] <= 'z')
            w[i] = w[i] + 'A' - 'a';

        if (w[i] < 'A' || w[i] > 'Z')
            throw WordBankException(
                "Word contains symbols which are not letters");
    }

    std::string s;
    while (db >> s)
        if (s == w)
            throw WordBankException("Word already exists!");

    db.close();

    db.open("words.db", std::ios::app);
    db.seekp(0, std::ios::end);

    db << w << std::endl;

    db.close();
}

#include <iostream>

std::string WordBank::getRandomWord() {
    std::ifstream db("words.db");

    int cnt = wordCount(db);
    if (cnt == 0)
        throw WordBankException("No words found. Add words first!");

    int sel = rand() % cnt;

    db.close();
    db.open("words.db");
    db.seekg(0, std::ios::beg);

    std::string s;
    for (int i = 0; i <= sel; i++)
        db >> s;

    db.close();

    return s;
}