#include<stdio.h>
#include<stdlib.h>

int val; // global to avoid using it frequently

void repeatCharacter(char character, int times) {
    for (int i = 0; i < times; i++)
        printf("%c", character);
}

void printNumber(int num) {
    int requiredDigits = num * 2 - 1; // for the pattern
    char *numStr;
    size_t numStrLen; // used only for numStrLen
    if (num == 0) {
        printf("|");
    } else if (num < 10) {
        repeatCharacter(num + '0', requiredDigits);
    } else {
        numStrLen = snprintf(NULL, 0, "%d", num) + 1;
        /* int snprintf(char *str, size_t size, const char *format, ...); from manual
           also, the +1 is to add the /0 null at the end, as with every string */

        numStr = malloc(numStrLen); // memory allocation for memory management
        sprintf(numStr, "%d", num);
        /* int sprintf(char *str, const char *format, ...); from manual
           the string will be stored in the pointer numStr, hence we used malloc
           if it is >=10, it stores first the 1, then the 0, and then /0 (null) */

        for (int i = 0; i < requiredDigits; i++) {
            printf("%c", numStr[i % (numStrLen - 1)]);
        }
        free(numStr);
    }
}

void printBoard(int board[][3]) {
    printf("\n");
    repeatCharacter(' ', val + 1);
    printf("A");
    repeatCharacter(' ', val * 2);
    printf("B");
    repeatCharacter(' ', val * 2);
    printf("C\n\n");
    // visualize the board (the game)
    for (int j = 0; j < 3; j++) {
        int num = 0;
        int widthToSatisfy = val * 2 - 1;  // total width
        int dashSidePadding = (widthToSatisfy - 1) / 2; // dashes
        int sidePadding = ((widthToSatisfy - 1) - ((num - 1) * 2)) / 2; // empty spaces
        if (num == 0)
            sidePadding = dashSidePadding;

        repeatCharacter(' ', 2);
        repeatCharacter(' ', sidePadding);
        printNumber(num);
        if (j != 2)
            repeatCharacter(' ', sidePadding);
    }
    printf("\n");

    for (int i = 0; i < val; i++) {
        for (int j = 0; j < 3; j++) {
            int num = board[i][j];
            int widthToSatisfy = val * 2 - 1;
            int dashSidePadding = (widthToSatisfy - 1) / 2;
            int sidePadding = ((widthToSatisfy - 1) - ((num - 1) * 2)) / 2;
            if (num == 0)
                sidePadding = dashSidePadding;

            repeatCharacter(' ', 2);
            repeatCharacter(' ', sidePadding);
            printNumber(num);
            if (j != 2)
                repeatCharacter(' ', sidePadding);
        }
        printf("\n");
    }

    int footer_length = 3 * (2 * val - 1) + 8; // length of dashes
    repeatCharacter('-', footer_length);
}

void moveToRod(int board[][3], int element, char to_rod) {
    int rowIndex, colIndex;
    for (int i = 0; i < val; i++) {
        for (int j = 0; j < 3; j++) { // j < 3 because there are A B C columns
            if (board[i][j] == element) {
                rowIndex = i; // assigns the current row index i
                colIndex = j; // assigns the current column index j
                break;
            }
        }
    }

    int toColumnIndex = to_rod - 'A'; // subtract from ASCII, for example, if to_rod = 'C' then C - A is 2 (if A = 0, B = 1, C = 2...)
    int toRowIndex;
    for (int i = val - 1; i >= 0; i--) {
        if (board[i][toColumnIndex] == 0) {
            toRowIndex = i;
            break;
        }
    }

    board[toRowIndex][toColumnIndex] = element;
    board[rowIndex][colIndex] = 0;
}

// recursion
void towerOfHanoi(int x, char from_rod, char to_rod, char aux_rod, int board[][3]) {
    if (x > 0) {
        towerOfHanoi(x - 1, from_rod, aux_rod, to_rod, board);
        printf("\n\n\n%c -> %c\n", from_rod, to_rod);
        moveToRod(board, x, to_rod);
        printBoard(board);
        towerOfHanoi(x - 1, aux_rod, to_rod, from_rod, board);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Error, %s <num>\n", argv[0]);
        return 0;
    }

    val = atoi(argv[1]);
    int board[val][3];

    for (int i = 0; i < val; i++) {
        for (int j = 0; j < 3; j++) {
            if (j == 0) {
                board[i][j] = i + 1;
            } else {
                board[i][j] = 0;
            }
        }
    }
    printBoard(board);
    towerOfHanoi(val, 'A', 'C', 'B', board);
    printf("\n");
    return 0;
}
