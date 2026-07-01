
#pragma once
#include <iostream>
#include <fstream>
#include "Question.h"
using namespace std;
class quiz
{
public :

    Question question [50];
    int tq;

    quiz () {
        tq = 0;
    }

    void loadQuestions(string filename) {
        ifstream file(filename);
        string line;

        while(tq < 50) {
            if(!getline(file, line)) break;
            question[tq].text = line;

            for(int i = 0; i < 4; i++) {
                getline(file, line);
                question[tq].options[i] = line;
            }

            getline(file, line);
            question[tq].correctAnswer = line[0];

            tq++;
            getline(file, line);
        }
        file.close();
    }

    void displayQuestion (int index) {
        cout << question[index].text << endl;
        cout << "A) " << question[index].options[0] << endl;
        cout << "B) " << question[index].options[1] << endl;
        cout << "C) " << question[index].options[2] << endl;
        cout << "D) " << question[index].options[3] << endl;
    }



};