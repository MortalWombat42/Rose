/* 
 * File:   Move.h
 * Author: Alex Grech IV
 *
 * Created on May 8, 2016, 5:28 PM
 */

#ifndef MOVE_H
#define	MOVE_H

class Move {
public:
    Move();
    Move(char, char);
    char first();
    char second();
private:
    char moveType_;
    char direction_;
};

#endif	/* MOVE_H */

