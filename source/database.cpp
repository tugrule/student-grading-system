#include "database.hpp"
#include <algorithm>
#include <fstream>
#include <sstream> 
#include <stdexcept>

void Database::saveToFile() {
    std::ofstream out;  //open output file for students
    out.open(_fileName, std::ios::out);
    for(const Student& s : _students) {
        s.save(out);
    }
    out.close(); 
}

void Database::loadFile(){
    std::ifstream in;   //input file stream
    in.open(_fileName, std::ios::in);   //open the file for input
    std::vector<std::string> row;   //vector to save words in 
    std::string line, word;   //line for getline, word for separating line
    if (!in.is_open()){     
        throw std::runtime_error("File is not open!");  //if file is not opening then error
    }
    bool st = true; //to know when reading student or grades
    std::string id; //id of student 
    while(std::getline(in, line))
    {
        row.clear();    //clear out vector 
        std::stringstream ss(line); 
        while(getline(ss,word,',')){    //separate words in line and add to vector
            row.push_back(word);
        }
        if(st) {    //if student line then save id and add it to the database
            id = row[0];
            if(!addStudent(id, row[1], row[2])){
                throw std::runtime_error("Cannot initialize student records.");
            }
            st = false; 
        }
        else{ //if grade line add grades one by one
            st = true; //next line will be student
            int ctr = 0; //to keep track of criteria and grades 
            std::string name;   //criteria name
            double grade;       //grade 
            for(auto it = row.begin(); it != row.end(); it++ ) {
                if(std::next(it) == row.end()) continue;     //ignore total grade - gets calculated later
                else if(ctr % 2 == 0) {     //here is the criteria -- even counter 
                    //std::cout << *it << std::endl;
                    name = (*it);
                    ctr++;
                }
                else {                      //grade -- odd counter
                    //std::cout << *it << std::endl;
                    grade = std::stod(*it);
                    editStudent(id, name, grade);
                    ctr++;
                }
            }
        }
    }
    in.close();
}

auto Database::findStudent(const std::string& id) {
    auto it = _students.begin();
    for(it ; it < _students.end(); it++){
        if(it->getId() == id) 
            return it;
    }
    return it;
}
 
bool Database::existStudent(const std::string& id) {
    if(findStudent(id) != _students.end())
        return true;
    else 
        return false; 
}
bool Database::addStudent(const std::string& id, const std::string& fName, const std::string& lName) {
    auto it = findStudent(id);
    if(it != _students.end())
        return false;
    else  
        _students.push_back(Student(id,fName,lName));
        return true;
}

bool Database::editStudent(const std::string& id, const std::string& name, const double& grade){
    auto it = findStudent(id);
    if(it != _students.end()){
        return it->insertGrade(name, grade); 
    }
    return false; 
}

bool Database::editStudent(const std::string& id, const std::string& name){
    auto it = findStudent(id);
    if(it != _students.end()){
        return it->deleteGrade(name);
    }
    return false; 
}

bool Database::editStudent(const std::string& id) {
    auto it = findStudent(id);
    if(it != _students.end()){
        it->clearGrades();
        return true; 
    }
    return false; 
}

bool Database::deleteStudent(const std::string& id){
    auto it = findStudent(id);
    if(it != _students.end()){
        _students.erase(it);
        return true; 
    }
    return false; 
}

void Database::viewStudent(std::ostream& os, const std::string& id) {
    auto it = findStudent(id);
    if(it != _students.end())
        os << (*it);
}


std::ostream& operator<<(std::ostream& os, const Database& db) {
    for(auto it = db._students.begin(); it < db._students.end(); it++){    
        os << (*it) << "\n";
    }
    return os;
}
/*
int main () {
    Database db("none"); 
    db.addStudent("001", "rob", "will");
    db.addStudent("002", "dest", "jan");
    db.editStudent("001", "add", "CSE 2102", 95.6);
    db.editStudent("001", "add", "CSE 2100", 95.6);
    db.editStudent("001", "del", "CSE 2102", 95.6);
    db.editStudent("001", "clr", "CSE 2102", 95.6);
    std::cout << db;
    db.deleteStudent("002");
    db.viewStudent(std::cout, "001");
    return 0;
}
*/