#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define BOARD_SIZE 8

// Function to display the Chess board
void displayBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    printf("\n   A B C D E F G H\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("%d\n", i + 1);
    }
    printf("   A B C D E F G H\n");
}

// Function to initialize the Chess board with pieces
void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    // Set up black pieces
    board[0][0] = board[0][7] = 'r';
    board[0][1] = board[0][6] = 'n';
    board[0][2] = board[0][5] = 'b';
    board[0][3] = 'q';
    board[0][4] = 'k';

    for (int i = 0; i < BOARD_SIZE; i++) {
        board[1][i] = 'p';
    }

    // Set up white pieces
    board[7][0] = board[7][7] = 'R';
    board[7][1] = board[7][6] = 'N';
    board[7][2] = board[7][5] = 'B';
    board[7][3] = 'Q';
    board[7][4] = 'K';

    for (int i = 0; i < BOARD_SIZE; i++) {
        board[6][i] = 'P';
    }

    // Fill the empty cells with '-'
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = '-';
        }
    }
}

// Function to convert the user's input to board coordinates
bool convertInputToCoords(char input[3], int *row, int *col) {
    if (input[0] >= 'A' && input[0] <= 'H' && input[1] >= '1' && input[1] <= '8') {
        *col = input[0] - 'A';
        *row = input[1] - '1';
        return true;
    }
    return false;
}

// Function to check if the move is valid
bool isValidMove(char board[BOARD_SIZE][BOARD_SIZE], int startRow, int startCol, int endRow, int endCol) {
    char piece = board[startRow][startCol];
    char targetPiece = board[endRow][endCol];

    // Check if the start position contains a piece and it belongs to the current player
    if (piece == '-') {
        return false;
    }

    // Check if the destination is within the board
    if (endRow < 0 || endRow >= BOARD_SIZE || endCol < 0 || endCol >= BOARD_SIZE) {
        return false;
    }

    // Check if the piece moves according to its valid moves
    // (The rules for valid moves are not fully implemented in this simplified version)
    // For example, pawns can move forward one or two squares, bishops diagonally, etc.
    // Knights have more complex moves.
    // Note: This implementation does not consider special rules like castling and en passant.
    // It also does not handle checkmate conditions.
    switch (tolower(piece)) {
        case 'p':
            if (startRow == 1) { // First move for black pawns
                if ((endRow == startRow + 1 || endRow == startRow + 2) && endCol == startCol && targetPiece == '-') {
                    return true;
                }
            } else {
                if (endRow == startRow + 1 && endCol == startCol && targetPiece == '-') {
                    return true;
                }
            }
            break;
        case 'r':
        case 'n':
        case 'b':
        case 'q':
        case 'k':
            // Add the specific rules for these pieces (rook, knight, bishop, queen, king) as needed
            // For simplicity, we assume that any move is valid for these pieces in this example.
            return true;
    }

    return false;
}

int main() {
    char board[BOARD_SIZE][BOARD_SIZE];
    char input[3];
    int startRow, startCol, endRow, endCol;

    initializeBoard(board);
    displayBoard(board);

    // Main game loop
    while (true) {
        printf("Enter your move (e.g., A2 A4): ");
        scanf("%s", input);

        if (!convertInputToCoords(input, &startRow, &startCol)) {
            printf("Invalid input. Please enter a valid move (e.g., A2 A4).\n");
            continue;
        }

        scanf("%s", input);

        if (!convertInputToCoords(input, &endRow, &endCol)) {
            printf("Invalid input. Please enter a valid move (e.g., A2 A4).\n");
            continue;
        }

        if (isValidMove(board, startRow, startCol, endRow, endCol)) {
            board[endRow][endCol] = board[startRow][startCol];
            board[startRow][startCol] = '-';
            displayBoard(board);
        } else {
            printf("Invalid move. Try again.\n");
        }
    }

    return 0;
}
