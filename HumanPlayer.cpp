/* 
 * File:   HumanPlayer.cpp
 * Author: Alex Grech IV
 * 
 * Created on May 8, 2016, 5:24 PM
 */

#include <cctype>
#include <iostream>
#include "HumanPlayer.h"
#include "Move.h"

using namespace std;

/**
 * Create the human player and tell the base class that it is human
 */
HumanPlayer::HumanPlayer() : Player(true) {
}

/**
 * Gets move from the human player and makes sure it is a valid move
 * @param compLoc Location of computer player to use in checkObstacle
 * @param humLoc Location of human player to use in checkObstacle
 * @return 
 */
Move HumanPlayer::getMove(pair<int, int> compLoc, pair<int, int> humLoc) {
    char type, dir;
    bool validOption;
    do {
        //assume player gives a valid move
        validOption = true;
        //ask player for move type
        cout << "Options: (M)ove, (A)ttack, (D)efend" << endl;
        cout << "Enter Choice:" << endl;
        //get move type from player
        cin >> type;
        //make it capital
        type = toupper(type);
        //make sure it is a valid move type
        while (type != 'M' && type != 'A' && type != 'D') {
            cout << "Invalid choice, try again" << endl;
            cout << "Options: (M)ove, (A)ttack, (D)efend" << endl;
            cout << "Enter Choice:" << endl;
            cin >> type;
            type = toupper(type);
        }
        //ask player for direction
        cout << "Choose direction: (N,E,S,W)" << endl;
        //get direction from player
        cin >> dir;
        ////make it capital
        dir = toupper(dir);
        //// make sure it is valid direction
        while (dir != 'N' && dir != 'E' && dir != 'S' && dir != 'W') {
            cout << "Invalid direction, try again" << endl;
            cout << "Choose direction: (N,S,E,W)" << endl;
            cin >> dir;
            dir = toupper(dir);
        }
        //checks if the player has that move left
        if (!canMove(Move(type, dir))) {
            validOption = false;
            cout << "No remaining moves of that kind in that direction" << endl;
        }
        //checks for obssacles
        if (!checkObstacle(humLoc, compLoc, Move(type, dir))) {
            validOption = false;
            cout << "Something is in the way" << endl;
        }
        if (!validOption) cout << "Try again" << endl;
        //check if it was a valid option
    } while (!validOption);
    //return the chosen move
    return Move(type,dir);
}