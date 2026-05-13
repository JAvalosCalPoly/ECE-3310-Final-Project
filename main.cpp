#include "puzzle.h"
#include "ui.h"
#include "Config.h"
#include "wordData.h"

#include <iostream>
#include <vector>
#include <string>

void printGrid(const std::vector<std::string>& grid) {
    for (int row = 0; row < static_cast<int>(grid.size()); row++) {
        std::cout << grid[row] << "\n";
    }
}

std::vector<std::string> getWordsForPuzzle(int amount) {
    std::vector<std::string> selectedWords;

    for (int i = 0; i < amount && i < static_cast<int>(wordList.size()); i++) {
        selectedWords.push_back(wordList[i]);
    }

    return selectedWords;
}

int main() {
    std::cout << "Generating crossword puzzle...\n";

    int gridSize = 10;
    int numberOfBlocks = 0;
    int numberOfWords = 5;

    std::vector<std::string> words = getWordsForPuzzle(numberOfWords);

    std::vector<std::string> wordGrid;
    bool generated = false;

    for (int attempt = 0; attempt < 100 && !generated; attempt++) {
        wordGrid.clear();

        for (int i = 0; i < gridSize; i++) {
            wordGrid.push_back(std::string(gridSize, '.'));
        }

        if (numberOfBlocks > 0) {
            addRandomBlocks(wordGrid, numberOfBlocks);
        }

        generated = generate(wordGrid, words, 0);
    }

    if (!generated) {
        std::cout << "Could not generate puzzle.\n";
        return 1;
    }

    std::cout << "Generated raw puzzle:\n";
    printGrid(wordGrid);

    Puzzle puzzle;
    puzzle.loadGrid(wordGrid);

    UI ui(&puzzle);
    ui.run();

    std::cout << "\nThanks for playing!\n";

    return 0;
}