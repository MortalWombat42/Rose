/* 
 * File:   Board.cpp
 * Author: Alex Grech IV
 * 
 * Created on May 8, 2016, 4:56 PM
 */

#include <cstdlib>
#include <iostream>
#include "Board.h"

using namespace std;

/**
 * Creates an array of null pointers to players, then places the given player
 * and computer at (1,1) and (2,2), respectively.
 * @param pc Human player
 * @param npc Computer player
 */
Board::Board(HumanPlayer& pc, ComputerPlayer& npc) : player_(pc), comp_(npc) {
    //fill board with null pointers
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board_[i][j] = NULL;
        }
    }
    //set player positions
    board_[1][1] = &player_;
    board_[2][2] = &comp_;
}

/**
 * Destructor
 */
Board::~Board() {
}

/**
 * Prints out the board
 */
void Board::print() {
    cout << endl << endl;
    cout << "      N" << endl;
    for (int i = 0; i < 4; i++) {
        if (i == 2) cout << "W  ";
        else cout << "   ";
        for (int j = 0; j < 4; j++) {
            if (!board_[i][j]) cout << '_';
            else {
                char c;
                if (board_[i][j]->isHuman()) c = 'X';
                else c = 'O';
                cout << c;
            }
            cout << ' ';
        }
        if (i == 2) cout << " E";
        cout << endl;
    }
    cout << "      S" << endl;
}

/**
 * Finds and returns the location of the computer
 * @return 
 */
pair<int, int> Board::compLoc() {
    int k, l;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board_[i][j]) {
                if (!board_[i][j]->isHuman()) {
                    k = i;
                    l = j;
                }
            }
        }
    }
    std::pair<int, int> loc(k, l);
    return loc;
}

/**
 * Finds and returns the location of the human
 * @return 
 */
pair<int, int> Board::humanLoc() {
    int k, l;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board_[i][j]) {
                if (board_[i][j]->isHuman()) {
                    k = i;
                    l = j;
                }
            }
        }
    }
    pair<int, int> loc(k, l);
    return loc;
}

/**
 * Checks if the computer is dead
 * @return 
 */
bool Board::isCompDead() {
    return comp_.isDead();
}

/**
 * Checks if the human is dead
 * @return 
 */
bool Board::isHumanDead() {
    return player_.isDead();
}

/**
 * Moves the players
 */
void Board::movePlayers() {
    //Moves of the players
    Move m1, m2;
    //locations of the players
    int i1, j1, i2, j2;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            //if there's something at (i,j)
            if (board_[i][j]) {
                //get the move for that player
                Move m = board_[i][j]->getMove(compLoc(), humanLoc());
                //decrement the move for  that player
                board_[i][j]->move(m);
                //sets the human to m1,i1,j1 and the computer to m2,i2,j2
                if (board_[i][j]->isHuman()) {
                    m1 = m;
                    i1 = i;
                    j1 = j;
                } else {
                    m2 = m;
                    i2 = i;
                    j2 = j;
                }
            }
        }
    }
    //prints out the moves
    cout << "Player: " << m1.first() << ' ' << m1.second() << endl;
    cout << "Computer: " << m2.first() << ' ' << m2.second() << endl;
    //checks if the moves are of the same type
    if (m1.first() == m2.first()) {
        //resolve them at the same time
        resolve(m1,i1,j1,m2,i2,j2);
        return;
    }
    //resolve them in order 'M','A','D'
    if (m1.first() == 'M') resolve(m1,i1,j1);
    if (m2.first() == 'M') resolve(m2,i2,j2);
    if (m1.first() == 'A') resolve(m1,i1,j1);
    if (m2.first() == 'A') resolve(m2,i2,j2);
    if (m1.first() == 'D') resolve(m1,i1,j1);
    if (m2.first() == 'D') resolve(m2,i2,j2);
    
}

/**
 * Resolves the given move from the given position
 * @param m Move to be executed
 * @param i Location of player
 * @param j "   "   "   "   "
 */
void Board::resolve(Move m, int i, int j) {
    //check move type
    switch(m.first()) {
        //if moving
        case 'M':
            //check direction
            switch (m.second()) {
                //move accordingly
                case 'N':
                    board_[i-1][j] = board_[i][j];
                    board_[i][j] = NULL;
                    return;
                case 'E':
                    board_[i][j+1] = board_[i][j];
                    board_[i][j] = NULL;
                    return;
                case 'S':
                    board_[i+1][j] = board_[i][j];
                    board_[i][j] = NULL;
                    return;
                case 'W':
                    board_[i][j-1] = board_[i][j];
                    board_[i][j] = NULL;
                    return;
            }
        //if attacking
        case 'A':
            //attack in the right direction
            switch (m.second()) {
                case 'N':
                    if(board_[i-1][j]) board_[i-1][j]->kill();
                    return;
                case 'E':
                    if(board_[i][j+1]) board_[i][j+1]->kill();
                    return;
                case 'S':
                    if(board_[i+1][j]) board_[i+1][j]->kill();
                    return;
                case 'W':
                    if(board_[i][j-1]) board_[i][j-1]->kill();
                    return;
            }
        //if defending
        case 'D':
            //revive if other player is in that direction
            switch (m.second()) {
                case 'N':
                    if(board_[i-1][j]) board_[i][j]->revive();
                    return;
                case 'E':
                    if(board_[i][j+1]) board_[i][j]->revive();
                    return;
                case 'S':
                    if(board_[i+1][j]) board_[i][j]->revive();
                    return;
                case 'W':
                    if(board_[i][j-1]) board_[i][j]->revive();
                    return;
            }
    }
}

/**
 * Resolves 2 moves at once if both are the same
 * @param m1 Move of one player
 * @param i1 Location of that player
 * @param j1 "  "   "   "   "   "   "
 * @param m2 Move of other player
 * @param i2 Location of other player
 * @param j2 "  "   "   "   "   "   "
 */
void Board::resolve(Move m1, int i1, int j1, Move m2, int i2, int j2) {
    //new locations depending on direction of moves
    int newI1 = i1;
    int newJ1 = j1;
    int newI2 = i2;
    int newJ2 = j2;
    switch (m1.second()) {
        case 'N': newI1--; break;
        case 'E': newJ1++; break;
        case 'S': newI1++; break;
        case 'W': newJ1--; break;
    }
    switch (m2.second()) {
        case 'N': newI2--; break;
        case 'E': newJ2++; break;
        case 'S': newI2++; break;
        case 'W': newJ2--; break;
    }
    //if both players are moving to the same place
    if (m1.first() == 'M' && m2.first() == 'M' && newI1 == newI2 
            && newJ1 == newJ2) return;
    //if both players are attacking each other
    if (m1.first() == 'A' && m2.first() == 'A' && newI1 == i2 && newJ1 == j2 
            && newI2 == i1 && newJ2 == j1) return;
    //if there aren't any conflicts
    resolve(m1,i1,j1);
    resolve(m2,i2,j2);
}