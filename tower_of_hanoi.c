#include<stdio.h>
#include<stdlib.h>

int val; //global gia na m in itn xrisimopoio sixna



void repeatCharacter(char character, int times) {
    for (int i = 0; i < times; i++)
        printf("%c", character);
}

void printNumber(int num) {
    int requiredDigits = num * 2 - 1; //gia to motivo
    char *numStr;
    size_t numStrLen; //to xrisomopoio mono gia to numStrLen
    if (num == 0) {
        printf("|");
    } else if (num < 10) {
        repeatCharacter(num + '0', requiredDigits);
    } else {
        numStrLen = snprintf(NULL, 0, "%d", num) + 1;
        /*int snprintf(char *str, size_t size, const char *format, ...); apo manual
        episis to +1 gia na prosthesei sto telos to /0 null, opos einai kathe sting*/

        numStr = malloc(numStrLen); //mem allocate diaxirisi mnimis
        sprintf(numStr, "%d", num);
        /*int sprintf(char *str, const char *format, ...); apo manual
        to string tha apothikefti sto pointer numStr giafto kai kaname malloc
        ama diladi einai >=10 tote apothikevete prota to 1 kai meta to 0 kai meta to /0(null) */

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
    //visualize ton pinaka(to paixnidi)
    for (int j = 0; j < 3; j++) {
        int num = 0;
        int widthToSatisfy = val * 2 - 1;  //total width
        int dashSidePadding = (widthToSatisfy - 1) / 2; //pavles
        int sidePadding = ((widthToSatisfy - 1) - ((num - 1) * 2)) / 2; //empty space ta kena
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

    int footer_length = 3 * (2 * val - 1) + 8; //length of dashes
    repeatCharacter('-', footer_length);
}

void moveToRod(int board[][3], int element, char to_rod) {
    int rowIndex, colIndex;
    for (int i = 0; i < val; i++) {
        for (int j = 0; j < 3; j++) { // j<3 giati einai A B C stiles (columns)
            if (board[i][j] == element) {
                rowIndex = i; //assigns the current row index i
                colIndex = j; //assigns the current row index j
                break;
            }
        }
    }

    int toColumnIndex = to_rod - 'A'; //afairesi apo ASCII an paradeigma to to_rod = 'C' tote C-A kanei 2(an A=0, B=1, C=3...)
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
//anadromi
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