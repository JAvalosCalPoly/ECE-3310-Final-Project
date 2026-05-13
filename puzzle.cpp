#include "puzzle.h"
#include "Config.h"
#include "trie.h"
#include "wordData.h"

Puzzle::Puzzle() {
    rows = 0;
    cols = 0;
}

Puzzle::Puzzle(int rows, int cols) {
    this->rows = rows; // set the number of rows
    this->cols = cols; // set the number of columns
    grid.resize(rows, std::vector<cell>(cols)); // initialize puzle with the dimensions
}

void Puzzle::loadGrid(const std::vector<std::string>& wordGrid) {
    rows = wordGrid.size();
    if (rows == 0) {
        cols = 0;
        grid.clear();
        return; // empty grid for whatever reason
    }
    cols = wordGrid[0].size();
    grid.clear();
    grid.resize(rows, std::vector<cell>(cols)); // initialize puzzle with the dimensions
    // loop through the grid and set the cells
    for (int i=0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char currentLetter = wordGrid[i][j];
            bool black = (currentLetter == '#');
            char letter = black ? ' ' : currentLetter; // if black
            grid[i][j] = cell(letter, black, false, false, 0); // cell with the letter and black status
        }
    }
    // clue numbering, across, and down
    for (int i=0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!grid[i][j].getCellType()) { // if we not black
                bool across_start = isAcrossStart(grid, i, j);
                bool down_start = isDownStart(grid, i, j);
                int clue_num = getClueNum(grid, i, j);
                grid[i][j].setIsAcrossStart(across_start);
                grid[i][j].setIsDownStart(down_start);
                grid[i][j].setClueNum(clue_num);
            }
        }
    }
}

int Puzzle::getRows() {
    return rows;
}

int Puzzle::getCols() {
    return cols;
}

cell& Puzzle::getCell(int row, int col) {
    return grid[row][col];
}

const cell& Puzzle::getCell(int row, int col) const {
    return grid[row][col];
}

bool Puzzle::inBounds(int row, int col) const {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

void Puzzle::setUsrLetter(int row, int col, char letter) {
    if (!inBounds(row, col)) return; // out of bounds :(
    if (grid[row][col].getCellType()) return; // black cell :(
    grid[row][col].setUsrLetter(letter);
}

void Puzzle::clearUsrLetter(int row, int col) {
    if (!inBounds(row, col)) return; // out of bounds :(
    if (grid[row][col].getCellType()) return; // black cell :(
    grid[row][col].setUsrLetter(' ');
}

bool Puzzle::isBlack(int row, int col) {
    if (!inBounds(row, col)) return false; // out of bounds :(
    return grid[row][col].getCellType();
}

bool Puzzle::isCellCorrect(int row, int col) {
    if (!inBounds(row, col)) return false;
    if (grid[row][col].getCellType()) return false;
    return grid[row][col].isCorrect();
}

bool Puzzle::isPuzzleComplete() {
    for (int i=0; i<rows;i++) {
        for (int j = 0; j < cols; j++) {
            if (!grid[i][j].getCellType() && !grid[i][j].isCorrect()) return false; // if there is a non black cell that is wrong
        }
    }
    return true;
}

const std::vector<std::vector<cell>>& Puzzle::getGrid() const {
    return grid; // grid
}

bool Puzzle::isAcrossStart(std::vector<std::vector<cell>>& grid, int row, int col) {
    if (grid[row][col].getCellType()) return false; // black cell cant have a word
    bool leftBlocked = (col == 0) || grid[row][col - 1].getCellType(); // left is black or out of bounds
    bool rightOpen = (col + 1) < cols && !grid[row][col + 1].getCellType(); // right is not black and in bounds
    return leftBlocked && rightOpen;
}

bool Puzzle::isDownStart(std::vector<std::vector<cell>>& grid, int row, int col) {
    if (grid[row][col].getCellType()) return false;
    bool upBlocked = (row == 0) || grid[row - 1][col].getCellType();
    bool downOpen = (row + 1) < rows && !grid[row + 1][col].getCellType();
    return upBlocked && downOpen;
}

int Puzzle::getClueNum(std::vector<std::vector<cell>>& grid, int row, int col) {
    if (grid[row][col].getCellType()) return 0; // black cell has no clue number

    int clueNumber = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if(!grid[i][j].getCellType()) {
                bool startsAcross = isAcrossStart(grid, i, j);
                bool startsDown = isDownStart(grid, i, j);

                if (i == row && j == col) {
                    if (startsAcross || startsDown) {
                        return clueNumber; // clue number
                    }
                        return 0; // not a clue start
                }
            }
        }
    }
    return 0;
}