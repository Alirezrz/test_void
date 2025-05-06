#include"Header.hpp"



Question::Question(){
    cout<<"\e[1;35mChoose type of Question :(enter the number)"<<endl<<"1_Short Answer"<<endl<<"2_Test"<<endl<<"3_Long Answer\033[0m"<<endl;
    int type;   cin>>type;  cin.ignore();
    if(type == 1){
        this->type="Short";
        cout<<"Question body: ";
        string tmp; getline(cin,tmp); 
        this->question_body=tmp;
        cout<<"Answer : ";
        getline(cin,tmp); 
        this->Answer=tmp;
        cout<<"\e[0;32mCorrect answer score : \033[0m";
        double pos; cin>>pos; cin.ignore();
        cout<<"\033[31mWrong answer effect : \033[0m";
        double neg; cin>>neg; cin.ignore();
        this->Positive_effect=pos;
        this->Negative_effect=neg;
        for(int i=0;i<4;i++){
            this->Options[i]="---this Question is not a test---";
        }

    }
    else if(type == 2){
        this->type="Test";
        cout<<"Question body: ";
        string tmp; getline(cin,tmp); 
        this->question_body=tmp;
        cout<<"Enter the options :(4 choices for student)"<<endl;
        for(int i=0;i<4;i++){
            cout<<i+1<<"_";
            string ans;
            getline(cin,ans);
            this->Options[i]=ans;
        }
        cout<<"Answer : ";
        getline(cin,tmp); 
        this->Answer=tmp;
        cout<<"\e[0;32mCorrect answer score : \033[0m";
        double pos; cin>>pos; cin.ignore();
        cout<<"\033[31mWrong answer effect : \033[0m";
        double neg; cin>>neg; cin.ignore();
        this->Positive_effect=pos;
        this->Negative_effect=neg;

    }
    else if(type == 3){
        this->type="Long";
        cout<<"Question body: ";
        string tmp; getline(cin,tmp); 
        this->question_body=tmp;
        cout<<"Answer : ";
        getline(cin,tmp); 
        this->Answer=tmp;
        for(int i=0;i<4;i++){
            this->Options[i]="---this Question is not a test---";
        }
        cout<<"\e[0;32mCorrect answer score : \033[0m";
        double pos; cin>>pos; cin.ignore();
        this->Positive_effect=pos;
        this->Negative_effect=0;
    }

}

void Question::display_to_teacher(){
    if(this->type=="Short"){
        cout<<this->question_body<<endl;
        cout<<"Answer = "<<this->Answer<<endl;
        cout<<"\e[0;32mCorrect answer score : \033[0m" <<this->Positive_effect<<endl;
        cout<<"\033[31mWrong answer effect : \033[0m"<<this->Negative_effect<<endl;
        return;
    }
    else if(this->type=="Test"){
        cout<<this->question_body<<endl;
        cout<<"Student options :"<<endl;
        for(int i=0;i<4;i++){
            if(this->Options[i]==Answer){
                cout<<i+1<<"_\e[0;32m"<<Options[i]<<"\033[0m"<<endl;
            }
            else{
                cout<<i+1<<"_\033[31m"<<Options[i]<<"\033[0m"<<endl;
            }
        }
        cout<<"\e[0;32mCorrect answer score : \033[0m" <<this->Positive_effect<<endl;
        cout<<"\033[31mWrong answer effect : \033[0m"<<this->Negative_effect<<endl;
        return;

    }
    else if(this->type=="Long"){
        cout<<question_body<<endl;
        cout<<"Answer = "<<Answer<<endl;
        cout<<"\e[0;32mCorrect answer score : \033[0m" <<this->Positive_effect<<endl;
        return;
    }
}

void Question::display_to_student(){
    if(this->type=="Short"){
        cout<<this->question_body<<endl;
        return;
    }
    else if(this->type=="Test"){
        cout<<this->question_body<<endl;
        return;

    }
    else if(this->type=="Long"){
        cout<<question_body<<endl;
        return;
    }
} 



json Question::Question_to_json(){
        json j_question;
        j_question["type"] = this->type;
        j_question["question_body"] = this->question_body;
        j_question["Options"] = json :: array();
        for(int i=0;i<4;i++){
            j_question["Options"].push_back(this->Options[i]);
        }
        j_question["Answer"] = this->Answer;
        j_question["Positive_effect"] = this -> Positive_effect;
        j_question["Negative_effect"] = this-> Negative_effect;

        return j_question;

}