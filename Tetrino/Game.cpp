//
//  Game.cpp
//  Tetrino
//
//  Created by Farzin Faghihi on 11/22/2013.
//  Copyright (c) 2013 Farzin Faghihi. All rights reserved.
//

#include "Game.h"
#include "time.h"

typedef vec2 point2;
typedef vec4 color4;

GLuint abuffer;
GLuint program;

int randomNum() {
    
    int num = (rand() % 7) + 1;

    return num;
}

void Game::init(double windowWidth, double windowHeight, int blocksize){
    
    srand((unsigned int)time(0));
    
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(point2[4]) + sizeof(color4[4]), NULL, GL_STATIC_DRAW);
    
    this->gameWidth = windowWidth;
    this->gameHeight = windowHeight;
    this->blocksize = blocksize;
    this->score = 0;
    this->scoreMultiplier = 0;
    this->gameOver = false;
    printf("Score: %d \n", this->score);
    
    //set up grid
    this->gridSizeX = (int)((windowWidth/blocksize)*2);
    this->gridSizeY = (int)((windowHeight/blocksize)*2);
    this->grid = new Square **[this->gridSizeX];
    for(int i = 0; i < this->gridSizeX; i++) {
        this->grid[i] = new Square *[this->gridSizeY];
        for (int j = 0; j < this->gridSizeY; j++) {
            this->grid[i][j] = NULL;
        }
    }
    
    
    program = InitShader("vertex.glsl", "fragment.glsl");
    glUseProgram(program);
    
    glGenVertexArrays(1, &abuffer);
    glBindVertexArray(abuffer);
    
    int num = randomNum();
    this->currentTetromino = new Tetromino(num);
}

void Game::draw(Square square) {
    
    point2 vertices[4] = { square.bottomLeftCorner, square.topLeftCorner, square.topRightCorner, square.bottomRightCorner };
    color4 vColors[4] = { square.bottomLeftColor, square.topLeftColor, square.topRightColor, square.bottomRightColor };
    
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(vColors), vColors);
    
    GLuint location = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    
    GLuint vColor = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices)));
    
}

void Game::createTetromino() {
    
    int num = randomNum();
    Tetromino *piece = new Tetromino(num);
    this->currentTetromino = piece;
    
}