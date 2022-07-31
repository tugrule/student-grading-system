#ifndef DATABASE_HPP
#define DATABASE_HPP
#include <vector>
#include "student.hpp"
class Database {
    std::vector<Student> _students;
    std::string _fileName;
    auto findStudent(const std::string& id); 
 public: 
    Database(const std::string& fileName) :_fileName(fileName) {loadFile();}
    void saveToFile();
    void loadFile();
    bool existStudent(const std::string& id); 
    void viewStudent(std::ostream& os, const std::string& id);
    bool addStudent(const std::string& id, const std::string& fName, const std::string& lName);
    bool editStudent(const std::string& id, const std::string& name, const double& grade);
    bool editStudent(const std::string& id, const std::string& name);
    bool editStudent(const std::string& id);
    bool deleteStudent(const std::string& id);
    friend std::ostream& operator<<(std::ostream& os, const Database& db);
};
#endif