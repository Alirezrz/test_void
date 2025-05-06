#include"Header.hpp"

// Student Methods-----
//                    |
//                    |
//                    |
//                    V

Student::Student() {
    this->setName();
    this->setField();
    cout << "Enter your ID: " << endl;
    int flag = 0;
    while (flag == 0) {
        string id;
        getline(cin, id);
        string tmp = Name;
        if (Check_logout_exit_command(tmp) == 1) {
            Logout();
            return;
        } else if (Check_logout_exit_command(tmp) == 2) {
            lists_deleter();
            exit(0);
        }
         // Ceking out the used ids for the  id to be unique
         
         
         if (Valid_ID(id)==true) {
             this->setID(id);
             flag = 1;
         } else {
             cout << "\033[31minvalid ID!\033[31m" << endl << "\e[0;33mPlease enter new ID:\033[0m" << endl;
         }
    }
    this->setPass();
}

Student::~Student() {
}

void Student::setField() {
    cout << "Enter your Field:" << endl;
    cin >> Field;
    string tmp = Name;
    if (Check_logout_exit_command(tmp) == 1) {
        Logout();
        return;
    } else if (Check_logout_exit_command(tmp) == 2) {
        lists_deleter();
        exit(0);
    }
    cin.ignore();
    return;
}
void Student::Show_personal_information(){
    cout << endl << "Name : " << this->Name << endl;
    cout << "ID : " << this->ID << endl;
    cout << "Field : " << this->Field << endl;
    return;
}

void Student::Change_Passsword(){
    cout << "Enter your current Password:" << endl;
    int flag = 0;
    while (flag == 0) {
        string pas;
        getline(cin, pas);
        string tmp = pas;
        if (Check_logout_exit_command(tmp) == 1) {
            cout<<"Loging out..."<<endl;
            Logout();
            Menu();
            return;
        } 
        else if (Check_logout_exit_command(tmp) == 2) {
            lists_deleter();
            exit(0);
        }
        if (this->check_Pass(pas)) {
            cout << "Enter your new Password :" << endl;
            string newpas;
            getline(cin, newpas);
            string tmp = newpas;
            if (Check_logout_exit_command(tmp) == 1) {
            cout<<"Loging out..."<<endl;
            Logout();
            Menu();
            return;
        } 
        else if (Check_logout_exit_command(tmp) == 2) {
            lists_deleter();
            exit(0);
        }
            int set_flag = 0;
            while (set_flag == 0) {
                cout << "Confirm your new Password:" << endl;
                string tmp;
                getline(cin, tmp);
                string tmp3 = tmp;
                if (Check_logout_exit_command(tmp3) == 1) {
                cout<<"Loging out..."<<endl;
                Logout();
                Menu();
                return;
                } 
                else if (Check_logout_exit_command(tmp3) == 2) {
                    lists_deleter();
                    exit(0);
                }
                if (tmp == newpas) {
                    flag = 1;
                    this->Password = newpas;
                    cout << "\e[0;32m***Password Updated Successfully ...***\033[0m" << endl;
                    this->Options();
                    set_flag = 1;
                } else {
                    cout << "\e[0;33mEnter your new Password correctly!\033[0m" << endl;
                }
            }
        } else {
            cout << "\e[0;31m<< Wrong Password >>\e[0;31m" << endl << "\e[0;33mtry again\033[0m" << endl;
        }
    }
    return;
}
void Student::Options() {
    cout << endl << " \e[0;36m------- Options -----------------------------\033[0m" << endl;
    cout << "\e[0;36m|\033[0m \e[0;94m1-\033[0m \e[1;34mLogout \033[0m                                  \e[0;36m|\033[0m" << endl;
    cout << "\e[0;36m|\033[0m \e[0;94m2-\033[0m \e[1;34mShow Personal information  \033[0m              \e[0;36m|\033[0m" << endl;
    cout << "\e[0;36m|\033[0m \e[0;94m3-\033[0m \e[1;34mChange Password          \033[0m                \e[0;36m|\033[0m" << endl;
    cout << "\e[0;36m|\033[0m \e[0;94m4-\033[0m \e[1;34mExams          \033[0m                          \e[0;36m|\033[0m" << endl;
    cout << "\e[0;36m|\033[0m \e[0;94m5-\033[0m \e[1;34mScore Sheet          \033[0m                    \e[0;36m|\033[0m" << endl;
    cout << " \e[0;36m---------------------------------------------\033[0m" << endl;
    cout << "Enter number of your command:" << endl;
    string cmd;
    getline(cin, cmd);
    lower(&cmd);
    string tmp = cmd;
    if (cmd == "exit") {
        lists_deleter();
        exit(0);
    } else if (cmd[0] == '1') {
        cout << "Good Bye " << Name << endl;
        store_students();
        Menu();
    } else if (cmd[0] == '2') {
       this->Show_personal_information();
        this->Options();
    } 
    else if (cmd[0] == '3') {
        this->Change_Passsword();
        this->Logout();
        Menu();
    }
    else if(cmd[0]=='4'){
        this->Exams();
    }
    else if(cmd[0]=='5'){
        this->Scores_table.display();
        cout<<endl;
        this->display_Average();
        int Rank = this->Rank_Computer();
        if(Rank!=0){
            cout<<endl<<"\e[0;36mYour rank is \e[1;34m"<<Rank<<"\033[0m"<<endl;
            this->Exam_Score_sheet_displayer();
            CSVHandler(*this);
        }
        else 
            cout<<endl<<"\e[0;36mYour rank is NAN (no scores yet)\e[1;34m"<<"\033[0m"<<endl;
        
        this->Options();
    }
    return;
}

void Student::Exams(){
    cout << endl << " \e[0;36m------- Exams options -----------------------------\033[0m" << endl;
    cout << "\e[0;36m\033[0m \e[0;94m1-\033[0m \e[1;34mParticipate \033[0m                                  \033[0m" << endl;
    cout << "\e[0;36m\033[0m \e[0;94m2-\033[0m \e[1;34mView list of participated exams  \033[0m              \033[0m" << endl;
    cout << "\e[0;36m\033[0m \e[0;94m3-\033[0m \e[1;34mAttend Exam  \033[0m              \033[0m" << endl;
    cout << "\e[0;36m\033[0m \e[0;94m4-\033[0m \e[1;34mView Scores Sheet  \033[0m              \033[0m" << endl;
    cout << "\e[0;36m\033[0m \e[0;94m5-\033[0m \e[0;31mreturn  \033[0m              \033[0m" << endl;
    cout << "Enter number of your command:" << endl;
    string cmd;
    getline(cin, cmd);
    if(cmd[0]=='1'){
        cout<<"\e[0;36mAvailable Exams:\033[0m"<<endl;
        for(int i=1;i<exam_codes->size();i++){
            cout<<"\e[0;36mCode : "<<exam_codes->at(i).get_code()<<"    \033[0m"<<endl;
        }
        cout<<"Enter the code you want to participate in:";
        string code;
        getline(cin,code);
        int flag=0;
        for(int i=0;i<participated_exams.size();i++){
            if(code==participated_exams.at(i)){
                cout<<"\e[0;33mYou have already participated in this exam\033[0m"<<endl<<endl;
                this->Exams();
                return;
            }
        }
        
        for(int i=0;i<exam_codes->size();i++){
            if(code==exam_codes->at(i).get_code()){
                this->participated_exams.push_back(code);
                exam_codes->at(i).participate_student(this->ID);
                cout<<"\e[0;32m*** Participation compeleted successfully***\033[0m"<<endl<<endl;
                flag=1;
                this->Exams();
                return;
            }
        }
        if(flag==0){
            cout<<"\e[0;33mNo Exam exist with this code\033[0m"<<endl<<endl;
            this->Exams();
            return;
        }
    }
    else if(cmd[0]=='2'){
        cout<<"\e[0;36mYour participated Exam codes list:\033[0m"<<endl<<endl;
        for(int i=0;i<this->participated_exams.size();i++){
            cout<<i+1<<". "<<participated_exams.at(i)<<endl;
        }
        this->Exams();
        return;
    }
    else if(cmd[0]=='3'){
        this->attend_exam();
        return;
    }
    else if(cmd[0]=='4'){
        for(int i=0;i<this->scores.size();i++){
            cout<<"\e[0;36mCode : " <<scores.at(i).exam_code;
            cout<<"\033[0m";
            if(scores.at(i).score>=15.0){
                cout<<"  \e[0;32mScore = ";
                printf("%.2f\n",scores.at(i).score);
                cout<<"\033[0m";
            }
            else if(scores.at(i).score<15.0&&scores.at(i).score>=10){
                cout<<"  \e[0;33mScore = ";
                printf("%.2f\n",scores.at(i).score);
                cout<<"\033[0m";
            }
            else{
                cout<<"  \e[0;31mScore = ";
                printf("%.2f\n",scores.at(i).score);
                cout<<"\033[0m";
            }
        }
        this->Exams();
        return;
    }
    
    
    else if(cmd[0]=='5'){
        this->Options();
        return;
    }
    else{
        cout<<"\e[0;33minvlaid number"<<endl<<endl;
        this->Exams();
        return;
    }
}
void Student::attend_exam(){
    cout<<"list of the exams you have participated:"<<endl;
    for(int i=0;i<participated_exams.size();i++){
        cout<<participated_exams.at(i)<<endl;
    }
    string code;
    cout<<"Enter the Code you want to attend :  ";
    getline(cin,code);
    for(int i=0;i<scores.size();i++){
        if(code==scores.at(i).exam_code){
            cout<<"\e[0;33m    You have attended this exam before\033[0m"<<endl<<endl;
            this->Exams();
            return;
        }
    }
    bool participated = false;
    for(int i=0;i<participated_exams.size();i++){
        if(code==participated_exams.at(i)){
            participated = true;
            break;
        }
    }
    if(!participated){
        cout<<"\e[0;33m    You haven't participated in this exam yet\033[0m"<<endl<<endl;
        this->Exams();
        return;
    }
    for(int i=0;i<created_Exams_list->size();i++){
        if(code == created_Exams_list->at(i).get_code()){
            student_score score = created_Exams_list->at(i).Execution(this->Scores_table,this -> Name);
            score.set_exam_code(code);
            this->Push_back_score(score);
            store_students();
            store_Exams();   // this call is added
            cout<<"\e[0;32m*** Exam completed successfully ***\033[0m"<<endl<<endl;
            this->Exams();
            return;
        }
    }
    
    cout<<"\e[0;33m    No exam found with this code\033[0m"<<endl<<endl;
    this->Exams();
}
void Student::Push_back_score(student_score scr){
    this->scores.push_back(scr);
    return;
}


// this mthod build a json type of student:
json Student::student_to_json(){
    json student;
    student["Name"]=this->Name;
    student["ID"]=this->ID;
    student["Password"]=this->Password;
    student["Field"]=this->Field;
    student["participated_exams"] = json::array();
    for(auto exam : this->participated_exams){
        student["participated_exams"].push_back(exam);
    }
    student["scores"] = json::array();
    for(auto score : this->scores){
        json exam_score;
        exam_score["exam_code"] = score.exam_code;
        exam_score["score"] = score.score;
        student["scores"].push_back(exam_score);
    }
    json table;
    table["questions"] = json::array();
    for(auto q : this->Scores_table.questions){

        table["questions"].push_back(q);
    }
    table["Student_Answers"] = json::array();
    for(auto ans : Scores_table.Student_Answers){
        table["Student_Answers"].push_back(ans);
    }
    table["Correct_Answers"] = json::array();
    for(auto ans : Scores_table.Correct_Answers){
        table["Correct_Answers"].push_back(ans);
    }

    table["scores"] = json ::array();
    for(auto scr:Scores_table.scores){
        table["scores"].push_back(scr);
    }

    

    table["short_scores_sigma"] = Scores_table.short_scores_sigma;
    table["test_scores_sigma"] = Scores_table.test_scores_sigma;
    student["Scores_table"] = table;
    return student;
}

//this function turn a json type student to a Student type
Student json_to_student(json j_student){
    Student tmp_student(-1);
    tmp_student.Name=j_student["Name"];
    tmp_student.Field=j_student["Field"];
    tmp_student.ID=j_student["ID"];
    tmp_student.Password=j_student["Password"];
    if(j_student.contains("participated_exams")){
        for(auto exam  : j_student["participated_exams"]){
            tmp_student.participated_exams.push_back(exam.get<string>());
        }

    }
    if(j_student.contains("scores")){
        for(auto json_score : j_student["scores"]){
            student_score scr;
            scr.exam_code=json_score.value("exam_code", "");//return empty if not found
            scr.score=json_score.value("score",0.0);//return 0.0 if not found
            tmp_student.scores.push_back(scr);
        }
    }


    ReportCard tmp_table;
    if(j_student.contains("Scores_table")){
        json table = j_student["Scores_table"];
        for(auto q : table["questions"]){
            tmp_table.questions.push_back(q);
        }

        for(auto ans :table["Student_Answers"]){
            tmp_table.Student_Answers.push_back(ans);
        }

        
        for(auto ans :table["Correct_Answers"]){
            tmp_table.Correct_Answers.push_back(ans);
        }

        for(auto scr :table["scores"]){
            tmp_table.scores.push_back(scr);
        }


        
        for (auto& ex_cd : table["Exams_Codes"]) {
            tmp_student.Scores_table.Exams_Codes.push_back(ex_cd);
        }

        tmp_table.short_scores_sigma = table["short_scores_sigma"];
        tmp_table.test_scores_sigma = table["test_scores_sigma"];

    }
    tmp_student.Scores_table=tmp_table;


    return tmp_student;
}

void Load_students(){
    ifstream file("students.json");
    if (file.is_open()) {
            json students;
            file >> students;
            for ( auto& student : students) {
                Student *new_student= new Student(-1);
                *new_student = json_to_student(student);
                student_list->push_back(*new_student);
                delete new_student;
            }
            file.close();
    }     
    else {
        ofstream new_file("students.json");
        new_file << json::array().dump(4);
        new_file.close();
        cout << "Created new empty students.json" << endl;
    }
}

void store_students() {
    json students = json::array();

    for ( auto& student : *student_list) {
        students.push_back(student.student_to_json());
    }

    ofstream file("students.json");
    if (file.is_open()) {
        file << students.dump(4);
        file.close();
    }
    else {
        cout << "Error: Failed to open students.json for writing!" << endl;
    }
}

double Student::Average_score(){
    double number=0;
    double sigma=0;
    for(int  i=0 ;i<this->scores.size();i++){
        number++;
        sigma += this->scores.at(i).score;
    }

    return sigma/number;
}

double Student::Max_score(){
    double max=this->scores[0].score;
    for(int i=0;i<this->scores.size();i++){
        if(max<this->scores[i].score){
            max = this->scores[i].score;
        }
    }

    return max;
}

int Student::Rank_Computer() {
    vector<double> averages;
    for (auto& s : *student_list) {
        if (s.scores.size() > 0) { 
            averages.push_back(s.Average_score());
        }
    }
    sort(averages.rbegin(), averages.rend());    

    double epsilon = 0.00001;
    double Current_average=this->Average_score();
    for(int i=0;i<averages.size();i++){
        if(fabs(Current_average-averages[i])<epsilon){
            return i+1;
        }
    }
    return 0; // if we have no scores we will get 0

}

void Student::display_Average(){
    double sum=0;
    double num=0;
    for(int i=0;i<this->scores.size();i++){
        sum+=this->scores.at(i).score;
        num++;
    }
    if(num!=0){
        cout<<"Your Average is : "<<sum/num<<endl;
        return;
    }
    else {
        cout<<"NO score"<<endl;
        return;

    }
}

void Student :: Exam_Score_sheet_displayer(){
    double max= this->scores[0].score;
    for(int i=0;i<this->scores.size();i++){
        if(this->scores[i].score>max){
            max=this->scores[i].score;
        }
        for(int j=0;j<35;j++)
            cout<<"--";
        cout<<endl;
        cout<<"\e[0;35mCode : \e[0;36m" <<scores.at(i).exam_code;
        cout<<"\033[0m\e[0;35m";
        cout<<"  Name : \e[0;36m"<<FindExamName(scores.at(i).exam_code);
        if(scores.at(i).score>=15.0){
            cout<<" \e[0;35m  Score = \e[0;32m";
            printf("%.2f\n",scores.at(i).score);
            cout<<"\033[0m";
        }
        else if(scores.at(i).score<15.0&&scores.at(i).score>=10){
            cout<<"   \e[0;35m  Score = \e[0;33m";
            printf("%.2f\n",scores.at(i).score);
            cout<<"\033[0m";
        }
        else{
            cout<<"  \e[0;35m  Score = \e[0;31m";
            printf("%.2f\n",scores.at(i).score);
            cout<<"\033[0m";
        }
    }
    for(int j=0;j<35;j++)
            cout<<"--";
    cout<<endl;
    cout<<"\e[1;33mMaximum Score = \e[1;36m"<<max<<"\033[0m"<<endl;
    cout<<endl;
    return;
}