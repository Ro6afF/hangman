#include "WordBank.hpp"

#include <cstdlib>
#include <fstream>
int WordBank::wordCount(std::ifstream &db) {
    int cnt = 0;

    db.seekg(0, std::ios::beg);

    std::string s;
    while (db >> s)
        cnt++;

    db.close();

    return cnt;
}

void WordBank::addWord(const char *word) {
    std::fstream db("words.db", std::ios::in);

    std::string s;
    while (db >> s)
        if (s == word)
            throw std::invalid_argument("Word already exists!");

    db.close();

    db.open("words.db", std::ios::app);
    db.seekp(0, std::ios::end);

    db << word << std::endl;

    db.close();
}

std::string WordBank::getRandomWord() {
    std::ifstream db("words.db");
    int sel = rand() % wordCount(db);

    db.seekg(0, std::ios::beg);

    std::string s;
    for (int i = 0; i < sel; i++)
        db >> s;

    db.close();

    return s;
}