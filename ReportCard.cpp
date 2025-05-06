#include"Header.hpp"



void ReportCard::display() {
    if (questions.empty()) {
        cout << "No exam results to display.\n";
        return;
    }

    // Header
    cout << "\nLine No.  Question          Student Answer    Correct Answer    Result      Score\n";
    cout << "---------------------------------------------------------------------------------\n";

    for (int  i = 0; i < questions.size(); ++i) {
        string result = "[SKIPPED]";
        string color_code = "";
        double score = 0.0;

        if (i < Student_Answers.size() && i < Correct_Answers.size()) {
            if (Student_Answers[i] == Correct_Answers[i]) {
                color_code = "\033[32m"; 
                result = "CORRECT";
            } else {
                color_code = "\033[31m"; 
                result = "WRONG  ";
            }
        }

        if (i < scores.size()) {
            score = scores[i];
        }

        // Print with score column
        printf("%-8d  %-16.16s  %-16.16s  %-16.16s  %s%s \033[0m %7.2f\n",
               static_cast<int>(i + 1),
               questions[i].c_str(),
               (i < Student_Answers.size()) ? Student_Answers[i].c_str() : "N/A",
               (i < Correct_Answers.size()) ? Correct_Answers[i].c_str() : "N/A",
               color_code.c_str(),
               result.c_str(),
               score);
    }
}
   
