#include<stdio.h>
//arxika tha kano mia sinartisi pou tha vlepoume tin triliza (pinaka) kai tha ton alazoume
void printBoard(char keno[9]) {
    printf(" %c | %c | %c \n", keno[0], keno[1], keno[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", keno[3], keno[4], keno[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", keno[6], keno[7], keno[8]);
}

int main(){
	int i; //gia for loops
	char keno[9]; //o pinakas pou tha vazoume ta simvola
	
	for (i=0; i < 9; i++){
			keno[i] = ' ';
	}

	printBoard(keno);
	
	char player = 'X';
	int num; //i apadsisi tou paikti
	int count = 11; //count ama einai tie
	
	while (1) {
		printf("Player %c: ", player);
		scanf("%d", &num); //asks the answer
		if (num >= 1 && num <= 9 && keno[num - 1] == ' ') {
            keno[num - 1] = player;
            printBoard(keno);


			for (i = 0; i < 9; i += 3) {
                if (keno[i] == keno[i + 1] && keno[i + 1] == keno[i + 2] && keno[i] != ' ') {//orizodies
                    printf("Player %c won\n", player);
                    return 0; // End the game
                }
            }

            for (i = 0; i < 3; i++) {
                if (keno[i] == keno[i + 3] && keno[i + 3] == keno[i + 6] && keno[i] != ' ') {//kathetes
                    printf("Player %c won\n", player);
                    return 0; // End the game
                }
            }

            if ((keno[0] == keno[4] && keno[4] == keno[8] && keno[0] != ' ') || (keno[2] == keno[4] && keno[4] == keno[6] && keno[2] != ' ')) { //diagonies
                printf("Player %c won\n", player);
                return 0; // End the game
            }
			//switching players
			if (player == 'X') {
				player = '0';
			} else {
				player = 'X';
			}

		}/*else {
			printf("\0");    AN to vgalo apo comment tha mou emfanisei warning gia to \0 :D
		}*/
		count -=1;
		if (count==0) {
			printf("Tie\n");
			return 0;
		}	
	}
}