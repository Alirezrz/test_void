#include"Header.hpp"


// Person Methods-----
//                    |
//                    |
//                    |
//                    V

Person::Person() {
    ID = "uninitialized";
    Password = "uninitialized";
}

Person::~Person() {
    status = out;
}

void Person::setName() {
    cout << "Enter your name:" << endl;
    getline(cin, Name);
    trim(&Name);
    string tmp = Name;
    if (Check_logout_exit_command(tmp) == 1) {
        Logout();
        return;
    } else if (Check_logout_exit_command(tmp) == 2) {
        lists_deleter();
        exit(0);
    }
    return;
}

void Person::setPass() {
    cout << "Enter your password:" << endl;
    cout << "(including letters/numbers/space/...)" << endl;
    string tmp1;
    getline(cin, tmp1);
    string tmp = tmp1;
    if (Check_logout_exit_command(tmp) == 1) {
        Logout();
        return;
    } else if (Check_logout_exit_command(tmp) == 2) {
        lists_deleter();
        exit(0);
    }
    int flag = 0;
    cout << "Confirm your password:\n(enter password)" << endl;
    while (flag == 0) {
        string tmp2;
        getline(cin, tmp2);
        string tmp = tmp2;
        if (Check_logout_exit_command(tmp) == 1) {
            Logout();
            return;
        } else if (Check_logout_exit_command(tmp) == 2) {
            lists_deleter();
            exit(0);
        }
        if (tmp1 == tmp2) {
            this->Password = tmp1;
            flag = 1;
        } else {
            cout << "\033[31mWrong password!\033[31m" << endl << "\e[0;33mPlease enter your password correctly to confirm:\033[0m" << endl;
        }
    }
    return;
}

int Person::check_Pass(string pass) {
    if (pass == Password)
        return 1;
    else
        return 0;
}

void Person::setID(string id) {
    this->ID = id;
    fstream used_IDs;
    used_IDs.open("used_IDs.txt",ios::app);
    used_IDs<<endl<<id;
    used_IDs.close();
    number_of_IDs++;
    return;
}

void Person::Logout() {
    status = out;
    Menu();
    return;
}

void Person::Login() {
    status = in;
    return;
}