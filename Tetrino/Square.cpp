//
//  Square.cpp
//  Tetrino
//
//  Created by Farzin Faghihi on 11/21/2013.
//  Copyright (c) 2013 Farzin Faghihi. All rights reserved.
//

#include "Square.h"

double Square::windowHeight = 480;
double Square::windowWidth = 320;
double Square::blocksize = 48;

Square::Square() {
    
    this->restrictMove = false;
    
    this->halfBlockWidth = (blocksize/windowWidth)/2;
    this->halfBlockHeight = (blocksize/windowHeight)/2;
    this->blockWidth = this->halfBlockWidth*2;
    this->blockHeight = this->halfBlockHeight*2;
    
}
    
void Square::initPoints() {
    
    this->bottomLeftCorner = point2(-halfBlockWidth, 1-(this->blockHeight));
    this->topLeftCorner = point2(-halfBlockWidth, 1);
    this->topRightCorner = point2(halfBlockWidth, 1);
    this->bottomRightCorner = point2(halfBlockWidth, 1-(this->blockHeight));
}

void Square::initColors(color4 color) {
    
    this->bottomLeftColor = color;
    this->topLeftColor = color;
    this->topRightColor = color;
    this->bottomRightColor = color;
}

void Square::move(double x, double y){
    bottomLeftCorner[0] += x;
    bottomLeftCorner[1] -= y;
    topLeftCorner[0] += x;
    topLeftCorner[1] -= y;
    topRightCorner[0] += x;
    topRightCorner[1] -= y;
    bottomRightCorner[0] += x;
    bottomRightCorner[1] -= y;
    
}