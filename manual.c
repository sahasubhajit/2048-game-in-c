#include <stdio.h>
#include <ncurses.h>
#include "manual.h"

void display2048Manual() {
    printw("2048 Game Manual\n");
    printw("========================================\n\n");
    
    printw("Introduction:\n");
    printw("2048 is a popular puzzle game where you combine tiles to reach the\n");
    printw("2048 tile. The game is played on a 4x4 grid, and you can move the tiles\n");
    printw("in four directions: up, down, left, and right. The game ends when there\n");
    printw("are no more moves possible, or you reach the 2048 tile.\n\n");

    printw("Game Controls:\n");
    printw("Use the arrow keys to move tiles in the desired direction.\n");
    printw("   - Press 'Up Arrow' to move tiles upwards.\n");
    printw("   - Press 'Down Arrow' to move tiles downwards.\n");
    printw("   - Press 'Left Arrow' to move tiles to the left.\n");
    printw("   - Press 'Right Arrow' to move tiles to the right.\n\n");

    printw("Objective:\n");
    printw("Combine tiles with the same number to create a new tile with the sum\n");
    printw("of the two tiles. The ultimate goal is to create a tile with the number\n");
    printw("2048. The game ends when no more moves are possible or when you reach\n");
    printw("the 2048 tile.\n\n");

    printw("Scoring:\n");
    printw("Your score is based on the number of moves and the value of the tiles\n");
    printw("you combine. The higher the value of the tiles you create, the higher\n");
    printw("your score will be. Try to achieve the highest score possible!\n\n");

    printw("Game Over:\n");
    printw("The game ends when there are no more moves possible. You can restart\n");
    printw("the game to try again or exit the game.\n\n");

    printw("Winning the Game:\n");
    printw("The game is won when you create the 2048 tile. Celebrate your victory\n");
    printw("and aim for an even higher score!\n\n");

    printw("Enjoy playing 2048!\n");
    printw("========================================\n");
}
/*
void main() {
    // Call the function to display the manual
    display2048Manual();
}
*/
