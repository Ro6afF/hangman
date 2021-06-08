#include "Hangman.hpp"

#include "User.hpp"
#include "WordBank.hpp"

std::istream *Hangman::inp = nullptr;
std::ostream *Hangman::out = nullptr;

void Hangman::help() {
    std::ostream &out = *Hangman::out;

    out << "Welcome to hangman! \nThis is a list of the possible commands: \n"
        << "  help - display this message\n"
        << "  login - log in to the game\n"
        << "  register - make a new account in the game\n"
        << "  addWord - add a new word to the bank\n"
        << "  start - start a new game\n"
        << "  continue - load a saved game from file\n"
        << "  # - save the current game\n"
        << "  exit - exit the game\n";
    out.flush();
}

void Hangman::login() {
    std::istream &inp = *Hangman::inp;
    std::ostream &out = *Hangman::out;

    std::string username, pass;
    out << "Username: ";
    inp >> username;
    out << "Password: ";
    inp >> pass;

    try {
        User::signIn(username.c_str(), pass.c_str());
        out << "[ Successful login! ]" << std::endl;
    } catch (std::invalid_argument &e) {
        out << "[ " << e.what() << " ]" << std::endl;
    }
}

void Hangman::signUp() {
    std::istream &inp = *Hangman::inp;
    std::ostream &out = *Hangman::out;

    std::string username, pass, email;
    out << "Username: ";
    inp >> username;
    out << "Email: ";
    inp >> email;
    out << "Password: ";
    inp >> pass;

    try {
        User::signUp(username.c_str(), email.c_str(), pass.c_str());
        out << "[ Successful regstration! ]" << std::endl;
    } catch (std::invalid_argument &e) {
        out << "[ " << e.what() << " ]" << std::endl;
    }
}

void Hangman::addWord() {
    std::istream &inp = *Hangman::inp;
    std::ostream &out = *Hangman::out;

    std::string w;
    out << "Word to add: ";
    inp >> w;
    try {
        WordBank::addWord(w.c_str());
        out << "[ You successfully added a new word! ]" << std::endl;
    } catch (std::invalid_argument &e) {
        out << "[ " << e.what() << " ]" << std::endl;
    }
}

void Hangman::run(std::istream &inp, std::ostream &out) {
    Hangman::inp = &inp;
    Hangman::out = &out;

    (*Hangman::inp).tie(Hangman::out);
    std::string cmd;
    help();
    do {
        out << "$ ";
        inp >> cmd;

        for (size_t i = 0; i < cmd.size(); i++)
            if (cmd[i] >= 'A' && cmd[i] <= 'Z')
                cmd[i] = cmd[i] + 'a' - 'A';

        if (cmd == "exit")
            out << "Bye!" << std::endl;
        else if (cmd == "help")
            help();
        else if (cmd == "login")
            login();
        else if (cmd == "register")
            signUp();
        else if (cmd == "addword")
            addWord();
        else
            out << "Command not found..." << std::endl;
    } while (cmd != "exit");
}