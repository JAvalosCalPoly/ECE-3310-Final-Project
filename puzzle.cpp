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

    // If grid is empty, stop here.
    if (rows == 0) {
        cols = 0;
        grid.clear();
        acrossHints.clear();
        downHints.clear();
        return;
    }

    cols = wordGrid[0].size();

    // Clear old data.
    grid.clear();
    acrossHints.clear();
    downHints.clear();

    // Make the grid the right size.
    grid.resize(rows, std::vector<cell>(cols));

    // Copy letters into the puzzle grid.
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char currentLetter = wordGrid[i][j];

            bool isBlack = false;

            if (currentLetter == '#' || currentLetter == '.') {
                isBlack = true;
            }

            if (isBlack) {
                grid[i][j] = cell(' ', true, false, false, 0);
            }
            else {
                grid[i][j] = cell(currentLetter, false, false, false, 0);
            }
        }
    }

    int clueNumber = 1;

    // Go left to right, top to bottom.
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            // Skip black cells.
            if (grid[i][j].getCellType()) {
                continue;
            }

            bool acrossStart = isAcrossStart(grid, i, j);
            bool downStart = isDownStart(grid, i, j);

            // Only number cells that start a word.
            if (acrossStart || downStart) {
                grid[i][j].setClueNum(clueNumber);
                grid[i][j].setIsAcrossStart(acrossStart);
                grid[i][j].setIsDownStart(downStart);

                // Add across hint.
                if (acrossStart) {
                    std::string word = getWordAcross(i, j);
                    std::string hint = findHintForWord(word);
                    acrossHints[clueNumber] = 
                        "(row " + std::to_string(i+1) +
                        ", col " + std::to_string(j+1) +
                        ") " + hint;
                }

                // Add down hint.
                if (downStart) {
                    std::string word = getWordDown(i, j);
                    std::string hint = findHintForWord(word);
                    downHints[clueNumber] = 
                        "(row " + std::to_string(i+1) + 
                        ", col " + std::to_string(j+1) +
                        ") " + hint;
                }

                clueNumber++;
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

    int clueNumber = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if(!grid[i][j].getCellType()) {
                bool startsAcross = isAcrossStart(grid, i, j);
                bool startsDown = isDownStart(grid, i, j);
                if (startsAcross || startsDown) {
                        clueNumber++;
                    }
                if (i == row && j == col) {
                    return clueNumber;
                }
            }
        }
    }
    return 0;
}

const std::map<int, std::string>& Puzzle::getAcrossHints() const {
    return acrossHints;
}

const std::map<int, std::string>& Puzzle::getDownHints() const {
    return downHints;
}

std::string Puzzle::getWordAcross(int row, int col) {
    std::string word = "";

    int currentCol = col;

    while (currentCol < cols && !grid[row][currentCol].getCellType()) {
        word += grid[row][currentCol].getLetter();
        currentCol++;
    }

    return word;
}

std::string Puzzle::getWordDown(int row, int col) {
    std::string word = "";

    int currentRow = row;

    while (currentRow < rows && !grid[currentRow][col].getCellType()) {
        word += grid[currentRow][col].getLetter();
        currentRow++;
    }

    return word;
}

// std::string Puzzle::findHintForWord(const std::string& word) {
//     for (int i = 0; i < static_cast<int>(wordList.size()) && i < static_cast<int>(hintList.size()); i++) {
//         if (wordList[i] == word) {
//             return hintList[i];
//         }
//     }

//     return "No hint found";
// }
std::string Puzzle::findHintForWord(const std::string& word) {
    for (int i = 0; i < static_cast<int>(wordList.size()) && i < static_cast<int>(hintList.size()); i++) {
        if (wordList[i] == word) {
            return hintList[i];
        }
    }

    return "No hint found for: " + word;
}
