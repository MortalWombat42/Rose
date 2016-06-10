/* 
 * File:   ComputerPlayer.cpp
 * Author: Alex Grech IV
 * 
 * Created on May 8, 2016, 7:09 PM
 */

#include <cstdlib>
#include <utility>
#include "ComputerPlayer.h"

using namespace std;

/**
 * Create computer player and tell base class that it is not human
 */
ComputerPlayer::ComputerPlayer() : Player(false) {
}

/**
 * Generates a move for the computer based on the location of the human player
 * @param compLoc Location for the computer player
 * @param humLoc Location for the human player
 * @return 
 */
Move ComputerPlayer::getMove(pair<int, int> compLoc, pair<int, int> humLoc) {
    //set move type and direction to ' ' to make sure it gets initialized
    char moveType = ' ';
    char moveDir = ' ';
    //get the distance and direction to the human player
    int distY = compLoc.first - humLoc.first;
    int distX = compLoc.second - humLoc.second;
    //If player is within 1 space in any direction
    if (abs(distX) <= 1 && abs(distY) <= 1) {
        //If player is adjacent and can attack
        if (distX * distY == 0 && canAttack()) {
            moveType = 'A';
            //If player is N of computer
            if (distY > 0 && canMove(Move('A', 'N')) && checkObstacle(compLoc, humLoc, Move('A', 'N'))) {
                moveDir = 'N';
            //If player is E of computer
            } else if (distX < 0 && canMove(Move('A', 'E')) && checkObstacle(compLoc, humLoc, Move('A', 'E'))) {
                moveDir = 'E';
            //If player is S of computer
            } else if (distY < 0 && canMove(Move('A', 'S')) && checkObstacle(compLoc, humLoc, Move('A', 'S'))) {
                moveDir = 'S';
            //If player is W of computer
            } else if (distX > 0 && canMove(Move('A', 'W')) && checkObstacle(compLoc, humLoc, Move('A', 'W'))) {
                moveDir = 'W';
            }
        } //If player is adjacent, can't attack, but can defend
        if (distX * distY == 0 && canDefend() && moveDir == ' ') {
            moveType = 'D';
            //If player is N of computer
            if (distY > 0 && canMove(Move('D', 'N')) && checkObstacle(compLoc, humLoc, Move('D', 'N'))) {
                moveDir = 'N';
            //If player is E of computer
            } else if (distX < 0 && canMove(Move('D', 'E')) && checkObstacle(compLoc, humLoc, Move('D', 'E'))) {
                moveDir = 'E';
            //If player is S of computer
            } else if (distY < 0 && canMove(Move('D', 'S')) && checkObstacle(compLoc, humLoc, Move('D', 'S'))) {
                moveDir = 'S';
            //If player is W of computer
            } else if (distX > 0 && canMove(Move('D', 'W')) && checkObstacle(compLoc, humLoc, Move('D', 'W'))) {
                moveDir = 'W';
            }
        }
    }//If computer couldn't attack or defend, try to move towards player
    if (moveDir == ' ') {
        moveType = 'M';
        //If player is N of computer and can move that direction
        if (distY > 0 && canMove(Move('M', 'N')) && checkObstacle(compLoc, humLoc, Move('M', 'N'))) {
            moveDir = 'N';
        //If player is E of computer and can move that direction
        } else if (distX < 0 && canMove(Move('M', 'E')) && checkObstacle(compLoc, humLoc, Move('M', 'E'))) {
            moveDir = 'E';
        //If player is S of computer and can move that direction
        } else if (distY < 0 && canMove(Move('M', 'S')) && checkObstacle(compLoc, humLoc, Move('M', 'S'))) {
            moveDir = 'S';
        //If player is W of computer and can move that direction
        } else if (distX > 0 && canMove(Move('M', 'W')) && checkObstacle(compLoc, humLoc, Move('M', 'W'))) {
            moveDir = 'W';
        }
    }//If still unable to come up with a move, go through all possible moves
    if (moveDir == ' ') {
        if (canMove(Move('M','N')) && checkObstacle(compLoc, humLoc, Move('M','N'))) {
            moveDir = 'N';
        } else if (canMove(Move('M','E')) && checkObstacle(compLoc, humLoc, Move('M','E'))) {
            moveDir = 'E';
        } else if (canMove(Move('M','S')) && checkObstacle(compLoc, humLoc, Move('M','S'))) {
            moveDir = 'S';
        } else if (canMove(Move('M','W')) && checkObstacle(compLoc, humLoc, Move('M','W'))) {
            moveDir = 'W';
        } else if (!moveDir && canAttack()) {
            moveType = 'A';
            if (canMove(Move('A','N')) && checkObstacle(compLoc, humLoc, Move('A','N'))) {
                moveDir = 'N';
            } else if (canMove(Move('A','E')) && checkObstacle(compLoc, humLoc, Move('A','E'))) {
                moveDir = 'E';
            } else if (canMove(Move('A','S')) && checkObstacle(compLoc, humLoc, Move('A','S'))) {
                moveDir = 'S';
            } else if (canMove(Move('A','W')) && checkObstacle(compLoc, humLoc, Move('A','W'))) {
                moveDir = 'W';
            } else if (!moveDir && canDefend()) {
                moveType = 'D';
                if (canMove(Move('D','N')) && checkObstacle(compLoc, humLoc, Move('D','N'))) {
                    moveDir = 'N';
                } else if (canMove(Move('D','E')) && checkObstacle(compLoc, humLoc, Move('D','E'))) {
                    moveDir = 'E';
                } else if (canMove(Move('D','S')) && checkObstacle(compLoc, humLoc, Move('D','S'))) {
                    moveDir = 'S';
                } else if (canMove(Move('D','W')) && checkObstacle(compLoc, humLoc, Move('D','W'))) {
                    moveDir = 'W';
                }
            }
        }
    }
    return Move(moveType, moveDir);
}