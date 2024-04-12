#ifndef GAME_H
#define GAME_H

#include "Square.h"
#include "Button.h"
#include <GL/glext.h>
#include <iostream>

class Game {
    /* Square board[9]; */
    Square **board;
    int count;
    bool playerX;
    bool AI;

    bool winner;

    bool filled;
   

    Button button1;
    Button button2;
    Button button3;
    Button button4;
    Button button5;
    Button win;
    Button playAgain;

    bool clicked1;
    bool clicked2;
    bool clicked3;
    bool clicked4;
    bool clicked5;



    void AIMove() {
        /* if(winner == false){
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
        } */
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

        float size = 1.2 / count;

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
        button1 = Button("vs. Human", 0.5, 0.5);
        button2 = Button("vs. A.I.", 0.5, 0.2);
        button3 = Button("3 x 3", -0.9, -0.75);
        button4 = Button("4 x 4", -0.5, -0.75);
        button5 = Button("5 x 5", -0.1, -0.75);



        win = Button("win", 0, 0);
        playAgain = Button("Play Again", 0.5, -0.5);

    

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

        if(filled == true){
            for(int i = 0; i < count; i++){
                int seen = 0;
                for(int j = 0; j < count; j++){
                    if(board[i][j].isSelected() == PLAYER_X){
                        seen++;
                    }
                }
                if(seen == count){
                    winner = true;
                    break;
                }
            }
        }

        if(button3.contains(x, y)){
            std::cout << "Will change to 3x3" << std::endl;
            for(int i = 0; i < count; i++){
                delete[] board[i];
            }
            delete[] board;
            count = 3;
            clicked3 = true;
            init();
            playerX = true;
          
        } else if(button4.contains(x, y)){
            std::cout << "Will change to 4x4" << std::endl;
            for(int i = 0; i < count; i++){
                delete[] board[i];
            }
            delete[] board;
            count = 4;
            clicked4 = true;
            init();
            playerX = true;
           
        } else if (button5.contains(x, y)){
            std::cout << "Will change to 5x5" << std::endl;
            for(int i = 0; i < count; i++){
                delete[] board[i];
            }
            delete[] board;
            count = 5;
            clicked5 = true;
            init();
            playerX = true;
            
           
        } else if(button1.contains(x, y)){
            clicked1 = true;;
            playerX = true;
            AI = false;
        } else if(button2.contains(x, y)){
            AIMove();
            clicked2 = true;
            playerX = false;
            AI = true;
            
        } else if (playAgain.contains(x, y)){
            winner = false;
            for(int i = 0; i < count; i++){
                delete[] board[i];
            }
            delete[] board;
            count = 3;
            clicked3 = false;
            init();
        }
        

        if (AI) {
            AIMove();
        }


    }


    void winX(){
        // int seen;
        // seen = 0;
        // for(int i = 0; i < count; i++){
        //     if(seen == count){
        //         break;
        //     }
        //     if(board[i]->isSelected() == PLAYER_X){
        //         seen++;
        //     }
        // }
        // if(seen == count){
        //     winner = true;
        //     seen = 0;
        // }
        // seen = 0;

        int seen;
        for(int i = 0; i < count; i++){
            seen = 0;
            for(int j = 0; j < count; j++){
                if(board[i][j].isSelected() == PLAYER_X){
                    seen++;
                }
            }
            if(seen == count){
                winner = true;
                return;
            }
        }
        winner = false;

    }


    void draw() {
        if(winner == true){
            win.draw();
            playAgain.draw();
        } else if(winner == false){
            button3.draw();
            button4.draw();
            button5.draw();
            if(clicked3 == true || clicked4 == true || clicked5 == true){
                button1.draw();
                button2.draw();
                for (int i = 0; i < count; i++) {
                    for(int j = 0; j < count; j++){
                        board[i][j].draw();
                    }
                }
            }
           
        }

        
    }
};

#endif