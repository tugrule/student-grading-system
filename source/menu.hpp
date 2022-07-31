#ifndef MENU_HPP
#define MENU_HPP
#include "database.hpp"
#include <string>

class Menu {
    Database _db;
    void mainPrompt();
    void gradePrompt(const std::string& id);
 public: 
    Menu(const std::string& fileName) :_db(fileName) {}
    void mainMenu();
    std::string promptId();
    void promptView(); 
    void promptAdd();
    void promptEdit(); 
    void promptDelete();
};

#endif