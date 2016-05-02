//
//  tetromino.cpp
//  Tetrino
//
//  Created by Farzin Faghihi on 11/23/2013.
//  Copyright (c) 2013 Farzin Faghihi. All rights reserved.
//

#include "tetromino.h"

color4 colors[7] = { color4(0, 0.68, 0.94, 1.0), color4(0.97, 0.58, 0.11, 1.0), color4(0.92, 0.0, .55, 1.0),
                     color4(0.93, 0.11, 0.14, 1.0), color4(0.22, 0.71, 0.29, 1.0), color4(0.0, 0.45, 0.74, 1.0), color4(0.4, 0.18, 0.57, 1.0) };

Tetromino::Tetromino(int piece){

    this->restricted = false;
    this->squares.push_back(new Square());
    this->squares.push_back(new Square());
    this->squares.push_back(new Square());
    this->squares.push_back(new Square());
    
    this->initTetromino();
    this->initColors(piece);
    switch (piece){
        case 1: // line cyan piece
            this->squares[1]->move(0, squares[0]->blockHeight);
            this->squares[2]->move(0, 2*squares[0]->blockHeight);
            this->squares[3]->move(0, 3*squares[0]->blockHeight);
            this->middle[0] = this->squares[1]->bottomLeftCorner[0] + this->squares[0]->halfBlockWidth;
            this->middle[1] = this->squares[1]->bottomLeftCorner[1] - this->squares[0]->halfBlockHeight;
            break;
        case 2: // square orange piece
            this->squares[1]->move(squares[0]->blockWidth, 0);
            this->squares[2]->move(squares[0]->blockWidth, squares[0]->blockHeight);
            this->squares[3]->move(0, squares[0]->blockHeight);
            this->middle[0] = this->squares[1]->topLeftCorner[0];
            this->middle[1] = this->squares[1]->topLeftCorner[1];
            break;
        case 3: // T piece
            this->squares[1]->move(-squares[0]->blockWidth, 0);
            this->squares[2]->move(squares[0]->blockWidth, 0);
            this->squares[3]->move(0, squares[0]->blockHeight);
            this->middle[0] = this->squares[0]->topLeftCorner[0] + this->squares[0]->halfBlockWidth;
            this->middle[1] = this->squares[0]->topLeftCorner[1] - this->squares[0]->halfBlockHeight;
            break;
        case 4: //  L red piece
            this->squares[1]->move(0, squares[0]->blockHeight);
            this->squares[2]->move(0, 2*squares[0]->blockHeight);
            this->squares[3]->move(-squares[0]->blockWidth, 2*squares[0]->blockHeight);
            this->middle[0] = this->squares[2]->topLeftCorner[0] + this->squares[0]->halfBlockWidth;
            this->middle[1] = this->squares[2]->topLeftCorner[1] - this->squares[0]->halfBlockHeight;
            break;
        case 5: // L green square piece
            this->squares[1]->move(0, squares[0]->blockHeight);
            this->squares[2]->move(0, 2*squares[0]->blockHeight);
            this->squares[3]->move(this->squares[0]->blockWidth, 2*squares[0]->blockHeight);
            this->middle[0] = this->squares[2]->topLeftCorner[0] + this->squares[0]->halfBlockWidth;
            this->middle[1] = this->squares[2]->topLeftCorner[1] - this->squares[0]->halfBlockHeight;
            break;
        case 6: // Z blue square piece
            this->squares[1]->move(-squares[0]->blockWidth, 0);
            this->squares[2]->move(0, squares[0]->blockHeight);
            this->squares[3]->move(squares[0]->blockWidth, squares[0]->blockHeight);
            this->middle[0] = this->squares[0]->topLeftCorner[0] + this->squares[0]->halfBlockWidth;
            this->middle[1] = this->squares[0]->topLeftCorner[1] - this->squares[0]->halfBlockHeight;
            break;
        case 7: // Z purple square piece
            this->squares[1]->move(squares[0]->blockWidth, 0);
            this->squares[2]->move(0, squares[0]->blockHeight);
            this->squares[3]->move(-squares[0]->blockWidth, squares[0]->blockHeight);
            this->middle[0] = this->squares[0]->topLeftCorner[0] + this->squares[0]->halfBlockWidth;
            this->middle[1] = this->squares[0]->topLeftCorner[1] - this->squares[0]->halfBlockHeight;
            break;
    }
}

void Tetromino::rotation(int degrees){
    GLdouble angle = DegreesToRadians * degrees;
    
    mat2 rot = mat2();
    rot = { vec2(cos(angle), sin(angle)), vec2(-sin(angle), cos(angle)) };
    
    double windowWidth = this->squares[0]->windowWidth;
    double windowHeight = this->squares[0]->windowHeight;
    for(int i = 0; i < 4; i++) {
        
        point2 pixelCorners[4];
        pixelCorners[0] = point2((this->squares[i]->topLeftCorner[0]+1)/2*windowWidth,
                                     (this->squares[i]->topLeftCorner[1]+1)/2*windowHeight);
        pixelCorners[1] = point2((this->squares[i]->topRightCorner[0]+1)/2*windowWidth,
                                     (this->squares[i]->topRightCorner[1]+1)/2*windowHeight);
        pixelCorners[2] = point2((this->squares[i]->bottomRightCorner[0]+1)/2*windowWidth,
                                     (this->squares[i]->bottomRightCorner[1]+1)/2*windowHeight);
        pixelCorners[3] = point2((this->squares[i]->bottomLeftCorner[0]+1)/2*windowWidth,
                                     (this->squares[i]->bottomLeftCorner[1]+1)/2*windowHeight);
        point2 pixelMiddle = point2((this->middle[0]+1)/2*windowWidth,
                                 (this->middle[1]+1)/2*windowHeight);
        
        point2 newPixelCorners[4];
        newPixelCorners[0] = rot*(pixelCorners[0]-pixelMiddle)+pixelMiddle;
        newPixelCorners[1] = rot*(pixelCorners[1]-pixelMiddle)+pixelMiddle;
        newPixelCorners[2] = rot*(pixelCorners[2]-pixelMiddle)+pixelMiddle;
        newPixelCorners[3] = rot*(pixelCorners[3]-pixelMiddle)+pixelMiddle;
        
        for(int j = 0; j < 4; j++) {
            if ((newPixelCorners[j][0] > 320 || newPixelCorners[j][0] < 0)) {
                return;
            }
            if ((newPixelCorners[j][1] > 480 || newPixelCorners[j][1] < 0)) {
                return;
            }
        }
        
        this->squares[i]->topRightCorner = point2((newPixelCorners[0][0]*2/windowWidth)-1, (newPixelCorners[0][1]*2/windowHeight)-1);
        this->squares[i]->bottomRightCorner = point2((newPixelCorners[1][0]*2/windowWidth)-1, (newPixelCorners[1][1]*2/windowHeight)-1);
        this->squares[i]->bottomLeftCorner = point2((newPixelCorners[2][0]*2/windowWidth)-1, (newPixelCorners[2][1]*2/windowHeight)-1);
        this->squares[i]->topLeftCorner = point2((newPixelCorners[3][0]*2/windowWidth)-1, (newPixelCorners[3][1]*2/windowHeight)-1);
    }
}

void Tetromino::initTetromino() {
    
    for(int i = 0; i < 4; i++) {
        this->squares[i]->initPoints();
    }
}

void Tetromino::initColors(int piece) {
    
    int colorPicker = piece-1;
    color4 color = colors[colorPicker];
    
    for(int i = 0; i < 4; i++) {
        this->squares[i]->initColors(color);
    }
}

bool Tetromino::atBottom() {
    
    bool outBounds = false;
    for(int i = 0; i < 4; i++) {
        if(this->squares[i]->bottomLeftCorner[1] < -0.98) {
            outBounds = true;
        }
        
    }
    
    return outBounds;
}

bool Tetromino::atLeftBorder() {
    bool outBounds = false;
    for(int i = 0; i < 4; i++) {
        if(this->squares[i]->bottomLeftCorner[0] < -0.83) {
            outBounds = true;
        }
        
    }
    
    return outBounds;
}

bool Tetromino::atRightBorder() {
    bool outBounds = false;
    for(int i = 0; i < 4; i++) {
        if(this->squares[i]->bottomLeftCorner[0] > .68) {
            outBounds = true;
        }
        
    }
    
    return outBounds;
}

void Tetromino::move(double x, double y) {
    
    for(int i = 0; i < 4; i++) {
        this->squares[i]->move(x, y);
    }
    this->middle[0] += x;
    this->middle[1] -= y;
}

void Tetromino::restrictMove() {
    
    for(int i = 0; i < 4; i++) {
        this->squares[i]->restrictMove = true;
    }
    this->restricted = true;
}

