#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void ticTacToe();
void playTurn(int *turn, char grid[3][3]);
int checkInput(char *position);
int markPosition(char *position, int *turn, char grid[3][3]);
int checkWin(char grid[3][3]);

int main() {
    ticTacToe();

    while (1) {
        char option;
        printf("\nPlay Again? (y)es or (n)o.\n");
        scanf(" %c", &option);

        if (option == 'y') ticTacToe();
        else if (option == 'n') {
            puts("Bye, thanks for playing! o/");
            break;
        };
    }

    return 0;
}

void ticTacToe() {
    int turn = 1;
    char grid[3][3] = {{'_', '_', '_'},
                       {'_', '_', '_'},
                       {'_', '_', '_'}};

    puts("\nGame Started!\n");
    
    while (1) {
        playTurn(&turn, grid);
        if (checkWin(grid)) break;
    }
};

void playTurn(int *turn, char grid[3][3]) {
    char position[3];

    while (1) {
        printf("\n%c turn.\n\n", *turn ? 'X' : 'O');
    
        printf("  1 2 3\n");
        printf("A %c|%c|%c\n", grid[0][0], grid[0][1], grid[0][2]);
        printf("B %c|%c|%c\n", grid[1][0], grid[1][1], grid[1][2]);
        printf("C %c|%c|%c\n", grid[2][0], grid[2][1], grid[2][2]);
    
        printf("\nChoose the position (1A, 3B, etc.)\n");
        scanf("%s", position);
    
        if (!checkInput(position)) {
            printf("\nInvalid input.\n");
            continue;
        };
        
        if (markPosition(position, turn, grid)) break;

        printf("\nPosition already marked. Please choose another.\n");
    }
}

int checkInput(char *position) {
    if (position[0] != '1' && position[0] != '2' && position[0] != '3') return 0;
    if (position[1] != 'A' && position[1] != 'B' && position[1] != 'C') return 0;
    
    return 1;
}

int markPosition(char *position, int *turn, char grid[3][3]) {
    int line, column;

    column = (position[0] == '1') ? 0 : (position[0] == '2') ? 1 : 2;
    line = (position[1] == 'A') ? 0 : (position[1] == 'B') ? 1 : 2;

    if (grid[line][column] != '_') return 0;

    grid[line][column] = *turn ? 'X' : 'O';
    *turn = !(*turn);
    
    return 1;
}

int checkWin(char grid[3][3]) {
    char winner = '_';
    int allMarked = 1;
    
    if (grid[0][0] == grid[0][1] && grid[0][0] == grid[0][2]) winner = grid[0][0];
    else if (grid[1][0] == grid[1][1] && grid[1][0] == grid[1][2]) winner = grid[1][0];
    else if (grid[2][0] == grid[2][1] && grid[2][0] == grid[2][2]) winner = grid[2][0];
    
    else if (grid[0][0] == grid[1][0] && grid[0][0] == grid[2][0]) winner = grid[0][0];
    else if (grid[0][1] == grid[1][1] && grid[0][1] == grid[2][1]) winner = grid[0][1];
    else if (grid[0][2] == grid[1][2] && grid[0][2] == grid[2][2]) winner = grid[0][2];
        
    else if (grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2]) winner = grid[0][0];
    else if (grid[0][2] == grid[1][1] && grid[0][2] == grid[2][0]) winner = grid[0][2];

    if (winner != '_') {
        printf("\n%c Wins!!!\n", winner);
        return 1;
    };
    
    for (int i = 0; i < 3 && allMarked; i++) {
        for (int j = 0; j < 3 && allMarked; j++) {
            if (grid[i][j] == '_') allMarked = 0;
        }
    }

    if (allMarked) {
        printf("\nDraw!\n");
        return 1;
    }

    return 0;
}
