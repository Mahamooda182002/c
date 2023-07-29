#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define BOARD_WIDTH 20
#define BOARD_HEIGHT 10

// Function to draw the game board
void drawBoard(char board[BOARD_HEIGHT][BOARD_WIDTH], int snakeX[], int snakeY[], int snakeLength, int fruitX, int fruitY) {
    system("cls"); // Clear the console

    for (int i = 0; i < BOARD_WIDTH + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        printf("#");
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (i == fruitY && j == fruitX)
                printf("F"); // Draw the fruit
            else if (i == snakeY[0] && j == snakeX[0])
                printf("O"); // Draw the head of the snake
            else {
                bool isBodyPart = false;
                for (int k = 1; k < snakeLength; k++) {
                    if (i == snakeY[k] && j == snakeX[k]) {
                        printf("o"); // Draw the body of the snake
                        isBodyPart = true;
                        break;
                    }
                }
                if (!isBodyPart)
                    printf(" ");
            }
        }
        printf("#\n");
    }

    for (int i = 0; i < BOARD_WIDTH + 2; i++)
        printf("#");
    printf("\n");
}

int main() {
    char board[BOARD_HEIGHT][BOARD_WIDTH];

    // Initialize the game board
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board[i][j] = ' ';
        }
    }

    // Initialize the snake position and length
    int snakeX[100] = { BOARD_WIDTH / 2 };
    int snakeY[100] = { BOARD_HEIGHT / 2 };
    int snakeLength = 1;

    // Initialize the fruit position
    int fruitX = rand() % BOARD_WIDTH;
    int fruitY = rand() % BOARD_HEIGHT;

    // Game loop
    bool game_over = false;
    while (!game_over) {
        // Draw the game board
        drawBoard(board, snakeX, snakeY, snakeLength, fruitX, fruitY);

        // User input
        if (_kbhit()) {
            switch (_getch()) {
                case 'w':
                    snakeY[0]--;
                    break;
                case 'a':
                    snakeX[0]--;
                    break;
                case 's':
                    snakeY[0]++;
                    break;
                case 'd':
                    snakeX[0]++;
                    break;
                case 'x':
                    game_over = true;
                    break;
            }
        }

        // Check for collisions with the fruit
        if (snakeX[0] == fruitX && snakeY[0] == fruitY) {
            // Increase the snake length
            snakeLength++;

            // Generate new fruit coordinates
            fruitX = rand() % BOARD_WIDTH;
            fruitY = rand() % BOARD_HEIGHT;
        }

        // Move the snake body
        for (int i = snakeLength - 1; i > 0; i--) {
            snakeX[i] = snakeX[i - 1];
            snakeY[i] = snakeY[i - 1];
        }

        // Check for collisions with the walls
        if (snakeX[0] < 0 || snakeX[0] >= BOARD_WIDTH || snakeY[0] < 0 || snakeY[0] >= BOARD_HEIGHT)
            game_over = true;

        // Check for collisions with the snake body
        for (int i = 1; i < snakeLength; i++) {
            if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
                game_over = true;
        }

        Sleep(100); // Slow down the game
    }

    printf("Game Over! Your score: %d\n", snakeLength - 1);
    return 0;
}
