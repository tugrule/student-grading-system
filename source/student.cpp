#include "student.hpp"
#include <map> 

Student::Student(){}

void Student::save(std::ostream& os) const{
    os << _id << "," << _fName << "," << _lName << "\n";
    for(auto it = _gradeBook.begin(); it != _gradeBook.end(); it++){
        os << it->first << "," << it->second << ",";
    }
    os << _totalGrade << "\n";
}
Student::Student(const std::string& id, const std::string& fName, const std::string& lName) 
 : _id(id), _fName(fName), _lName(lName){_totalGrade=0;}

std::ostream& operator<<(std::ostream& os,const Student& s) {
    os << "Student ID\t: " << s._id << "\n"
        << "First Name\t: " <<  s._fName << "\n" 
        <<"Last Name\t: " << s._lName << "\n";
    for(auto it = s._gradeBook.begin(); it != s._gradeBook.end(); it++){
        os << "Criteria: " << it->first << "\t: " << it->second << "\n";
    }
    os << "Total grade: " << s._totalGrade << "\n";
    return os;
}

bool Student::insertGrade(const std::string& name, const double& grade) {
    if(_gradeBook.find(name) == _gradeBook.end()){
        _gradeBook.insert({name, grade});
        _totalGrade += grade;
        return true; 
    }
    else 
        return false; 
}
bool Student::deleteGrade(const std::string& name) {
    auto it = _gradeBook.find(name);
    if(it != _gradeBook.end()){
        _totalGrade = _totalGrade - it->second;
        _gradeBook.erase(it);
        return true; 
    }
    else 
        return false;
}

/*
int main() {
    Student s("001","Greg", "Brown");
    s.insertGrade("CSE2300",97);
    s.insertGrade("CSE2100",91);
    s.deleteGrade("CSE2300");
    std::cout << s << std::endl;
    return 0;
}
*/




