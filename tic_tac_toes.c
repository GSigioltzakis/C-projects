#include<stdio.h>
// Initially, I will create a function that will display the tic-tac-toe board and update it.
void printBoard(char keno[9]) {
    printf(" %c | %c | %c \n", keno[0], keno[1], keno[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", keno[3], keno[4], keno[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", keno[6], keno[7], keno[8]);
}

int main(){
    int i; // for loops
    char keno[9]; // the board where we will place the symbols
    
    for (i = 0; i < 9; i++) {
        keno[i] = ' ';
    }

    printBoard(keno);
    
    char player = 'X';
    int num; // the player's input
    int count = 11; // count to check if it's a tie
    
    while (1) {
        printf("Player %c: ", player);
        scanf("%d", &num); // asks for the player's input
        if (num >= 1 && num <= 9 && keno[num - 1] == ' ') {
            keno[num - 1] = player;
            printBoard(keno);

            for (i = 0; i < 9; i += 3) {
                if (keno[i] == keno[i + 1] && keno[i + 1] == keno[i + 2] && keno[i] != ' ') { // horizontal
                    printf("Player %c won\n", player);
                    return 0; // End the game
                }
            }

            for (i = 0; i < 3; i++) {
                if (keno[i] == keno[i + 3] && keno[i + 3] == keno[i + 6] && keno[i] != ' ') { // vertical
                    printf("Player %c won\n", player);
                    return 0; // End the game
                }
            }

            if ((keno[0] == keno[4] && keno[4] == keno[8] && keno[0] != ' ') || (keno[2] == keno[4] && keno[4] == keno[6] && keno[2] != ' ')) { // diagonal
                printf("Player %c won\n", player);
                return 0; // End the game
            }
            // switching players
            if (player == 'X') {
                player = '0';
            } else {
                player = 'X';
            }

        }/*else {
            printf("\0");    If I remove the comment, it will show a warning for \0 :D
        }*/
        count -= 1;
        if (count == 0) {
            printf("Tie\n");
            return 0;
        }    
    }
}
