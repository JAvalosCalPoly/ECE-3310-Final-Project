#include <iostream>
#include "Config.h"
#include <algorithm>
#include <random>

using namespace std;

bool isLetterCell(char cell) {
    return cell != '.' && cell != '#';
}

bool canPlaceWord(vector<string>& grid, string word, int row, int col, char dir) {
    int n = grid.size();
    int wordLength = word.length();
    bool hasIntersection = false;

    // Check if word fits inside grid - added by Jonathan
    if (dir == 'A') {
        if (col + wordLength > n) {
            return false;
        }
    }
    else {
        if (row + wordLength > n) {
            return false;
        }
    }

    // Check cell before the word - added by Jonathan
    if (dir == 'A') {
        if (col > 0 && isLetterCell(grid[row][col - 1])) {
            return false;
        }
    }
    else {
        if (row > 0 && isLetterCell(grid[row - 1][col])) {
            return false;
        }
    }

    // Check cell after the word - added by Jonathan
    if (dir == 'A') {
        int afterCol = col + wordLength;

        if (afterCol < n && isLetterCell(grid[row][afterCol])) {
            return false;
        }
    }
    else {
        int afterRow = row + wordLength;

        if (afterRow < n && isLetterCell(grid[afterRow][col])) {
            return false;
        }
    }

    for (int i = 0; i < word.length(); i++) {
        int r = row;
        int c = col;

        if (dir == 'A')
            c += i;
        else
            r += i;

        if (r >= n || c >= n)
            return false;

        if (grid[r][c] == '#')
            return false;

        if (grid[r][c] != '.' && grid[r][c] != word[i])
            return false;

        if (grid[r][c] == word[i])
            hasIntersection = true;
        // - added by Jonathan to check if the word is being placed next to another word without intersecting
        if (grid[r][c] == '.') {
        if (dir == 'A') {
            if (r > 0 && isLetterCell(grid[r - 1][c])) {
                return false;
            }

            if (r + 1 < n && isLetterCell(grid[r + 1][c])) {
                return false;
            }
        }
        else {
            if (c > 0 && isLetterCell(grid[r][c - 1])) {
                return false;
            }

            if (c + 1 < n && isLetterCell(grid[r][c + 1])) {
                return false;
            }
        }
    }
    }
      //
    

    bool gridEmpty = true;

    for (string rowData : grid) {
        for (char cell : rowData) {
            if (cell != '.' && cell != '#') {
                gridEmpty = false;
            }
        }
    }

    if (gridEmpty)
        return true;

    return hasIntersection;
}

vector<PlacementChange> placeWord(vector<string>& grid, string word, int row, int col, char dir) {
    vector<PlacementChange> changedCells;

    for (int i = 0; i < word.length(); i++) {
        int r = row;
        int c = col;

        if (dir == 'A')
            c += i;
        else
            r += i;

        if (grid[r][c] == '.') {
            changedCells.push_back({ r, c });
            grid[r][c] = word[i];
        }
    }

    return changedCells;
}

void removeWord(vector<string>& grid, vector<PlacementChange>& changedCells) {
    for (PlacementChange cell : changedCells) {
        grid[cell.row][cell.col] = '.';
    }
}

//Backtracking function to generate the crossword puzzle
bool generate(vector<string>& grid, vector<string>& words, int index) {
    int n = grid.size();

    if (index == words.size())
        return true;

    string word = words[index];

vector<int> rows(n);
vector<int> cols(n);

for (int i = 0; i < n; i++) {
    rows[i] = i;
    cols[i] = i;
}

random_device rd;
mt19937 rng(rd());

shuffle(rows.begin(), rows.end(), rng);
shuffle(cols.begin(), cols.end(), rng);

for (int row : rows) {
    for (int col : cols) {

            if (canPlaceWord(grid, word, row, col, 'A')) {
                vector<PlacementChange> changes = placeWord(grid, word, row, col, 'A');

                if (generate(grid, words, index + 1))
                    return true;

                removeWord(grid, changes);
            }

            if (canPlaceWord(grid, word, row, col, 'D')) {
                vector<PlacementChange> changes = placeWord(grid, word, row, col, 'D');

                if (generate(grid, words, index + 1))
                    return true;

                removeWord(grid, changes);
            }
        }
    }

    return false;
}

//Function to print the grid for testing purposes
/*void printGrid(vector<string>& grid) {
    for (string row : grid) {
        for (char cell : row) {
            cout << cell << ' ';
        }
        cout << endl;
    }
}*/

void addRandomBlocks(vector<string>& grid, int numberOfBlocks) {
    int n = grid.size();

    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> dist(0, n - 1);

    int placed = 0;

    while (placed < numberOfBlocks) {
        int row = dist(rng);
        int col = dist(rng);

        if (grid[row][col] == '.') {
            grid[row][col] = '#';
            placed++;
        }
    }
}
