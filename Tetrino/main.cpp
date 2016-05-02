#include <stdio.h>
#include "irrKlang/include/irrKlang.h"
#include "irrKlang/include/conio.h"

#include <math.h>
#include "Game.h"

using namespace irrklang;
using namespace std;

//window properties
double windowHeight = 480;
double windowWidth = 320;
int blocksize = 48;
Game *game;
bool isGravity = false;

unsigned int timeInterval = 1000;

void display(){
    
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    for(int i = 0; i < game->gridSizeX; i++) {
        for (int j = 0; j < game->gridSizeY; j++) {
            if(game->grid[i][j] != NULL) {
                game->draw(*game->grid[i][j]);
                glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            }
        }
    }
    for(int i = 0; i < 4; i++) {
        game->draw(*game->currentTetromino->squares[i]);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }
    glFlush();
}

void checkGameOver() {
    for (int x = 0; x < game->gridSizeX; x++) {
        if(game->grid[x][19] == NULL) {
            game->gameOver = true;
        }
    }
}

bool canMove(int gridPosX, int gridPosY) {
    
    if(gridPosX <= 12 && gridPosX >= 0 && game->grid[gridPosX][gridPosY] == NULL) {
        return true;
    }
    
    return false;
}

void speedUp() {
    if (timeInterval > 100) {
        timeInterval -= 100;
    }
}

void clearLines() {
    Square *square = game->currentTetromino->squares[0];
    for (int y = 0; y < game->gridSizeY; y++) {
        bool toClear = true;
        for (int x = 0; x < game->gridSizeX; x++) {
            if(game->grid[x][y] == NULL) {
                toClear = false;
            }
        }
        if(toClear) {
            game->scoreMultiplier++;
            game->score += game->scoreMultiplier;
            speedUp();
            printf("Score: %d \n", game->score);
            for (int x = 0; x < game->gridSizeX; x++) {
                game->grid[x][y] = NULL;
            }
            //shift lines down
            for (int j = y+1; j < game->gridSizeY; j++) {
                for (int k = 0; k < game->gridSizeX; k++) {
                    if (game->grid[k][j] != NULL) {
                        game->grid[k][j-1] = game->grid[k][j];
                        game->grid[k][j]->move(0, square->blockHeight);
                        game->grid[k][j] = NULL;
                    }
                }
            }
            y -=1;
        }
    }
}

void gravityMove(int t) {
    
    isGravity = true;
    bool allMove = true;
    
    for (int i = 0; i < 4; i++) {
        Square *currentSquare = game->currentTetromino->squares[i];
        double currentPosY = currentSquare->topLeftCorner[1];
        double newPosY = currentPosY + -currentSquare->halfBlockHeight*2;
        int gridPosX = round(((currentSquare->topLeftCorner[0]+1)/2*game->gridSizeX));
        int gridPosY = round(((newPosY+1)/2*game->gridSizeY));
        
        if(!canMove(gridPosX, gridPosY)) {
            allMove = false;
        }
    }
    
    bool atBottom = game->currentTetromino->atBottom();
    if (allMove && !atBottom) {
        game->currentTetromino->move(0, game->currentTetromino->squares[0]->halfBlockHeight*2);
    }
    else {
        game->currentTetromino->restrictMove();
        for (int i = 0; i < 4; i++) {
            Square *currentSquare = game->currentTetromino->squares[i];
            int gridPosX = round(((currentSquare->topLeftCorner[0]+1)/2*game->gridSizeX));
            int gridPosY = round(((currentSquare->topLeftCorner[1]+1)/2*game->gridSizeY));
            if (currentSquare->restrictMove) {
                game->grid[gridPosX][gridPosY] = currentSquare;
            }
        }
        clearLines();
        game->createTetromino();
    }
    
    glutPostRedisplay();
    
    isGravity = false;
    glutTimerFunc(timeInterval, gravityMove, 0);
}

void moveObject(int key) {
    
    if (!game->currentTetromino->restricted && !isGravity) {
        bool allMove = true;
        switch (key) {
            case 'r': {
                timeInterval = 1000;
                game->score = 0;
                game->scoreMultiplier = 0;
                game->gameOver = false;
                for (int x = 0; x < game->gridSizeX; x++) {
                    for (int y = 0; y < game->gridSizeY; y++) {
                        delete game->grid[x][y];
                        game->grid[x][y] = NULL;
                    }
                }
                game->createTetromino();
            }
            case GLUT_KEY_UP: {
                game->currentTetromino->rotation(90);
                break;
            }
            case GLUT_KEY_LEFT: {
                for (int i = 0; i < 4; i++) {
                    Square *currentSquare = game->currentTetromino->squares[i];
                    double currentPosX = currentSquare->topLeftCorner[0];
                    double newPosX = currentPosX + -currentSquare->halfBlockWidth*2;
                    int gridPosX = round(((newPosX+1)/2*game->gridSizeX));
                    int gridPosY = round((currentSquare->topLeftCorner[1]+1)/2*game->gridSizeY);
                    
                    if(!canMove(gridPosX, gridPosY)) {
                        allMove = false;
                    }
                }
                
                bool atOutbounds = game->currentTetromino->atLeftBorder();
                
                if (allMove && !atOutbounds) {
                    game->currentTetromino->move(-game->currentTetromino->squares[0]->halfBlockWidth*2, 0);
                }
                break;
            }
            case GLUT_KEY_RIGHT: {
                for (int i = 0; i < 4; i++) {
                    Square *currentSquare = game->currentTetromino->squares[i];
                    double currentPosX = currentSquare->topLeftCorner[0];
                    double newPosX = currentPosX + currentSquare->halfBlockWidth*2;
                    int gridPosX = round(((newPosX+1)/2*game->gridSizeX));
                    int gridPosY = round(((currentSquare->topLeftCorner[1]+1)/2*game->gridSizeY));
                    
                    if(!canMove(gridPosX, gridPosY)) {
                        allMove = false;
                    }
                }
                
                bool atOutbounds = game->currentTetromino->atRightBorder();
                
                if (allMove && !atOutbounds) {
                    game->currentTetromino->move(game->currentTetromino->squares[0]->halfBlockWidth*2, 0);
                }
                break;
            }
            case GLUT_KEY_DOWN: {
                for (int i = 0; i < 4; i++) {
                    Square *currentSquare = game->currentTetromino->squares[i];
                    double currentPosY = currentSquare->topLeftCorner[1];
                    double newPosY = currentPosY + -currentSquare->halfBlockHeight*2;
                    int gridPosX = round((currentSquare->topLeftCorner[0]+1)/2*game->gridSizeX);
                    int gridPosY = round(((newPosY+1)/2*game->gridSizeY));
                    
                    if(!canMove(gridPosX, gridPosY)) {
                        allMove = false;
                    }
                }
                
                bool atBottom = game->currentTetromino->atBottom();
                if (allMove && !atBottom) {
                    game->currentTetromino->move(0, game->currentTetromino->squares[0]->halfBlockHeight*2);
                }
                else {
                    game->currentTetromino->restrictMove();
                    for (int i = 0; i < 4; i++) {
                        Square *currentSquare = game->currentTetromino->squares[i];
                        int gridPosX = round(((currentSquare->topLeftCorner[0]+1)/2*game->gridSizeX));
                        int gridPosY = round(((currentSquare->topLeftCorner[1]+1)/2*game->gridSizeY));
                        if (currentSquare->restrictMove) {
                            game->grid[gridPosX][gridPosY] = currentSquare;
                        }
                    }
                    clearLines();
                    game->createTetromino();
                }
                break;
            }
        }
    }
    
    glutPostRedisplay();
}

void keyboardControl(int key, int x, int y) {
    moveObject(key);
}

int main(int argc, char** argv){
    
    // start irrKlang with default parameters
    ISoundEngine* engine = createIrrKlangDevice();
    if (!engine)
        return 0; // error starting up the engine
    
    // play some sound stream, looped
    engine->play2D("Tetris.wav", true);
    
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGBA | GLUT_3_2_CORE_PROFILE);
    
    glutInitWindowSize(windowWidth, windowHeight);
    
    glutCreateWindow("Tetrino");
    
    game = new Game();
    game->init(windowWidth, windowHeight, blocksize);
    
    glutDisplayFunc(display);
    
    glutSpecialFunc(keyboardControl);
    
    glutTimerFunc(timeInterval, gravityMove, 0);
    
    glutIdleFunc(glutPostRedisplay);
    
    glutMainLoop();
    
    //engine->drop(); // delete engine
    
    return 0;
}