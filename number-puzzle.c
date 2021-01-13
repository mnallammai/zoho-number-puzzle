#include<stdio.h> // header for input output
#include<conio.h> // header for getch
#include<stdlib.h> // header for clearing screen
#include<time.h> // header used to generate different random number every time

static const int EMPTY_SQUARE_VALUE = -1;

void printInstructions() {
    printf("\n\t\t\tNUMBER PUZZLE GAME!\n");
    printf("\tArrange Elements from 1 to 15 in ascending order and leave the hyphen (-) at the last\n");
    printf("\t\t\t\t RULES\n");
    printf("\t\t 1.Press LEFT ARROW KEY(<) for LEFT\n");
    printf("\t\t 2.Press RIGHT ARROW KEY(>) for RIGHT\n");
    printf("\t\t 3.Press DOWN ARROW KEY for DOWN\n");
    printf("\t\t 4.Press UP ARROW KEY for UP\n");
    printf("\t\t 5.Press q to quit the game!\n\n");
}

void printSquareBoard(int size, int play_square[size][size],
                      int keypress) { //Its enough to display play square alone to user hence it is passed as parameter
    system(CLEAR_CMD);
    printInstructions();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; printf(" -----"), j++);
        printf("\n|  ");
        for (int j = 0; j < size; j++)
            if (play_square[i][j] == EMPTY_SQUARE_VALUE)
                printf("-  |  ");
            else if (play_square[i][j] < 10)
                printf("%d  |  ", play_square[i][j]);
            else
                printf("%d |  ", play_square[i][j]);
        printf("\n");
    }
    for (int j = 0; j < size; printf(" -----"), j++);
    printf("\n");
    printf("Moves : %d \n", keypress);
}

int won(int size, int play_square[size][size]) {
    // Check if the expected square is same as the play square

    int i, j, value;

    for (i = 0, value = 1; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (play_square[i][j] != value++) {

                break;
            }
        }
    }
    if (i == size && j == size - 1&& play_square[size-1][size-1] == EMPTY_SQUARE_VALUE) {
        return 1;
    } else {
        return 0;
    }
}

void swap(int size, int play_square[size][size], int row1, int col1, int row2, int col2) {
    int temp = play_square[row1][col1];
    play_square[row1][col1] = play_square[row2][col2];
    play_square[row2][col2] = temp;
}

void moveUp(int size, int **play_square, int *row, int *column) {
    if (*row > 0) {
        swap(size, play_square, *row, *column, (*row)--, *column);
    } else {
        printf("\a"); //if position not available provides a bell sound
    }
}

void moveDown(int size, int **play_square, int *row, int *column) {
    if (*row < size - 1) {
        swap(size, play_square, *row, *column, (*row)++, *column);
    } else {
        printf("\aInvalid move"); //if position not available provides a bell sound
    }
}

void moveRight(int size, int **play_square, int *row, int *column) {
    if (*column < size - 1) {
        swap(size, play_square, *row, *column, *row, (*column)++);
    } else {
        printf("\a Invalid move");
    }
}

void moveLeft(int size, int **play_square, int *row, int *column) {
    if (*column > 0) {
        swap(size, play_square, *row, *column, *row, (*column)--);
    } else {
        printf("\a Invalid move");
    }
}

void initializePlaySquare(int size, int play_square[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            play_square[i][j] = ((i*size) + j) + 1;
        }
    }
    // Set the last square as
    play_square[size - 1][size - 1] = EMPTY_SQUARE_VALUE;
}

void shufflePlaySquare(int size, int play_square[size][size]) {
    // Shuffle the play square using Fisher�Yates shuffle algorithm
    // Feed the seed value so that each time the shuffling happens better
    srand(time(0));
    int total_size = size * size;
    for (int row = 0; row < size; row++){
        for (int col = 0; col < size; col++){
            int random_number = rand() % total_size;
            int exchange_row = random_number / size;
            int exchange_col = random_number % size;
            // Skip the empty row box.
            if ((row == size - 1 && col == size - 1) || (exchange_row == size - 1 && exchange_col == size - 1)) {
                continue;
            }
            int tmp = play_square[row][col];
            play_square[row][col] = play_square[exchange_row][exchange_col];
            play_square[exchange_row][exchange_col] = tmp;
        }
    }
}

void startGame(int size, int play_square[size][size], int zero_row, int zero_column) {
    int keypress = 0;
    while (1) {

        printSquareBoard(size, play_square, keypress);
        //Check if won
        if (won(size, play_square)) {
            printf(" You Won this puzzle game\n Number of Moves : %d\n Thanks for playing this game!", keypress);
            break;
        }
        char c = getch();
        //when arrow key is pressed in getch input two values are sent by compiler -32 and the other is 72,80,75 or 77 based on arrow key. so get
        //until q or arrow pressed
        while (c != 'q' && c != -32) {
            printf("Enter proper choice\n");
            c = getch();
            printf("%c | %d\n", c,c);
        }
        //getch() for getting arrow keys input from the user
        if (c == 'q')
            break;
        //Check which arrow key is pressed

        switch (getch()) {
            case 72:    // Up arrow
                moveUp(size, play_square, &zero_row, &zero_column);
                keypress++;
                break;
            case 80:    // Down arrow
                moveDown(size, play_square, &zero_row, &zero_column);
                keypress++;
                break;
            case 77:    // Right arrow
                moveRight(size, play_square, &zero_row, &zero_column);
                keypress++;
                break;
            case 75:    // Left arrow
                moveLeft(size, play_square, &zero_row, &zero_column);
                keypress++;
                break;
            default:
                printf("Invalid Input");
        }

    }
}

int main() {
    int size, game_level;
    printf("Select the difficulty level of game\n");
    printf("\t1.Easy (3x3)\n");
    printf("\t2.Medium (4x4)\n");
    printf("\t3.Hard (5x5) [Default level]\n");
    scanf("%d", &game_level);

    switch (game_level) {
        case 1:
            size = 3;
            break;
        case 2:
            size = 4;
            break;
        default:
            size = 5;
            break;
    }

    int play_square[size][size];
    int zero_row = size - 1, zero_column = size - 1;

    initializePlaySquare(size, play_square);
    shufflePlaySquare(size, play_square);
    startGame(size, play_square, zero_row, zero_column);
}
