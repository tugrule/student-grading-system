#ifndef STUDENT_HPP
#define STUDENT_HPP
#include <string> 
#include <iostream> 
#include <map>

class Student {
    std::string _id, _fName, _lName;
    std::map<std::string,double> _gradeBook;     
    double _totalGrade;
 public:
    Student(); 
    Student(const std::string& id, const std::string& fName, const std::string& lName);
    void save(std::ostream& os) const;
    std::string getId() {return _id; }
    bool insertGrade(const std::string& name, const double& grade);
    bool deleteGrade(const std::string& name);
    void clearGrades() {_totalGrade = 0; _gradeBook.clear(); }
    friend std::ostream& operator<<(std::ostream& os, const Student& s);
};

#endif