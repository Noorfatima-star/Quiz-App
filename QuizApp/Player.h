#ifndef PLAYER_H
#define PLAYER_H

#endif // PLAYER_H

#include <string>
#include <iostream>
using namespace std;
class player {

private :

    string name ;
    int score;

public:

    player () {
        name = " ";
        score = 0;
    }
    player (string n , int s) {
        name = n;
        score = s;
    }

    void addScore() {
        score++;
    }

    void displayResult() {
        cout << "Player: " << name << endl;
        cout << "Score: " << score << endl;
    }

    int getScore() {
        return score;
    }

};
