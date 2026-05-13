#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <string>

using namespace std;

struct PlacementChange {
    int row;
    int col;
};

bool canPlaceWord(vector<string>& grid, string word, int row, int col, char dir);

vector<PlacementChange> placeWord(vector<string>& grid, string word, int row, int col, char dir);

void removeWord(vector<string>& grid, vector<PlacementChange>& changedCells);

bool generate(vector<string>& grid, vector<string>& words, int index);

//void printGrid(vector<string>& grid);

void addRandomBlocks(vector<string>& grid, int numberOfBlocks);

#endif
