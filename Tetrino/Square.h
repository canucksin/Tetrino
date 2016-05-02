//
//  Square.h
//  Tetrino
//
//  Created by Farzin Faghihi on 11/21/2013.
//  Copyright (c) 2013 Farzin Faghihi. All rights reserved.
//

#ifndef __Tetrino__Square__
#define __Tetrino__Square__

#include <iostream>
#include "Angel.h"

typedef vec2 point2;
typedef vec4 color4;

class Square {
    
public:
    // Square public properties
    static double windowWidth;
    static double windowHeight;
    static double blocksize;
    point2 bottomLeftCorner;
    point2 topLeftCorner;
    point2 topRightCorner;
    point2 bottomRightCorner;
    
    color4 bottomLeftColor;
    color4 topLeftColor;
    color4 topRightColor;
    color4 bottomRightColor;
    
    double offsetX;
    double offsetY;
    double halfBlockWidth;
    double halfBlockHeight;
    double blockWidth;
    double blockHeight;
    bool restrictMove;
    
    // Square methods
    Square();
    void initPoints();
    void initColors(color4 color);
    void checkPosition();
    void move(double x, double y);

private:
    
};

#endif /* defined(__Tetrino__Square__) */
