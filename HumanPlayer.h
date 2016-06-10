/* 
 * File:   HumanPlayer.h
 * Author: Alex Grech IV
 *
 * Created on May 8, 2016, 5:24 PM
 */

#ifndef HUMANPLAYER_H
#define	HUMANPLAYER_H

#include "Player.h"

class HumanPlayer : public Player {
public:
    HumanPlayer();
    virtual Move getMove(std::pair<int, int>, std::pair<int, int>);
private:

};

#endif	/* HUMANPLAYER_H */

