#include <stdio.h>
#include <stdbool.h>

#define N 9

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", grid[i][j]);
        printf("\n");
    }
}

// Function to check if a number can be placed in a given cell
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check the row and column for the same number
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num)
            return false;
    }

    // Check the 3x3 subgrid for the same number
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num)
                return false;
        }
    }

    return true;
}

// Function to find the next empty cell
bool findEmptyCell(int grid[N][N], int *row, int *col) {
    for (*row = 0; *row < N; (*row)++) {
        for (*col = 0; *col < N; (*col)++) {
            if (grid[*row][*col] == 0)
                return true;
        }
    }
    return false;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // If there are no empty cells, the puzzle is solved
    if (!findEmptyCell(grid, &row, &col))
        return true;

    // Try placing numbers from 1 to 9 in the cell
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            // Recursive call to solve the rest of the puzzle
            if (solveSudoku(grid))
                return true;

            // If placing the number doesn't lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }

    // No valid number can be placed in the cell
    return false;
}

int main() {
    int grid[N][N];

    printf("Enter the Sudoku puzzle (use 0 for empty cells):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    if (solveSudoku(grid)) {
        printf("Sudoku solved successfully:\n");
        printGrid(grid);
    } else {
        printf("No solution exists for the given Sudoku puzzle.\n");
    }

    return 0;
}
