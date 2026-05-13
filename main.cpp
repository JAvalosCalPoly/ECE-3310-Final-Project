#include "puzzle.h"
#include "ui.h"
#include "Config.h"
#include "wordData.h"

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>

void printGrid(const std::vector<std::string>& grid) {
    for (int row = 0; row < static_cast<int>(grid.size()); row++) {
        std::cout << grid[row] << "\n";
    }
}

std::vector<std::string> getWordsForPuzzle(int amount) {
    std::vector<std::string> selectedWords;
    std::vector<int> usedIndexes;

    std::random_device rd;
    std::mt19937 gen(rd());

    while (selectedWords.size() < amount && selectedWords.size() < wordList.size()) {
        std::uniform_int_distribution<> distr(0, wordList.size() - 1);
        int randomIndex = distr(gen);
        bool alreadyUsed = false;

        for (int i = 0; i < usedIndexes.size(); i++) {
            if (usedIndexes[i] == randomIndex) {
                alreadyUsed = true;
            }
        }
        if (!alreadyUsed) {
            usedIndexes.push_back(randomIndex);
            selectedWords.push_back(wordList[randomIndex]);
        }
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