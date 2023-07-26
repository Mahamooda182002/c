#include <stdio.h>

// Function to display the Tic-Tac-Toe board
void display_board(char board[3][3]) {
    printf("\n  1 2 3\n");
    for (int i = 0; i < 3; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < 3; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Function to check if a player has won
int check_win(char board[3][3], char player) {
    // Check rows, columns, and diagonals
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return 1; // Row win
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return 1; // Column win
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return 1; // Diagonal win
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return 1; // Diagonal win

    return 0;
}

int main() {
    char board[3][3];
    char player = 'X';
    int row, col;
    int moves = 0;
    
    // Initialize the board with empty spaces
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }

    printf("Welcome to Tic-Tac-Toe!\n");
    display_board(board);

    // Main game loop
    while (1) {
        printf("Player %c, enter row (1-3) and column (1-3) separated by space: ", player);
        scanf("%d %d", &row, &col);

        // Convert input to array indices
        row--;
        col--;

        // Check if the chosen cell is empty
        if (board[row][col] == ' ') {
            board[row][col] = player;
            moves++;
            display_board(board);

            // Check if the current player has won
            if (check_win(board, player)) {
                printf("Player %c wins!\n", player);
                break;
            }

            // Check if the game is a draw
            if (moves == 9) {
                printf("It's a draw!\n");
                break;
            }

            // Switch to the other player
            player = (player == 'X') ? 'O' : 'X';
        } else {
            printf("Cell already taken. Try again.\n");
        }
    }

    return 0;
}
