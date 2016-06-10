/* 
 * File:   main.cpp
 * Author: Alex Grech IV
 *
 * Created on May 8, 2016, 4:33 PM
 */


#include <cstdlib>
#include <iostream>
#include <utility>
#include "Board.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include "Move.h"
#include "Player.h"

using namespace std;

/**
 * Displays instruction for the game
 */
void displayInstructions() {
    cout << endl << "Instructions:" << endl;
    cout << "The game is played by moving the player’s token across the board " << endl <<
            "while attacking the other token and defending against attacks." << endl;
    cout << "However, the player only has a limited number of actions." << endl;
    cout << "Each turn counts as one action." << endl;
    cout << "On a given turn, the player can choose to Move, Attack, or Defend." << endl;
    cout << "When performing any action, a direction must be specified " << endl <<
            "(North, South, East, or West)." << endl;
    cout << "A player can Move four times in each direction, " << endl <<
            "and Attack or Defend once in each direction." << endl;
    cout << "The goal is to land a single successful attack on the opposing token." << endl;
    cout << "Once an action is performed, it is removed from the list " << endl <<
            "of possible actions." << endl;
    cout << "Thus, if a North Attack misses its target, the player can " << endl <<
            "no longer Attack North and must maneuver " << endl <<
            "(using their limited moveset) to attack from another angle." << endl;
    cout << "To play, first enter your choice of (M)ove, (A)ttack, or (D)efend." << endl;
    cout << "Then, select a direction." << endl;
    cout << "The computer will make its choice, then all moves will be resolved." << endl;
    cout << "The resolution order is as follows: Movement, Defense, and Attacks." << endl;
    cout << "This means that it is possible to not only dodge out of an attack, " << endl <<
            "but to dodge into one." << endl;
    cout << "Try to predict your enemy’s movements!" << endl;
    cout << "Two tokens cannot occupy the same space, and cannot move " << endl <<
            "outside the bounds of the board." << endl;
    cout << "An action must be performed every turn, so players wishing " << endl <<
            "to remain in the same place must spend either an Attack or " << endl <<
            "Defend action to remain stationary." << endl;
    cout << endl;
}

/**
 * Gets the users choice for what to do
 * @return Whatever the player choses
 */
int getChoice() {
    //asks the player what to do
    cout << "What would you like to do?" << endl;
    cout << "1-Play, 2-Instructions, 0-Quit" << endl;
    //gets players choice
    int choice;
    cin >> choice;
    //makes sure its a valid choice
    while (choice < 0 || choice > 2) {
        cout << "Invalid Choice" << endl;
        cout << "1-Play, 2-Instructions, 0-Quit" << endl;
        cin >> choice;
    }
    //returns the choice
    return choice;
}

/**
 * Plays the game
 * @return 
 */
int play() {
    //assume game is not over
    bool endGame = false;
    //create thee players
    HumanPlayer pc;
    ComputerPlayer npc;
    //create the board
    Board board(pc, npc);
    //play
    while (!endGame) {
        //print out board
        board.print();
        //move the players
        board.movePlayers();
        //check if any player is out of moves
        if(pc.outOfMoves() || npc.outOfMoves()) {
            board.print();
            endGame = true;
            cout << "Stalemate: a player ran out of moves" << endl;
        }
        //check if player won
        if(board.isCompDead()) {
            board.print();
            endGame = true;
            cout << "You win! Congratulations!" << endl;
        }
        //check if player lost
        if (board.isHumanDead()) {
            board.print();
            endGame = true;
            cout << "You lose... Better luck next time";
        }
    }
}

/*
 * Gets the players choice on what to do
 */
int main(int argc, char** argv) {
    cout << "Welcome!" << endl << endl;
    int choice = -1;
    //quit if choice is 0
    while (choice != 0) {
        //get player coice
        choice = getChoice();
        //execut that choice
        switch (choice) {
            case 1: 
                play();
                cout << "Play again?";
                break;
            case 2: displayInstructions();
                break;
        }
    }
}