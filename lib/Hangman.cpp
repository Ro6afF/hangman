#include "Hangman.hpp"

#include "Game.hpp"
#include "User.hpp"
#include "WordBank.hpp"

std::istream *Hangman::inp = nullptr;
std::ostream *Hangman::out = nullptr;
Game *Hangman::current = nullptr;

void Hangman::help() {
    std::ostream &out = *Hangman::out;

    out << "Welcome to hangman! \nThis is a list of the possible commands: \n"
        << "  help - display this message\n"
        << "  login - log in to the game\n"
        << "  register - make a new account in the game\n"
        << "  resetPass - reset password\n"
        << "  addWord - add a new word to the bank\n"
        << "  start - start a new game\n"
        << "  continue - load a saved game from file\n"
        << "  # - save the current game\n"
        << "  standing - print users by score\n"
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

void Hangman::resetPass() {
    std::istream &inp = *Hangman::inp;
    std::ostream &out = *Hangman::out;

    std::string username, pass, email;
    out << "Username: ";
    inp >> username;
    out << "Email: ";
    inp >> email;
    out << "New password: ";
    inp >> pass;

    try {
        User::resetPassword(username.c_str(), email.c_str(), pass.c_str());
        out << "[ Password changed sucessfully! ]" << std::endl;
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
    } catch (std::logic_error &e) {
        out << "[ " << e.what() << " ]" << std::endl;
    }
}

void Hangman::start() {
    std::ostream &out = *Hangman::out;

    try {
        current = new Game();
    } catch (std::logic_error &e) {
        out << "[ " << e.what() << " ]" << std::endl;
    }
}

void Hangman::continueGame() {
    std::istream &inp = *Hangman::inp;
    std::ostream &out = *Hangman::out;

    std::string file;
    out << "Enter file name: ";
    inp >> file;

    try {
        current = new Game(file.c_str());
    } catch (std::logic_error &e) {
        out << "[ " << e.what() << " ]" << std::endl;
    }
}

void Hangman::save() {
    std::ostream &out = *Hangman::out;

    current->save();
    delete current;
    current = nullptr;

    out << "[ Current game stopped and saved to file ]" << std::endl;
}

void Hangman::standing() {
    std::ostream &out = *Hangman::out;

    try {
        std::vector<std::pair<int, std::string>> stand = User::getStanding();

        int i = 1;

        for (std::pair<int, std::string> &x : stand) {
            out << "#" << i++ << " " << x.second << " " << x.first << std::endl;
        }
    } catch (std::logic_error &e) {
        out << "[ " << e.what() << " ]" << std::endl;
    }
}

void Hangman::exit() {
    std::istream &inp = *Hangman::inp;
    std::ostream &out = *Hangman::out;

    if (current != nullptr) {
        out << "Do you want to save the game to a file? [yes / no]:\n";
        std::string ans;
        inp >> ans;
        for (size_t i = 0; i < ans.size(); i++)
            if (ans[i] >= 'A' && ans[i] <= 'Z')
                ans[i] = ans[i] + 'a' - 'A';

        if (ans == "yes") {
            current->save();
            out << "[ Saved! ]\n";
        }
        delete current;
        current = nullptr;
    }
    out << "Bye!" << std::endl;
}

void Hangman::run(std::istream &inp, std::ostream &out) {
    Hangman::inp = &inp;
    Hangman::out = &out;

    (*Hangman::inp).tie(Hangman::out);
    std::string cmd;
    help();
    do {
        if (current == nullptr)
            out << "$ ";
        else {
#ifdef WINDOWS
            system("cls");
#else
            system("clear");
#endif
            out << *current;
            if (current->isLost()) {
                out << "You lost!!!\n$ ";
                delete current;
                current = nullptr;
            } else if (current->isWon()) {
                out << "YOU WON!\n$ ";
                delete current;
                current = nullptr;
            } else {
                out << "Pick a letter --> ";
            }
        }
        inp >> cmd;

        for (size_t i = 0; i < cmd.size(); i++)
            if (cmd[i] >= 'A' && cmd[i] <= 'Z')
                cmd[i] = cmd[i] + 'a' - 'A';

        if (cmd == "exit")
            exit();
        else if (cmd == "help")
            help();
        else if (cmd == "standing")
            standing();
        else if (current == nullptr && cmd == "login")
            login();
        else if (current == nullptr && cmd == "register")
            signUp();
        else if (current == nullptr && cmd == "resetpass")
            resetPass();
        else if (current == nullptr && cmd == "addword")
            addWord();
        else if (current == nullptr && cmd == "start")
            start();
        else if (current == nullptr && cmd == "continue")
            continueGame();
        else if (current != nullptr && cmd == "#")
            save();
        else if (current != nullptr && cmd.size() == 1)
            current->guess(cmd[0]);
        else
            out << "Command not found..." << std::endl;
    } while (cmd != "exit");
}