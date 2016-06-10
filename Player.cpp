/* 
 * File:   Player.cpp
 * Author: Alex Grech IV
 * 
 * Created on May 8, 2016, 4:34 PM
 */

#include <utility>
#include "Player.h"

using namespace std;

/**
 * Create the player and initialize all the moves
 * @param isHuman Tells whether the player is human
 */
Player::Player(bool isHuman) : numMovesN_(4), numMovesE_(4), numMovesS_(4), numMovesW_(4),
attackN_(true), attackE_(true), attackS_(true), attackW_(true),
defendN_(true), defendE_(true), defendS_(true), defendW_(true),
isHuman_(isHuman), isDead_(false) {
}

/**
 * Returns true if the player has any attacking moves left
 * @return 
 */
bool Player::canAttack() {
    return (attackN_ || attackE_ || attackS_ || attackW_);
}
/**
 * Returns true if the player has any defending moves left
 * @return 
 */
bool Player::canDefend() {
    return (defendN_ || defendE_ || defendS_ || defendW_);
}

/**
 * Determines if the player can complete a specified move based on 
 * the remaining moves of the player
 * @param m
 * @return 
 */
bool Player::canMove(Move m) {
    //get move type and direction
    char moveType = m.first();
    char moveDir = m.second();
    //checks move type
    switch (moveType) {
        case 'M':
            //checks move direction
            switch (moveDir) {
                //checks remaining moves
                case 'N': return (numMovesN_ > 0);
                case 'E': return (numMovesE_ > 0);
                case 'S': return (numMovesS_ > 0);
                case 'W': return (numMovesW_ > 0);
            }
        case 'A':
            switch (moveDir) {
                case 'N': return attackN_;
                case 'E': return attackE_;
                case 'S': return attackS_;
                case 'W': return attackW_;
            }
        case 'D':
            switch (moveDir) {
                case 'N': return defendN_;
                case 'E': return defendE_;
                case 'S': return defendS_;
                case 'W': return defendW_;
            }
    }
}

/**
 * Checks whether any obstacle will be in the way for a player to use move m
 * @param movingPLoc The location of the player that is moving
 * @param otherPLoc The location of the other player
 * @param m The move that will take place
 * @return 
 */
bool Player::checkObstacle(pair<int, int> movingPLoc, pair<int, int> otherPLoc, Move m) {
    //new x or y position
    int newY, newX;
    //get move type and direction
    char moveType = m.first();
    char moveDir = m.second();
    //check direction
    switch (moveDir) {
        case 'N':
            //get new Y position
            newY = movingPLoc.first - 1;
            //check if out of bounds
            if (newY < 0) return false;
            //check if (M)oving into the other player
            if (moveType == 'M' && newY == otherPLoc.first && movingPLoc.second == otherPLoc.second)
                return false;
            break;
        case 'E':
            //get new X position
            newX = movingPLoc.second + 1;
            //check if out of bounds
            if (newX > 3) return false;
            //check if (M)oving into the other player
            if (moveType == 'M' && newX == otherPLoc.second && movingPLoc.first == otherPLoc.first)
                return false;
            break;
        case 'S':
            //get new Y position
            newY = movingPLoc.first + 1;
            //check if out of bounds
            if (newY > 3) return false;
            //check if (M)oving into the other player
            if (moveType == 'M' && newY == otherPLoc.first && movingPLoc.second == otherPLoc.second)
                return false;
            break;
        case 'W':
            //get new X position
            newX = movingPLoc.second - 1;
            //check if out of bounds
            if (newX < 0) return false;
            //check if (M)oving into the other player
            if (moveType == 'M' && newX == otherPLoc.second && movingPLoc.first == otherPLoc.first)
                return false;
            break;
    }
    //if there is nothing in the way
    return true;
}
 
/**
 * Checks if the player is dead
 * @return 
 */
bool Player::isDead() {
    return isDead_;
}

/**
 * Checks to see if the player is a human
 * @return 
 */
bool Player::isHuman() {
    return isHuman_;
}

/**
 * Kills player
 */
void Player::kill() {
    isDead_ = true;
}

/**
 * Reduces move count by one for specified move
 * @param m Move chosen
 */
void Player::move(Move m) {
    //get move type and direction
    char type = m.first();
    char dir = m.second();
    //check type
    switch (type) {
        case 'M':
            //check direction
            switch (dir) {
                //decrement appropriate move
                case 'N': numMovesN_--; break;
                case 'E': numMovesE_--; break;
                case 'S': numMovesS_--; break;
                case 'W': numMovesW_--; break;
            }
            break;
        case 'A':
            switch (dir) {
                //set appropriate move to false
                case 'N': attackN_ = false; break;
                case 'E': attackE_ = false; break;
                case 'S': attackS_ = false; break;
                case 'W': attackW_ = false; break;
            }
            break;
        case 'D':
            switch (dir) {
                case 'N': defendN_ = false; break;
                case 'E': defendE_ = false; break;
                case 'S': defendS_ = false; break;
                case 'W': defendW_ = false; break;
            }
            break;
    }
}

/**
 * Checks to see if the player is out of moves
 * @return 
 */
bool Player::outOfMoves() {
    int movesLeft = numMovesN_ + numMovesE_ + numMovesS_ + numMovesW_ + 
                    attackN_ + attackE_ + attackS_ + attackW_ + 
                    defendN_ + defendE_ + defendS_ + defendW_;
    return (movesLeft == 0);
}

/**
 * Revives player (if player defends towards the enemy)
 */
void Player::revive() {
    isDead_ = false;
}