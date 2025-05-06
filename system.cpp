#include "Header.hpp"
#include "Person.cpp"
#include "Question.cpp"
#include "ReportCard.cpp"
#include "Teacher.cpp"
#include "Student.cpp"
#include "Exam.cpp"


int main(){
    printWelcomeMessage();
    
    Load_students();
    Load_teachers();
    Load_Exam_codes();
    Load_Exams();
    Menu();
    
    lists_deleter();

    
    return 0;
}