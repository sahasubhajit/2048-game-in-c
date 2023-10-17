#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>
#include "manual.h"


int previous_board[4][4] = {      //Initial state of the game, used this global variable to undo move or to check invalid move
    {0, 0, 2, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {2, 0, 0, 0}
    };

void printBoard(int board[4][4]) {
    //int score = compute_score(board);
    printw("  2048 Game Board\n\n");
    //printw("Score %d\n\n", score);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                printw("   -   ");
            } else {
                printw(" %4d  ", board[i][j]);
            }
            if (j < 3) {
                printw("|");
            }
        }
        printw("\n");
        if (i < 3) {
            printw("-------|-------|-------|-------\n");
        }
    }
    printw("\n");
}


int individual_score(int n){
    if (n %2 != 0){
        printw("Unexpected state!\n\n");
        exit(1);
    }
    else if(n == 2){
        return 0;
    }
    else{
        return 2*individual_score(n/2) + n;  //Recursive value a_n = 2*a_(n-1) + n, for n > 1 else 0
    }
}



void total_score(int board[4][4]){
    //printw("Before computing score \n\n");
    //printBoard(board);
    int score = 0;
    for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                if (board[i][j] != 0)
                {
                score += individual_score(board[i][j]);
                }
            }
        }
    printw("Present score %d\n\n", score); 
    //printw("After computing score \n\n");
    //printBoard(board);      
}

int game_over(int board[4][4]){  //function to check whether the game is over, 1 if no space to move tile else 0
    int flag = 1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0){
                flag = 0;
                break;
            }
        }
    }

    if (flag == 1){
        printw("\nTile full, Game Over!");
    }
    return flag;    
}








// Function to move tiles up
void move_up(int board[4][4]) {
    memcpy(previous_board, board, 64);    //keep track of the previous state
    for (int j = 0; j < 4; j++) {
        // Merge tiles in the same column
        int k = 0;
        for (int i = 1; i < 4; i++) {
            if (board[i][j] != 0) {
                if (board[k][j] == 0) {
                    board[k][j] = board[i][j];
                    board[i][j] = 0;
                } else if (board[k][j] == board[i][j]) {
                    board[k][j] *= 2;
                    board[i][j] = 0;
                    k++;
                } else {
                    k++;
                    if (k != i) {
                        board[k][j] = board[i][j];
                        board[i][j] = 0;
                    }
                }
            }
        }
    }
}



// Function to move tiles down
void move_down(int board[4][4]) {
    memcpy(previous_board, board, 64);    //keep track of the previous state
    for (int j = 0; j < 4; j++) {
        int k = 4 - 1;
        for (int i = 4 - 2; i >= 0; i--) {
            if (board[i][j] != 0) {
                if (board[k][j] == 0) {
                    board[k][j] = board[i][j];
                    board[i][j] = 0;
                } else if (board[k][j] == board[i][j]) {
                    board[k][j] *= 2;
                    board[i][j] = 0;
                    k--;
                } else {
                    k--;
                    if (k != i) {
                        board[k][j] = board[i][j];
                        board[i][j] = 0;
                    }
                }
            }
        }
    }
}



// Function to move tiles left
void move_left(int board[4][4]) {
    memcpy(previous_board, board, 64);     //keep track of the previous state
    for (int i = 0; i < 4; i++) {
        int k = 0;
        for (int j = 1; j < 4; j++) {
            if (board[i][j] != 0) {
                if (board[i][k] == 0) {
                    board[i][k] = board[i][j];
                    board[i][j] = 0;
                } else if (board[i][k] == board[i][j]) {
                    board[i][k] *= 2;
                    board[i][j] = 0;
                    k++;
                } else {
                    k++;
                    if (k != j) {
                        board[i][k] = board[i][j];
                        board[i][j] = 0;
                    }
                }
            }
        }
    }
}



// Function to move tiles right
void move_right(int board[4][4]) {
    memcpy(previous_board, board, 64);
    for (int i = 0; i < 4; i++) {
        int k = 4 - 1;
        for (int j = 4 - 2; j >= 0; j--) {
            if (board[i][j] != 0) {
                if (board[i][k] == 0) {
                    board[i][k] = board[i][j];
                    board[i][j] = 0;
                } else if (board[i][k] == board[i][j]) {
                    board[i][k] *= 2;
                    board[i][j] = 0;
                    k--;
                } else {
                    k--;
                    if (k != j) {
                        board[i][k] = board[i][j];
                        board[i][j] = 0;
                    }
                }
            }
        }
    }
}


int valid_move_checking(int board[4][4]){  //If any tile is not moved after the given move then mark it as invalid
    int valid = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++){
            if (board[i][j] != previous_board[i][j]){
                valid = 1;
                break;
            }

        }
    }
    return valid;
}



void main()
    {


    //printBoard(board);






    initscr();  // Initialize the ncurses library
    raw();      // Disable line buffering
    keypad(stdscr, TRUE); // Enable special keys (e.g., arrow keys)
    scrollok(stdscr, TRUE); // Enable scrolling

    int ch;
    
    
    
    
    
    printw("\n  Let's play 2048! \n");
    printw("  ****   ****   *  *   ****\n");
    printw("     *   *  *   *  *   *  *\n");
    printw("  ****   *  *   ****   ****\n");
    printw("  *      *  *      *   *  *\n");
    printw("  ****   ****      *   ****\n");


    int board[4][4] = {      //Initial state of the game
    {0, 0, 2, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {2, 0, 0, 0}
    };
    
    
    
    
    
    int r = 0;
    while ((ch = getch()) != 'q' && game_over(board) == 0) { // Loop until the 'q' key is pressed or any space to move tile
        switch (ch) {
            case KEY_UP:
                
                move_up(board);
                if (valid_move_checking(board) == 1) // Go to next state if the move is valid only
                {
                srand(time(NULL));   
                r = rand()%16;  
                while (board[r/4][r%4] != 0) //randomly select a space to add 2
                {
                    r = rand()%16;  
                }
                board[r/4][r%4] = 2;
                printw("Up arrow key pressed\n");
                total_score(board);
                printBoard(board);             
                game_over(board);              // print the game over condition if no space to move tile
                }
                break;
            case KEY_DOWN:
                
                move_down(board);
                if (valid_move_checking(board) == 1)  // Go to next state if the move is valid only
                {
                srand(time(NULL));   
                r = rand()%16;  
                while (board[r/4][r%4] != 0)  //randomly select a space to add 2
                {
                    r = rand()%16;  
                }
                board[r/4][r%4] = 2;
                printw("Down arrow key pressed\n");
                total_score(board);
                printBoard(board);
                game_over(board);           // print the game over condition if no space to move tile
                }
                break;
            case KEY_LEFT:
                
                move_left(board);
                if (valid_move_checking(board) == 1)  // Go to next state if the move is valid only
                {
                srand(time(NULL));   
                r = rand()%16;  
                while (board[r/4][r%4] != 0)  //randomly select a space to add 2
                {
                    r = rand()%16;  
                }
                board[r/4][r%4] = 2;
                printw("Left arrow key pressed\n");
                total_score(board);
                printBoard(board);
                game_over(board);          // print the game over condition if no space to move tile
                }
                break;
            case KEY_RIGHT:
                
                move_right(board);
                if (valid_move_checking(board) == 1)  // Go to next state if the move is valid only
                {
                srand(time(NULL));   
                r = rand()%16;  
                while (board[r/4][r%4] != 0)   //randomly select a space to add 2
                {
                    r = rand()%16;  
                }
                board[r/4][r%4] = 2;
                printw("Right arrow key pressed\n");
                total_score(board);
                printBoard(board);
                game_over(board);          // print the game over condition if no space to move tile
                }
                break;                
            case 'u':
                printw("\nUndo Move\n");
                memcpy(board, previous_board, 64);
                total_score(board);
                printBoard(board);
                break;
            case 'h':
                printw("Game Manual\n");
                display2048Manual();
                break;     
            default:
                printw("Pressed key: %c\n", ch);
                break;
        }
        refresh();
    }

    endwin(); // Clean up ncurses
    }       
