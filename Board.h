/* 
 * File:   Board.h
 * Author: Alex Grech IV
 *
 * Created on May 8, 2016, 4:56 PM
 */

#ifndef BOARD_H
#define	BOARD_H

#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include "Move.h"
#include "Player.h"

class Board {
public:
    Board(HumanPlayer&, ComputerPlayer&);
    virtual ~Board();
    std::pair<int, int> compLoc();
    std::pair<int, int> humanLoc();
    bool isCompDead();
    bool isHumanDead();
    void movePlayers();
    void print();
    void resolve(Move,int,int);
    void resolve(Move,int,int,Move,int,int);
private:
    Player* board_[4][4];
    ComputerPlayer comp_;
    HumanPlayer player_;
};

#endif	/* BOARD_H */

