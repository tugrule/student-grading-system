#include <iostream>
#include "menu.hpp"

void Menu::mainPrompt() {
    std::cout << "\n\n\t\tSTUDENT GRADING SYSTEM" << std::endl
        << "\nPress 1: View all students" << std::endl
        << "Press 2: View student" << std::endl
        << "Press 3: Add student" << std::endl
        << "Press 4: Manage grades" << std::endl
        << "Press 5: Delete student" << std::endl
        << "Press 6: Save & Exit" << std::endl;
}

void Menu::gradePrompt(const std::string& id) {
    bool use = 1; 
    while(use){ 
        std::cout << "\n\nPress 1: Add grade" << std::endl
        << "Press 2: Delete grade" << std::endl
        << "Press 3: Clear all grades" << std::endl
        << "Press 4: View all grades" << std::endl
        << "Press 5: Back to main menu" << std::endl;
        
        std::cout << "Enter option: "; 
        int option; 
        std::cin >> option; 
        switch (option){
        case 1:{
            std::string name;
            double grade; 
            std::cout << "\nPlease enter criteria name    :";
            std::cin >> name;
            std::cout << "Please enter grade            :";
            std::cin >> grade;
            if(_db.editStudent(id, name, grade))
                std::cout << "Grade added successfully.";
            else  
                std::cout << "Error: Criteria already exists.";
            break;
        }
        case 2: {
            std::string name;
            std::cout << "\nPlease enter criteria name    :";
            std::cin >> name;
            if(_db.editStudent(id, name))
                std::cout << "Grade deleted successfully.";
            else
                std::cout << "Error: Criteria doesn't exist.";
            break;
            }
        case 3: 
            _db.editStudent(id);
            break;
        case 4:
            std::cout << "\n\n\t\tDISPLAY GRADES\n" << std::endl; 
            _db.viewStudent(std::cout, id);
            break;
        case 5: 
            use = false; 
            break;
        default:
            std::cout << "Please enter a valid option!" << std::endl; 
            break;
        }
    }
} 

void Menu::mainMenu() {
    bool use = true; 
    while(use) {
        mainPrompt();
        std::cout << "Enter option: "; 
        int option; 
        std::cin >> option; 
        switch(option) {
        case 1: 
            std::cout << "\n\n\t\tALL STUDENT RECORDS\n" << std::endl << _db;
            break; 
        case 2: 
            promptView();
            break;
        case 3:
            promptAdd();
            break;
        case 4:
            promptEdit();
            break;
        case 5:
            promptDelete();
            break;
        case 6: 
            _db.saveToFile();
            use = false; 
            break;
        default:
            std::cout << "Please enter a valid option!" << std::endl; 
        }
    }
}

std::string Menu::promptId(){
    std::cout << "Please enter student id: ";
    std::string id; 
    std::cin >> id;
    return id;
}

void Menu::promptView() {
    std::cout << "\n\n\t\tVIEW STUDENT\n" << std::endl;
    std::string id = promptId();
    std::cout << "\n";
    _db.viewStudent(std::cout, id);
}

void Menu::promptAdd() {
    std::cout << "\n\n\t\tADD NEW STUDENT\n" << std::endl; 
    std::string id = promptId();
    std::cout << "Please enter student's first name: ";
    std::string fName; 
    std::cin >> fName;
    std::cout << "Please enter student's last name: ";
    std::string lName; 
    std::cin >> lName;
    if(_db.addStudent(id, fName, lName))
        std::cout << id << " added successfully." << std::endl; 
    else   
        std::cout << id << " already exists." << std::endl; 
}

void Menu::promptEdit() {
    std::cout << "\n\n\t\tMANAGE STUDENT GRADES\n" << std::endl;
    std::string id = promptId();
    if(_db.existStudent(id)){
        gradePrompt(id);
    }
    else 
        std::cout << id << " does not exist!" << std::endl;  
}

void Menu::promptDelete() {
    std::cout << "\n\n\t\tDELETE STUDENT\n" << std::endl; 
    std::string id = promptId();
    if(_db.deleteStudent(id))
        std::cout << id << " deleted successfully." << std::endl; 
    else 
        std::cout << id << " does not exist." << std::endl; 
}

