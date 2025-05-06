#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include<chrono>   // clock options
#include <iomanip> // for formating output
#include<thread>
#include<fstream>
#include <algorithm>
#include <random>
#include <ctime>
#include <sys/stat.h> // For directory creation
#include <unistd.h>
#include <sys/stat.h> // For non-Windows systems
#ifdef _WIN32
#include <direct.h>    // For Windows systems
#endif
#include "json.hpp"
#pragma once

using json = nlohmann::json;
using namespace std;


// Classes:
class Person;
class Teacher;
class Student;
class Exam;
class Exam_code;
class student_score;
class Question;
class ReportCard;



// Functions:
double time_counter(std::chrono::system_clock::time_point start);
void Clock_displayer(int time);
void Menu();
enum login { out = 0, in = 1 };
void lower(string* str);
void trim(string* str);
int Check_logout_exit_command(string cmd);
void printWelcomeMessage();
void lists_deleter();
double String_to_number(string str); 
void Load_students();
void Load_teachers();
void Load_Exam_codes();
void Load_Exams();
void store_students();
void store_teachers();
void store_Exam_codes();
void store_Exams();
Question json_to_Question(json j_question);
int exam_code_constructor(); 
Student json_to_student(json j_student);
Teacher json_to_teacher(json j_teacher);
Exam json_to_Exam(json j_exam);
bool Valid_ID(string id);
vector<int> getRandomSortedArray();
string FindExamName(string code);
void Change_question_score(string Exam_code,string std_id,double prev_score,double max,string question,string answer);


//records: 
vector<Student>* student_list = new vector<Student>;
vector<Teacher>* teacher_list = new vector<Teacher>;
vector<Exam_code>* exam_codes = new vector<Exam_code>;
vector<Exam>* created_Exams_list=new vector<Exam>;
int number_of_IDs=0;

void lower(string* str) {
    for (int i = 0; i < str->length(); i++) {
        if (str->at(i) <= 'Z' && str->at(i) >= 'A') {
            str->at(i) = str->at(i) + 32;
        }
    }
    return;
}



//============================================================================================================

//  Class declarations----------
//                             |
//                             |
//                             |
//                             |
//                             |
//                             |
//                             V

//Question class :

class Question{
    private:
        string type;
        string question_body;
        string Options[4]; // we use this for test question and for other types of questions they will be initialized with "null"
        string Answer;
        double Positive_effect;
        double Negative_effect;
        void display_to_teacher();
        void display_to_student();
        
        friend Question json_to_Question(json j_question);
        friend class Teacher;
        friend class Exam;
    public:
        Question();
        Question(string code){
            this->type="---First Question ---"; 
        }
        json Question_to_json();
    
};
//=========================================================================================================

class ReportCard{
private:
    
    vector<string> questions;
    vector<string>  Student_Answers;
    vector<string>  Correct_Answers;
    vector <double> scores;
    vector<double> Exams_Scores;
    vector<string> Exams_Codes;
    double Average;
    int attendence_number;
    double short_scores_sigma;  // Sigma of all positive and nengative scores
    double test_scores_sigma;   // Sigma of all positive and nengative scores

    friend class Student;
    friend class Exam;
    friend Student json_to_student(json j_student);  
    friend void Change_question_score(string Exam_code,string std_id,double prev_score,double max,string question,string answer);
public:
    ReportCard(){
        short_scores_sigma = 0;  // Sigma of all positive and nengative scores
        test_scores_sigma = 0 ;   // Sigma of all positive and nengative scores
        Average =0 ;
        attendence_number=0;
    }
    void display();


};





//=========================================================================================================

//student_score class:

class student_score{
    private:
        string exam_code;
        double score;
        friend class Student;
        friend class ReportCard;
        friend Student json_to_student(json j_student);
        friend class CSVHandler;
        friend void Change_question_score(string Exam_code,string std_id,double prev_score,double max,string question,string answer);
        
    public:
        void set_score(double scr){
            score=scr;
            return;
        }
        void set_exam_code(string code){
            exam_code=code;
            return;
        }
        inline double get_score(){return this->score;}
        

};

//============================================================================================================
//Exam_code class:

class Exam_code{
    protected:
        string designer;
        string Code;
        string designer_id;
       
    public:
        Exam_code();
        Exam_code(int n){};
        ~Exam_code();
        void set_designer(string name,string id);
        void set_code(string code);
        inline string get_designer(){return designer;}
        inline string get_code(){return Code;}
        void Add_to_list();
        void participate_student(string id);
        json Exam_code_to_json();
        friend Exam_code json_to_Exam_code(json exam_code);
        vector<string> participated_students;
        inline string get_designer_id(){return this->designer_id;}
};
Exam_code::Exam_code(){}
Exam_code::~Exam_code(){}
void Exam_code::set_designer(string name,string id){
    designer=name;
    this->designer_id=id;
    return;
}
void Exam_code::set_code(string code){
    this->Code=code;
    return;
}
void Exam_code::Add_to_list(){
    exam_codes->push_back(*this);
    return;
}
void Exam_code::participate_student(string id){
    participated_students.push_back(id);
    return;
}

json Exam_code :: Exam_code_to_json(){
    json exam;
    exam["designer"] = this->designer;
    exam["Code"] = this->Code;
    exam["designer_id"]= this->designer_id;
    exam["participated_students"] = json::array();
    for(auto student : this->participated_students){
        exam["participated_students"].push_back(student);
    }
    return exam;
}

//function to turn a json type exam code into exam_code class object:
Exam_code json_to_Exam_code(json exam_code){
    Exam_code new_code(-1);
    new_code.designer = exam_code["designer"];
    new_code.Code = exam_code["Code"];
    new_code.designer_id = exam_code["designer_id"];
    if(exam_code.contains("participated_students")){
        for(auto student : exam_code["participated_students"]){
            new_code.participated_students.push_back(student);
        }
    }

    return new_code;

}


// functions to store and load exam codes into program----
//                                                       |
//                                                       |
//                                                       V


void Load_Exam_codes(){
    ifstream file("exam_codes.json");
    if(file.is_open()){
        json codes;
        file >> codes;
        for(auto& code : codes){
            Exam_code * new_code = new Exam_code(-1);
            *new_code = json_to_Exam_code(code);
            exam_codes->push_back(*new_code);
            delete new_code;
        }
        file.close();
    }
    else {
        ofstream new_file("exam_codes.json");
        new_file << json::array().dump(4);
        new_file.close();
        cout << "Created new empty exa_codes.json" << endl;
    }

}


void store_Exam_codes(){
        json codes = json :: array();

        for(auto code :*exam_codes){
            codes.push_back(code.Exam_code_to_json());
        }

        ofstream file("exam_codes.json");

        if(file.is_open()){
            file << codes.dump(4);
            file.close();
        }
        else {
            cout << "Error: Failed to open exam_codes.json for writing!" << endl;
        }

}
//============================================================================================================
//Exam class :
class Exam : public Exam_code{
    private:
        static int max_code;
        string Name;
        friend Exam json_to_Exam(json j_exam);
        friend Teacher json_to_teacher(json j_teacher);
        int time;  // in  seconds 
        double number_of_Questions;
        vector <Question> Questions;  
        vector <string> Attended_students;
        vector <double> student_Grades;
        friend class Teacher;
        friend string FindExamName(string code);
    
    public:
        Exam();
        Exam(int n){time=0;};//for jsom to teacher function
        ~Exam();
        inline string get_code(){ return Code ; }
        inline string get_name(){ return Name ; }
        inline int get_time(){return time; }
        void Add();
        void Remove();
        void Show_to_teacher();
        void Show_to_student();
        student_score Execution(ReportCard& sheet,string name);
        void set_time();
        json Exam_to_json();
        void display_grades_to_teacher();
        

    
    
};
//============================================================================================================
// Person Class:
class Person {
    protected:
        string Name;
        string ID;
        string Password;
        login status;
        friend Student json_to_student(json j_student);
        virtual void Show_personal_information() = 0;
        virtual void Change_Passsword() = 0;
        
    
    public:
        Person();
        virtual ~Person();
        void setName();
        void setID(string id);
        void setPass();
        int check_Pass(string pass);
        inline string getname() { return Name; };
        inline string getID() { return ID; };
        void Logout();
        void Login();
        virtual void Exams(){};
        virtual void Options(){};
};
//======================================================================================================
// Teacher Class:
class Teacher : public Person {
    private:
        string number_of_courses;
        vector<string> Courses;
        friend void SignUP(vector<Teacher*>& teachers, vector<Student*>& students);
        friend void Login(vector<Teacher*>& teachers, vector<Student*>& students);
        friend Teacher json_to_teacher(json j_teacher);
        void Exams_scores_lists();
        virtual void Show_personal_information() final;
        virtual void Change_Passsword() final;
        

    public:
        Teacher();
        Teacher(int n){}; // this is for json to teacher function
        ~Teacher();
        void setCourses();
        virtual void Options();
        virtual void Exams();
        json teacher_to_json();
};

//===================================================================================================================

// Student Class:
class Student : public Person {
    private:
        string Field;
        friend void SignUP(vector<Teacher*>& teachers, vector<Student*>& students);
        friend void Login(vector<Teacher*>& teachers, vector<Student*>& students);
        vector <string> participated_exams;
        void setField();
        vector <student_score> scores;
        friend Student json_to_student(json j_student);
        virtual void Show_personal_information() final;
        virtual void Change_Passsword() final;
        ReportCard Scores_table;
        friend class CSVHandler;
        void Exam_Score_sheet_displayer();
        friend void Change_question_score(string Exam_code,string std_id,double prev_score,double max,string question,string answer);
        
    
    public:
        Student();
        Student(int n){}; // just give it a number --> this is beacuse prevneting error in  loading students
        ~Student();
        virtual void Options();
        void attend_exam();
        void Push_back_score(student_score scr);
        virtual void Exams() final;
        inline string get_field(){return this->Field;}
        json student_to_json( );
        double Average_score();
        double Max_score();
        int Rank_Computer();
        void display_Average();
};
//============================================================================================================


class CSVHandler {
private:
    string filename;
    string separator;
    const string CSV_DIR = "student_scores_csv_files"; // Directory name
    
    void create_csv_dir();

public:
    CSVHandler(Student student) {
        create_csv_dir(); 
        
        filename = CSV_DIR + "/" + student.getname() + ".csv";
        
        ofstream file(filename);

        file << "Exam,Score" << std::endl;
        for(auto score : student.scores) {
            file << FindExamName(score.exam_code) << "," << score.score << endl;
        }
        file.close();
        
        cout << "\033[0;96m" << student.Name << "\033[0m ,Your scores file is ready in \033[47m\033[0;32mcsv \033[0m\033[0mformat in this directory --> \e[0;93m"<< filename << "\033[0m" <<endl;
    }
};
   
void CSVHandler::create_csv_dir(){
    struct stat st;  // we use it to check the director status  If the directory doesn't exist it returns -1
    if (stat(CSV_DIR.c_str(), &st) == -1) {
        #ifdef _WIN32
        _mkdir(CSV_DIR.c_str());  // Windows version 
        #else
        mkdir(CSV_DIR.c_str(), 0755);  // Linux/macOS version 
        #endif
    }
}

//============================================================================================================


// functions implementations-------
//                                |
//                                |
//                                V


//this function remove the space at begining of the strings
void trim(string* str) {
    int len = str->length();
    int i = 0;
    while (i < len) {
        if (str->at(i) == ' ') {
            i++;
        } else {
            break;
        }
    }
    if (i == 0) {
        return;
    } else {
        for (int step = 0; step < i; step++) {
            int j = 0;
            for (j = 0; j < len - 1; j++) {
                str->at(j) = str->at(j + 1);
            }
            str->at(j) = '\0';
            len--;
        }
    }
    return;
}


// this function check for exit or logout command
int Check_logout_exit_command(string cmd) {
    lower(&cmd);
    if (cmd == "logout")
        return 1;
    else if (cmd == "exit")
        return 2;
    else
        return 0;
}

// this function print the welcome message at the start of the programm
void printWelcomeMessage() {
    cout << endl;
    cout << "-----------------------------------------------\n";
    cout << "        WELCOME TO THE SYSTEM!                \n";
    cout << "-----------------------------------------------\n";
    cout<< "                       created by Alireza rezaei\n";
    cout<<"                              std id : 610303148\n";
    return;
}



// lists_deleter Function
void lists_deleter(){
    
    // storing records  
    store_students(); 
    store_teachers(); 
    store_Exam_codes();
    store_Exams();


    teacher_list->clear();
    delete teacher_list;
    
    
    student_list->clear();
    delete student_list;
    
    exam_codes->clear();
    delete exam_codes;

    created_Exams_list->clear();
    delete created_Exams_list;
    
    return;
}


// SignUP and Login Functions

void SignUP(vector<Teacher>& teachers, vector<Student>& students) {
    cout << endl << "\e[1;35m---- SignUp ----\033[0m" << endl;
    string role;
    cout << endl << "Choose your role (Teacher/Student): " << endl;
    getline(cin, role);
    lower(&role);
    if (role == "teacher") {
        Teacher* nxt = new Teacher;
        teachers.push_back(*nxt);
        cout << "\e[0;32m********* SignUp Completed for " << nxt->getname() << " *********\033[0m" << endl;
        store_teachers();     // this call is added
        nxt->Options();
    } 
    else if (role == "student") {
        Student* nxt = new Student;
        students.push_back(*nxt);
        store_students();     // this call is added
        cout << "\e[0;32m********* SignUp Completed for " << nxt->getname() << " *********\033[0m" << endl;
        Menu();
    }
    else{
        cout<<"\033[31m<< invalid command >>\033[0m"<<endl<<endl;
    }
    return;
}

void Login(vector<Teacher>& teachers, vector<Student>& students) {
    cout << endl << "\e[1;35m---- Login ----\033[0m" << endl;
    cout << "Enter your ID:" << endl;
    int flag = 0;
    while (flag == 0) {
        string id;
        getline(cin, id);
        string tmp = id;
        if (Check_logout_exit_command(tmp) == 1) {
            cout<<"Loging out..."<<endl;
            Menu();
            return;
        } else if (Check_logout_exit_command(tmp) == 2) {
            lists_deleter();
            exit(0);
        }
        lower(&id);
        if (Check_logout_exit_command(id) == 1) {
            Menu();
            return;
        } else if (Check_logout_exit_command(id) == 2) {
            lists_deleter();
            exit(0);
        }
        for (int i = 0; i < teachers.size(); i++) {
            if (teachers[i].getID() == id) {
                int pas_flag = 0;
                while (pas_flag == 0) {
                    cout << "Enter your password:" << endl;
                    string pas;
                    getline(cin, pas);
                    string tmp = pas;
                    if (Check_logout_exit_command(tmp) == 1) {
                        cout<<"Loging out..."<<endl;
                        Menu();
                        return;
                    } else if (Check_logout_exit_command(tmp) == 2) {
                        lists_deleter();
                        exit(0);
                    }
                    if (teachers[i].check_Pass(pas)) {
                        cout << endl << "Welcome " << teachers[i].getname() << " ..." << endl << endl;
                        teachers[i].Login();
                        pas_flag = 1;
                        teachers[i].Options();
                        flag = 1;
                        return;
                    } else {
                        cout << "\e[0;31m< Wrong Password >\e[0;31m" << endl << "\e[0;33mTry again\033[0m" << endl;
                    }
                }
            }
        }
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getID() == id) {
                int pas_flag = 0;
                while (pas_flag == 0) {
                    cout << "Enter your password:" << endl;
                    string pas;
                    getline(cin, pas);
                    string tmp = pas;
                    if (Check_logout_exit_command(tmp) == 1) {
                        cout<<"Loging out..."<<endl;
                        Menu();
                        return;
                    } else if (Check_logout_exit_command(tmp) == 2) {
                        lists_deleter();
                        exit(0);
                    }
                    if (students[i].check_Pass(pas)) {
                        cout << endl << "Welcome " << students[i].getname() << " ..." << endl << endl;
                        students[i].Login();
                        pas_flag = 1;
                        students[i].Options();
                        flag = 1;
                        return;
                    } else {
                        cout << "\e[0;31m< Wrong Password >\e[0;31m" << endl << "\e[0;33mTry again\033[0m" << endl;
                    }
                }
            }
        }
        if (flag == 0) {
            cout << "\e[0;31m< This ID does not exist >\e[0;31m" << endl << "\e[0;33mEnter new ID:\033[0m" << endl;
        }
    }
}



//Main menu of the program :

void Menu()
{
    while(1)
    {
        extern vector<Student>* student_list;
        extern vector<Teacher>* teacher_list;
        cout <<endl<<"\e[0;36m ------- Menu --------\033[0m"<<endl;
        cout<<"\e[0;36m|\033[0m \e[0;94m1-\e[0;36m \e[1;34mSignUp\e[0;36m           \e[0;36m|\033[0m"<<endl;
        cout<<"\e[0;36m|\033[0m \e[0;94m2-\e[0;36m \e[1;34mLogin\e[0;36m            \e[0;36m|\033[0m"<<endl;
        cout<<"\e[0;36m|\033[0m \e[0;94m3-\e[0;36m \e[0;31mExit\e[0;36m             \e[0;36m|\033[0m"<<endl;
        cout<<" \e[0;36m---------------------\033[0m"<<endl;
        cout<<"Enter command:"<<endl;
        string cmd; getline(cin,cmd); lower(&cmd);
        if(cmd=="signup")
        {
            SignUP(*teacher_list, *student_list);
        }
        else if(cmd=="login")
        {
            Login(*teacher_list, *student_list);
        }
        else if(cmd=="exit")
        {
            lists_deleter();
            exit(0);
        }
        else{
            cout<<"\033[31m<< invalid command >>\033[0m"<<endl<<endl;
        }
    }
    return ; 
}


//string to number turner function 
double String_to_number(string str){
    double num=0;
    for(int i=0;i<str.size();i++){
        num*=10;
        num+=str.at(i)-'0';
    }
    return num;
}




//this function take the secs and print the clock 

void Clock_displayer(int time) {
    
    int hr = time / 3600;  
    time %= 3600;                
    int min = time / 60;   
    int sec = time % 60;   

    cout << setw(2) << setfill('0') << hr << ":"                   
         << setw(2) << setfill('0') << min << ":"
         << setw(2) << setfill('0') << sec << endl;
    return;
}
/*
set make sure we have at least two digit
setfill fill the empty space with 0

*/


double time_counter(std::chrono::system_clock::time_point start) {
    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> time_past = now - start;
    return time_past.count();  
}

int exam_code_constructor() {
    string filename = "used_examCodes.txt";
    int last_number = 0;
    string line;
    ifstream infile(filename);
    if (infile.is_open()) {
        while (getline(infile, line)) {
            if (!line.empty()) {
                    last_number = stoi(line);
            }
        }
        infile.close();
    }

    int new_number = last_number + 1;
    ofstream outfile(filename, ios::app);  
    if (outfile.is_open()) {
        outfile << new_number <<endl;
        outfile.close();
    } else {
        cout << "Error: Could not open file for writing" << endl;
    }

    return new_number;
}


bool Valid_ID(string id){
    bool valid = true;
    for(auto student : *student_list){
        if(student.getID()==id){
            valid=false;
            break;
        }
    }
    if(valid==true){
        for(auto teacher : *teacher_list){
            if(teacher.getID()==id){
                valid=false;
                break;
            }
        }
    }
    return valid;
}



vector<int> getRandomSortedArray() {
    vector<int> arr = {1, 2, 3, 4};
    // Initialize random number generator with time-based seed
    random_device rd;
    mt19937 g(rd());
    // Shuffle the array
    shuffle(arr.begin(), arr.end(), g);
    return arr;
}



Question json_to_Question(json j_question){
        Question question("tmp");
        question.type = j_question["type"];
        question.question_body= j_question["question_body"];
        for(int i=0;i<4;i++){
            question.Options [i]= j_question["Options"].at(i);
        }
        question.Answer = j_question["Answer"];
        question.Positive_effect = j_question["Positive_effect"];
        question.Negative_effect =  j_question["Negative_effect"]; 

        return question;   

}
string FindExamName(string code){
    for(auto exam : *created_Exams_list){
        if(exam.Code==code){
            return exam.Name;
        }
    }
    return "notfind";
}





void Change_question_score(string Exam_code,string std_id,double prev_score,double max,string question,string answer){
    for(auto &std : *student_list){
        if(std.getID()==std_id){
            for(auto &score :std.scores){
                if(score.exam_code==Exam_code){
                    bool flag = false;
                    while(!flag){
                        cout<<"Enter New Score : ";
                        double scr ;  cin >> scr; cin.ignore();
                        if(scr<=max&&scr>0){
                            flag =true;
                            score.score-=prev_score;
                            score.score+=scr;

                            
                            //changing the student rpeort card :
                            for(int i=0;i<std.Scores_table.questions.size();i++){
                                if(std.Scores_table.questions.at(i)==question){
                                    std.Scores_table.scores.at(i)=scr;
                                    std.Scores_table.Student_Answers.at(i)="--Approved--";
                                    break;
                                }
                            }

                       }
                       else if(scr<=0){
                            flag =true;
                            score.score-=prev_score;
                            score.score+=scr;

                        
                            //changing the student rpeort card :
                            for(int i=0;i<std.Scores_table.questions.size();i++){
                                if(std.Scores_table.questions.at(i)==question){
                                    std.Scores_table.scores.at(i)=scr;
                                    std.Scores_table.Student_Answers.at(i)="--Wrong answer--";
                                    break;
                            }
                        }
                       }
                       else{
                        cout<<"\e[0;33mMaximum valid score for this Question is \e[0;36m"<<max<<"\033[0m "<<endl;
                       }
                }
                    
                }
            }
        }
    }
    return;


}
