/* 
 * File:   Player.h
 * Author: Alex Grech IV
 *
 * Created on May 8, 2016, 4:34 PM
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include <utility>
#include "Move.h"

class Player {
public:
    Player(bool);
    bool canAttack();
    bool canDefend();
    bool canMove(Move);
    bool checkObstacle(std::pair<int, int>, std::pair<int, int>, Move);
    virtual Move getMove(std::pair<int, int>, std::pair<int, int>) = 0;
    bool isDead();
    bool isHuman();
    void kill();
    void move(Move);
    bool outOfMoves();
    void revive();
private:
    int numMovesN_;
    int numMovesE_;
    int numMovesS_;
    int numMovesW_;
    bool attackN_;
    bool attackE_;
    bool attackS_;
    bool attackW_;
    bool defendN_;
    bool defendE_;
    bool defendS_;
    bool defendW_;
    bool isHuman_;
    bool isDead_;
};

#endif	/* PLAYER_H */

