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
    bool winnerO;
    bool tieOutcome;

    bool filled;
   

    Button button1;
    Button button2;
    Button button3;
    Button button4;
    Button button5;
    Button win;
    Button winO;
    Button playAgain;
    Button quit;
    Button tieGame;

    bool clicked1;
    bool clicked2;
    bool clicked3;
    bool clicked4;
    bool clicked5;



    void AIMove() {
        if(winner == false || winnerO == false){
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
                        winX();
                        oWinner();
                    }
                    if(filled == true){
                        break;
                    }
                }
                playerX = !playerX;
            }
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
        tieGame = Button("Tie", -0.1, 0);



        win = Button("winner X", 0, 0);
        winO = Button ("winner O", 0, 0.1);
        playAgain = Button("Play Again", 0.5, -0.5);
        quit = Button("Quit", 0.7, -0.8);
        

    

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
        if(winner == false || winnerO == false || tieOutcome == false){
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
        } 

        if(filled == true){
            winX();
            oWinner();
            tie();
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
            // exit(0); stop openGl app
            winner = false;
            winnerO = false;
            tieOutcome = false;
            for(int i = 0; i < count; i++){
                delete[] board[i];
            }
            delete[] board;
            count = 3;
            clicked3 = false;
            init();
        } else if(quit.contains(x,y)){
            exit(0);
        }
        

        if (AI) {
            AIMove();
        }


    }

    void tie(){
        int row = 0;
        int column = 0;
        for(int i = 0; i < count; i++){
            for(int z = 0; z < count; z++){
                if(board[i][z].getPlayer() == PLAYER_X || board[i][z].getPlayer() == PLAYER_O){
                    column++;
                }
            }
            if(column == count * count){
                tieOutcome = true;
                break;
            }
        }
    }


    void winX(){
        for(int i = 0; i < count; i++){
            int xCount = 0;
            for(int z = 0; z < count; z++){
                if(board[i][z].getPlayer() == PLAYER_X){
                    xCount++;
                }
            }
            if(xCount == count){
                winner = true;
                break;
            }
        }

        for(int i = 0; i < count; i++){
            int xCount = 0;
            for(int z = 0; z < count; z++){
                if(board[z][i].getPlayer() == PLAYER_X){
                    xCount++;
                }
            }
            if(xCount == count){
                winner = true;
                break;
            }
        }

        int xCount = 0;
        for(int i = 0; i < count; i++){
            if(board[i][i].getPlayer() == PLAYER_X){
                xCount++;
            }
            if(xCount == count){
                winner = true;
                xCount = 0;
                break;
            }
        }
        int xCounts = 0;
        for(int i = 0; i < count; i++){
            if(board[count - 1 - i][i].getPlayer() == PLAYER_X){
                xCounts++;
            }
            if(xCounts == count){
                winner = true;
                xCounts = 0;
                break;
            }
        }
    
    
    }

    void oWinner(){
        for(int i = 0; i < count; i++){
            int xCount = 0;
            for(int z = 0; z < count; z++){
                if(board[i][z].getPlayer() == PLAYER_O){
                    xCount++;
                }
            }
            if(xCount == count){
                winnerO = true;
                break;
            }
        }

        for(int i = 0; i < count; i++){
            int xCount = 0;
            for(int z = 0; z < count; z++){
                if(board[z][i].getPlayer() == PLAYER_O){
                    xCount++;
                }
            }
            if(xCount == count){
                winnerO = true;
                break;
            }
        }

        int xCount = 0;
        for(int i = 0; i < count; i++){
            if(board[i][i].getPlayer() == PLAYER_O){
                xCount++;
            }
            if(xCount == count){
                winnerO = true;
                xCount = 0;
                break;
            }
        }
        int xCounts = 0;
        for(int i = 0; i < count; i++){
            if(board[count - 1 - i][i].getPlayer() == PLAYER_O){
                xCounts++;
            }
            if(xCounts == count){
                winnerO = true;
                xCounts = 0;
                break;
            }
        }
    }
 

    void draw() {
        if(winner == true){
            win.draw();
            playAgain.draw();
            quit.draw();
        } else if(winnerO == true){
            winO.draw();
            playAgain.draw();
            quit.draw();
        } else if(tieOutcome == true){
            tieGame.draw();
            playAgain.draw();
            quit.draw();
        }
        else if(winner == false || winnerO == false || tieOutcome == false){
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