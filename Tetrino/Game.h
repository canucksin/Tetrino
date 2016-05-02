//
//  Game.h
//  Tetrino
//
//  Created by Farzin Faghihi on 11/22/2013.
//  Copyright (c) 2013 Farzin Faghihi. All rights reserved.
//

#ifndef __Tetrino__Game__
#define __Tetrino__Game__

#include <iostream>
#include "Angel.h"
#include "tetromino.h"
#include <vector>

class Game {
    
public:
    GLuint abuffer;
    GLuint program;
    Tetromino *currentTetromino;
    int blocksize;
    double gameWidth;
    double gameHeight;
    Square ***grid;
    int gridSizeX;
    int gridSizeY;
    int score;
    int scoreMultiplier;
    bool gameOver;
    
    //methods
    void init(double windowWidth, double windowHeight, int blocksize);
    void draw(Square square);
    void createTetromino();
    
private:

};

#endif /* defined(__Tetrino__Game__) */
