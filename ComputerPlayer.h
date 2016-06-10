/* 
 * File:   ComputerPlayer.h
 * Author: Alex Grech IV
 *
 * Created on May 8, 2016, 7:09 PM
 */

#ifndef COMPUTERPLAYER_H
#define	COMPUTERPLAYER_H

#include "Player.h"

class ComputerPlayer : public Player {
public:
    ComputerPlayer();
    virtual Move getMove(std::pair<int, int>, std::pair<int, int>);
private:
};

#endif	/* COMPUTERPLAYER_H */

