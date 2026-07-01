#ifndef QUESTION_H
#define QUESTION_H


#include <string>
using namespace std;

class Question {
public:
    string text;
    string options[4];
    char correctAnswer;

    Question() {
        text = "";
        correctAnswer = ' ';
        for(int i = 0; i < 4; i++) {
            options[i] = "";
        }
    }

    Question(string q, string o[], char c) {
        text = q;
        correctAnswer = c;
        for(int i = 0; i < 4; i++) {
            options[i] = o[i];
        }
    }

    Question(const Question& q) {
        text = q.text;
        correctAnswer = q.correctAnswer;
        for(int i = 0; i < 4; i++) {
            options[i] = q.options[i];
        }
    }

    bool operator==(const Question& q) {
        return text == q.text;
    }
};
#endif // QUESTION_H