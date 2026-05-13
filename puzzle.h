#ifndef PUZZLE_H
#define PUZZLE_H

#include "cell.h"
#include "Config.h"
#include <vector>
#include <string>

class Puzzle {
    public:
    Puzzle();
    Puzzle(int rows, int cols);
    // build the grid from the list of words
    void loadGrid(const std::vector<std::string>& wordGrid);
    // getters
    int getRows();
    int getCols();
    // access
    cell& getCell(int row, int col);
    const cell& getCell(int row, int col) const;
    // are we in bounds?
    bool inBounds(int row, int col) const;
    // user input
    void setUsrLetter(int row, int col, char letter);
    void clearUsrLetter(int row, int col);
    // to check
    bool isBlack(int row, int col);
    bool isCellCorrect(int row, int col);
    bool isPuzzleComplete();
    
    // get grid, user will only read it so it is const btw :)
    const std::vector<std::vector<cell>>& getGrid() const;

    private:
        std::vector<std::vector<cell>> grid;
        int rows;
        int cols;
        // clue numebering, across, and down
        bool isAcrossStart(std::vector<std::vector<cell>>& grid, int row, int col);
        bool isDownStart(std::vector<std::vector<cell>>& grid, int row, int col);
        int getClueNum(std::vector<std::vector<cell>>& grid, int row, int col);
};

#endif