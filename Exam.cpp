#include"Header.hpp"


// Exam Methods--------
//                    |
//                    |
//                    |
//                    V



int Exam::max_code = exam_code_constructor();
Exam::Exam()
{
    cout<<"What is name of the exam ?"<<endl;
    getline(cin,Name);
    max_code++;
    Code=to_string(max_code);
    Question *first_question=new Question(Code);
    Questions.push_back(*first_question);
    delete first_question;
    cout<<endl<<"\e[47m\e[4;34m Exam code = "<<Code<<" \033[0m	"<<endl; 
    number_of_Questions=0; 
    this->time=0;
    this->set_time();
}
Exam::~Exam(){
    
}

void Exam::Add(){
    Question *nxtQ = new Question();
    this->Questions.push_back(*nxtQ);
    delete nxtQ;
    number_of_Questions++;
    return;
    
}  

void Exam::Remove(){
    cout << "\e[0;36mEnter the number of question you want to remove : \033[0m"<<endl;
    int index;
    cin>>index;
    cin.ignore();
    if (index <= 0 || index >= Questions.size()) {
        cout << "\033[31mThere is no question with this number!\033[0m" << endl;
        return;
    }
    
    Questions.erase(Questions.begin()+index);
    cout<<"Question number "<<index<<" \033[31mremoved\033[0m"<<endl;
    number_of_Questions--;
    return;
}

void Exam::Show_to_teacher(){
    cout<< "\e[1;36m--- "<<Name<<" ---      \033[0m"<<"          \e[1;36m_ number of questions= "<<number_of_Questions<<" _\033[0m"<<endl;
    cout<<"\e[1;36mTime limit : ";
    Clock_displayer(this->time);
    cout<<"\033[0m"<<endl;
    for(int i=1;i<Questions.size();i++){
       Questions.at(i).display_to_teacher();
    }
    cout<< endl<<"\e[1;36m------------------\033[0m"<<endl<<endl;
    return;
}
void Exam::Show_to_student(){
    cout<< "\e[1;36m--- "<<Name<<" ---      \033[0m"<<"          \e[1;36m_ number of questions= "<<number_of_Questions<<" _\033[0m"<<endl;
    cout<<"\e[1;36mTime limit : ";
    Clock_displayer(this->time);
    cout<<"\033[0m"<<endl;
    for(int i=1;i<Questions.size();i++){
       Questions.at(i).display_to_student();
    }
    cout<< endl<<"\e[1;36m------------------\033[0m"<<endl<<endl;
    return;
}



// Exam Execution Function
student_score Exam::Execution(ReportCard& sheet,string name){
    this->Attended_students.push_back(name);
    sheet.Exams_Codes.push_back(this->Code);
    double Sigma_PosititveScores=0;
    double Positive=0;
    double negative=0;
    cout << "\e[0;36m---- " << Name << " ----\033[0m" << endl;
    cout << "\e[4;33mTime limit: \033[0m";
    Clock_displayer(time);  
    cout << "\e[4;33mTeacher:\033[0m " << designer << endl;
    cout << "\e[4;33mQuestions:\033[0m " << number_of_Questions << endl << endl;
    cout << "Press Enter to start the exam..." << endl;
    string dummy;
    getline(cin, dummy);  
    auto start_time = chrono::system_clock::now();
    double past_time = 0;
    for (int i = 0; i < Questions.size(); i++) {
        past_time = time_counter(start_time);
        if (past_time >= time) {
            cout << "\n\e[0;31mTime's up!\033[0m\n";
            break;
        }
        double remaining = time - past_time;
        cout << "\n\e[0;33mTime remaining: \033[0m";
        Clock_displayer(static_cast<int>(remaining));


        if(Questions.at(i).type=="Short"){
            this->Questions.at(i).display_to_student();  cout<<endl;
            cout << "Answer: ";
            string ans;
            getline(cin,ans);
            past_time = time_counter(start_time);
            if (past_time >= time) {
                cout << "\n\e[0;31mTime's up! This answer won't be counted.\033[0m\n";
                break;
            }
            if (ans == Questions.at(i).Answer) {
                Positive+=Questions.at(i).Positive_effect;
                sheet.scores.push_back(Questions.at(i).Positive_effect);
                sheet.short_scores_sigma+=Questions.at(i).Positive_effect;
            }
            else if(ans != Questions.at(i).Answer){
                negative +=Questions.at(i).Negative_effect;
                sheet.scores.push_back(Questions.at(i).Negative_effect);
                sheet.short_scores_sigma+=Questions.at(i).Negative_effect;
            }
            Sigma_PosititveScores+=Questions.at(i).Positive_effect;


            sheet.questions.push_back(Questions.at(i).question_body);
            sheet.Student_Answers.push_back(ans);
            sheet.Correct_Answers.push_back(Questions.at(i).Answer);
            
            
        }


        
        


        else if(Questions.at(i).type=="Test"){

            bool answered = false;
            int number;
            map <int,string> cases;
            while(!answered){
                Questions.at(i).display_to_student();
                cout<<endl;
                vector<int> shuffled = getRandomSortedArray();
                
                for(int j = 0; j < 4; j++){
                    cout << j+1 << ") " << Questions.at(i).Options[shuffled[j] - 1] << endl;
                    cases[j+1] = Questions.at(i).Options[shuffled[j] - 1];
                }
                cout<<"Enter number of your answer : ";
                cin>>number; cin.ignore();
                if(number>4 || number <1){
                    cout<<"\e[0;31m number is out of range.\033[0m"<<endl;
                }

                else{
                past_time = time_counter(start_time);
                if (past_time >= time) {
                    cout << "\n\e[0;31mTime's up! This answer won't be counted.\033[0m\n";
                    break;
                }

                if(cases[number]==Questions.at(i).Answer){
                    Positive+=Questions.at(i).Positive_effect;
                    sheet.test_scores_sigma+=Questions.at(i).Positive_effect;
                    sheet.scores.push_back(Questions.at(i).Positive_effect);
                }
                else{
                    negative += Questions.at(i).Negative_effect;
                    sheet.test_scores_sigma+=Questions.at(i).Negative_effect;
                    sheet.scores.push_back(Questions.at(i).Negative_effect);
                }
                answered =true;
               
            }

        }
        Sigma_PosititveScores+=Questions.at(i).Positive_effect;


        sheet.questions.push_back(Questions.at(i).question_body);
        sheet.Student_Answers.push_back(cases[number]);
        sheet.Correct_Answers.push_back(Questions.at(i).Answer);
    }

        else if(Questions.at(i).type=="Long"){
            Questions.at(i).display_to_student();
            cout << "Answer: ";
            string ans;
            getline(cin,ans);

            past_time = time_counter(start_time);
            if (past_time >= time) {
                cout << "\n\e[0;31mTime's up! This answer won't be counted.\033[0m\n";
                break;
            }


            if(ans==Questions.at(i).Answer){
                Positive += Questions.at(i).Positive_effect;
                sheet.scores.push_back(Questions.at(i).Positive_effect);
            }
            else{
                negative += Questions.at(i).Negative_effect;
                sheet.scores.push_back(Questions.at(i).Negative_effect);
            }
            Sigma_PosititveScores+=Questions.at(i).Positive_effect;
            
            sheet.questions.push_back( Questions.at(i).question_body);
            sheet.Student_Answers.push_back(ans);
            sheet.Correct_Answers.push_back(Questions.at(i).Answer);

        
        
        
        }
        


}





    double score = 0;   // this score is out of sigma all positive scores and we must turn it to 20 base |
    score += Positive;  //                                                                               |
    score +=negative;   //                                                                               |
    score = ((score * 20) / Sigma_PosititveScores);   //                                           <-----|   
    printf("\nFinal Score = %.2f\n", score);
    student_score scr;
    scr.set_score(score);
    scr.set_exam_code(Code);
    sheet.Exams_Scores.push_back(scr.get_score());
    
    
    double tmp=sheet.Average*sheet.attendence_number;
    sheet.attendence_number++;
    tmp+=score;
    sheet.Average=tmp/sheet.attendence_number;
    this->student_Grades.push_back(scr.get_score());
    
    return scr;
}
void Exam::set_time(){
    cout<<"Set the exam time :"<<endl;
    int hr,min,sec;
    cout<<"Hours : ";
    cin>>hr;
    cout<<"Minutes : ";
    cin>>min;
    cout<<"Seconds : ";
    cin>>sec;
    cin.ignore();
    this->time+=sec;
    this->time+=(min)*60;
    this->time+=(hr)*60*60;
    return;
}



json Exam :: Exam_to_json(){
    json exam;
    exam["designer"]=this->designer;
    exam["Code"] = this->Code;
    exam["participated_students"]= json ::array();
    for(auto student : this->participated_students){
        exam["participated_students"].push_back(student);
    }
    exam["Name"] = this->Name;
    exam["number_of_Questions"]=this->number_of_Questions;
    exam["time"] = this->time;
    exam["Questions"]= json ::array();
    for(auto question :this->Questions){
        exam["Questions"].push_back(question.Question_to_json());
    }

    exam["Attended_students"]= json::array();
    for(auto std : this->Attended_students){
        exam["Attended_students"].push_back(std);
    }
    exam["student_Grades"]= json ::array();
    for(auto grade : this->student_Grades){
        exam["student_Grades"].push_back(grade);
    }

    return exam;

}


Exam json_to_Exam(json j_exam){
    Exam new_exam(-1);
    new_exam.designer=j_exam["designer"];
    new_exam.Code=j_exam["Code"];
    if(j_exam.contains("participated_students")){
        for(auto student : j_exam["participated_students"]){
            new_exam.participated_students.push_back(student);
        }
    }
    new_exam.Name=j_exam["Name"];
    new_exam.number_of_Questions=j_exam["number_of_Questions"];
    new_exam.time=j_exam["time"];
    for(auto question : j_exam["Questions"]){
        new_exam.Questions.push_back(json_to_Question(question));
    }
    for(auto std: j_exam["Attended_students"]){
        new_exam.Attended_students.push_back(std);
    }
    for(auto grd: j_exam["student_Grades"]){
        new_exam.student_Grades.push_back(grd);
    }

    return new_exam;
}


void Load_Exams(){
    ifstream file("Exams.json");
    if(file.is_open()){
        json exams;
        file>>exams;
        for(auto exam : exams){
            Exam *new_exam= new Exam(-1);
            *new_exam=json_to_Exam(exam);
            created_Exams_list->push_back(*new_exam);
            delete new_exam;
        }
        file.close();
    }
    else {
        ofstream new_file("Exams.json");
        new_file << json::array().dump(4);
        new_file.close();
        cout << "Created new empty Exams.json" << endl;
    }

}

void store_Exams(){
    json exams = json :: array();
    for(auto & exam : *created_Exams_list){
        exams.push_back(exam.Exam_to_json());
    }

    ofstream file("Exams.json");
    if(file.is_open()){
        file << exams.dump(4);
        file.close();
    }
    else{
        cout<<"faild to open Exams.json"<<endl;
    }
}


void Exam::display_grades_to_teacher() {
    const string YELLOW = "\033[1;33m";
    const string CYAN = "\033[1;36m";
    const string BLUE = "\033[0;36m";
    const string GREEN = "\033[1;92m";
    const string UNDERLINE = "\033[4;36m";
    const string WHITE_BG = "\033[47m";
    const string RESET = "\033[0m";

    if (Attended_students.empty()) {
        cout << YELLOW << "  ---- No student has attended this exam ----" << RESET << endl;
        return;
    }

    // Sort students and grades together using bubble sort
    for (int step = 0; step < Attended_students.size(); step++) {
        for (int i = 0; i < Attended_students.size() - 1 - step; i++) {
            if (student_Grades[i] < student_Grades[i+1]) {
                swap(student_Grades[i], student_Grades[i+1]);
                swap(Attended_students[i], Attended_students[i+1]);
            }
        }
    }
    
    const string TXT_DIR = "Exams_results_txt_files";
    struct stat st;
    if(stat(TXT_DIR.c_str(), &st)==-1){  // checking if the directory exist or not
        #ifdef _WIN32  // Windows
            _mkdir(TXT_DIR.c_str());
        #else       // Mac and linux
            mkdir(TXT_DIR.c_str(),0755);
        #endif


    }



    string filename = TXT_DIR + "/" +this->Name +".txt";
    ofstream file(filename);

    // Header
    cout << WHITE_BG << BLUE << "\n  Sorted Grades Report - " << Name << RESET << "\n\n";
    cout << left << setw(25) << "Student Name" << "  Grade\n";
    cout << string(40, '-') << endl;

    // Body
    for (size_t i = 0; i < Attended_students.size(); i++) {
        cout << left << setw(25) << Attended_students[i] 
             << "  " << CYAN << fixed << setprecision(2) << student_Grades[i] << RESET << endl;
        
        file << left << setw(25) << Attended_students[i] 
             << "  Grade: " << fixed << setprecision(2) << student_Grades[i] << endl;
    }

    // Statistics
    double max_scr = student_Grades[0];  // Already sorted, first is max
    string max_name = Attended_students[0];
    double sigma = accumulate(student_Grades.begin(), student_Grades.end(), 0.0);
    double average = sigma / student_Grades.size();

    // Output statistics
    cout << "\n" << WHITE_BG << BLUE << "  Statistics:" << RESET << "\n";
    cout << string(40, '-') << "\n";
    cout << left << setw(25) << "Highest Grade:" << "  " << CYAN  << max_scr << RESET << endl;
    cout << UNDERLINE << left << setw(25) << "Class Average:" << "  " << fixed << setprecision(2) << average << RESET << "\n\n";

    // File output
    file << "\nStatistics:\n" << string(40, '-') << "\n";
    file << left << setw(25) << "Highest Grade:" << "  " << max_name << " (" << max_scr << ")\n";
    file << left << setw(25) << "Class Average:" << "  " << fixed << setprecision(2) << average << "\n";

    file.close();

    cout << RESET << "  Report saved to: " <<YELLOW<< filename << RESET << "\n\n";
}