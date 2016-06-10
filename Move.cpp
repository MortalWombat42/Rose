/* 
 * File:   Move.cpp
 * Author: Alex Grech IV
 * 
 * Created on May 8, 2016, 5:28 PM
 */

#include "Move.h"

/**
 * Creates a move that defaults to (M)ove (N)orth
 */
Move::Move() : moveType_('M'), direction_('N') {
}

/**
 * Creates a move with specified type and direction.  If not a valid type or 
 * direction, defaults to 'M' for type and 'N' for direction
 * @param type
 * @param dir
 */
Move::Move(char type = 'M', char dir = 'N') {
    if (type == 'M' || type == 'A' || type == 'D')
        moveType_ = type;
    else moveType_ = 'M';
    if (dir == 'N' || dir == 'E' || dir == 'S' || dir == 'W')
        direction_ = dir;
    else direction_ = 'N';
}

/**
 * Get the move type
 * @return 
 */
char Move::first() {
    return moveType_;
}

/**
 * Get the move direction
 * @return 
 */
char Move::second() {
    return direction_;
}