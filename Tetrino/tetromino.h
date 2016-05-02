//
//  tetromino.h
//  Tetrino
//
//  Created by Farzin Faghihi on 11/23/2013.
//  Copyright (c) 2013 Farzin Faghihi. All rights reserved.
//

#ifndef __Tetrino__tetromino__
#define __Tetrino__tetromino__

#include <iostream>
#include "Square.h"
#include <vector>


class Tetromino {

public:
    std::vector<Square *> squares;
    vec2 middle;
    
    Tetromino(int piece);
    void rotate(int degrees);
    void move(double x, double y);
    void restrictMove();
    bool atBottom();
    bool atLeftBorder();
    bool atRightBorder();
    void rotation(int degrees);
    
    bool restricted;
    
private:
    void initTetromino();
    void initColors(int piece);
};

#endif /* defined(__Tetrino__tetromino__) */
