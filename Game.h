#ifndef GAME_H
#define GAME_H

#include "Square.h"
#include <iostream>

class Game {
    /* Square board[9]; */
    Square **board;
    int count;
    bool playerX;
    bool AI;

    bool filled;


    void AIMove() {
        if (!playerX) {
            for (int i = 0; i < count; i++) {
                filled = false;
                for(int j = 0; j < count; j++){
                    if(board[i][j].isEmpty()){
                        board[i][j].playO();
                        filled = true;
                        break;
                    }
                }
                if(filled == true){
                    break;
                }
            }
            playerX = !playerX;
        }
    }

    void init(){
        board = new Square*[count];
        for(int i = 0; i < count; i++){
            board[i] = new Square[count];
        }

        float x = -0.9;
        float y = 0.9;

        float size = 1.8 / count;

        for (int i = 0; i < count; i++){
            x = -0.9;
            for (int j = 0; j < count; j++){
                board[i][j] = Square(x, y, size);
                x += size;
            }
            y -= size;
        }
    }


public:
    Game() {

        count = 3;
        init();

       

        playerX = true;
        AI = false;
    }

    

    void AIOn() {
        AI = true;
        AIMove();
    }

    void AIOff() {
        AI = false;
    }

    void playerXFirst() {
        playerX = true;
    }

    void playerOFirst() {
        playerX = false;
    }

    void start() {
        if (AI) {
            AIMove();
        }
    }

    void handleMouseClick(float x, float y) {
        for (int i = 0; i < count; i++) {
            filled = false;
            for(int z = 0; z < count; z++){
                if (board[i][z].contains(x,  y)) {
                    if (board[i][z].isEmpty()) {
                        if (playerX) {
                            board[i][z].playX();
                            filled = true;

                        } else {
                            board[i][z].playO();
                            filled = true;
                        }
                        playerX = !playerX;
                        break;
                    }
                }
            }
            if(filled == true){
                break;
            }

        }

        if (AI) {
            AIMove();
        }
    }

    void draw() {
        for (int i = 0; i < count; i++) {
            for(int j = 0; j < count; j++){
                board[i][j].draw();
            }
        }
    }
};

#endif