#include "ui.h"
#include <iostream>
#include <string>
#include <conio.h>

UI::UI(Puzzle* puzzle) {
    this->puzzle = puzzle; // puzzle
    cursorRow = 0; // starting row
    cursorCol = 0; // starting column
    currentDirection = across; // starting direction
    isRunning = true; // game is running
    if (this->puzzle != nullptr) {
        bool validStart = false;
        for (int i = 0; i < this->puzzle->getRows(); i++) {
            for (int j = 0; j < this->puzzle->getCols(); j++) {
                if (!this->puzzle->isBlack(i, j)) {
                    cursorRow = i;
                    cursorCol = j;
                    validStart = true;
                    break;
                }
            }
            if (validStart) break;
        }
    }
}

void UI::run() {
    while (isRunning) {
        render();
        doInput();
    }
}

void UI::render() {
    // clear terminal by printing newlines
    std::cout << std::string(100, '\n');

    std::cout << "-------------------- CROSSWORD PUZZLE --------------------\n";

    renderBoardWithHints();

    std::cout << "\n";
    renderScore();

    std::cout << "\nControls:\n";
    std::cout << "arrows    = to move\n";
    std::cout << ":t        = toggle across or down\n";
    std::cout << ":x        = clear letter\n";
    std::cout << ":q        = quit\n";
}

void UI::renderBoardWithHints() {
    if (puzzle == nullptr) {
        std::cout << "No puzzle loaded.\n";
        return;
    }

    int totalLines = puzzle->getRows();

    int hintLines = 2;

    if (puzzle != nullptr) {
        hintLines += puzzle->getAcrossHints().size();
        hintLines += puzzle->getDownHints().size();
    }

    if (hintLines > totalLines) {
        totalLines = hintLines;
    }

    int gridWidth = puzzle->getCols() * 4; 

    std::cout << "PUZZLE";
    std::cout << std::string(gridWidth, ' ');
    std::cout << "HINTS\n";

    std::cout << "------";
    std::cout << std::string(gridWidth, ' ');
    std::cout << "------\n";

    for (int i = 0; i < totalLines; i++) {
        if (i < puzzle->getRows()) {
            std::cout << getGridLine(i);
        }
        else {
            std::cout << std::string(puzzle->getCols() * 4, ' ');
        }

        std::cout << std::string(gridWidth - 35, ' ');

        if (i < hintLines) {
            std::cout << getHintLine(i);
        }

        std::cout << "\n";
    }
}

std::string UI::getGridLine(int row) {
    std::string line = "";

    for (int j = 0; j < puzzle->getCols(); j++) {
        if (puzzle->isBlack(row, j)) {
            line += " ## ";
        }
        else {
            char displayChar = puzzle->getCell(row, j).getUsrLetter();

            if (displayChar == ' ') {
                displayChar = '_';
            }

            if (row == cursorRow && j == cursorCol) {
                line += "[";
                line += displayChar;
                line += "] ";
            }
            else {
                line += " ";
                line += displayChar;
                line += "  ";
            }
        }
    }

    return line;
}

std::string UI::getHintLine(int index) {
    std::string line = "";

    if (puzzle == nullptr) {
        return line;
    }

    const std::map<int, std::string>& across = puzzle->getAcrossHints();
    const std::map<int, std::string>& down = puzzle->getDownHints();

    int currentIndex = 0;

    if (index == 0) {
        return "Across:\n";
    }

    currentIndex = 1;

    for (std::map<int, std::string>::const_iterator it = across.begin(); it != across.end(); ++it) {
        if (currentIndex == index) {
            line += std::to_string(it->first);
            line += ". ";
            line += it->second;
            return line;
        }

        currentIndex++;
    }
    if (currentIndex == index) {
        return "Down:";
    }

    currentIndex++;

    for (std::map<int, std::string>::const_iterator it = down.begin(); it != down.end(); ++it) {
        if (currentIndex == index) {
            line += std::to_string(it->first);
            line += ". ";
            line += it->second;
            return line;
        }

        currentIndex++;
    }

    return line;
}

void UI::renderGrid() {
    if (puzzle == nullptr) {
        std::cout << "No puzzle loaded.\n";
        return;
    }
    for (int i = 0; i < puzzle->getRows(); i++) {
        for (int j = 0; j < puzzle->getCols(); j++) {
            if (puzzle->isBlack(i,j)) {
                std::cout << "##";
            } else {
                char displayChar = puzzle->getCell(i,j).getUsrLetter();
                if (displayChar == ' ') {
                    displayChar = '_';
                }
                if (i == cursorRow && j == cursorCol) {
                    std::cout << "['" << displayChar << "']";
                } else {
                    std::cout << " " << displayChar << " ";
                }
            }
        }
        std::cout << "\n";
    }
}

void UI::renderScore() {
    std::cout << "Score: " << gameScore.getScore() << "\n";
}

void UI::doInput() {
    unsigned char input;
    input = _getch();
    if (input == ':') {
        int command = _getch();
        if (command == 'q' || command == 'Q') {
            isRunning = false;
        }
        else if (command == 't' || command == 'T') {
            currentDirection = (currentDirection == across) ? down : across;
        }
        else if (command == 'x' || command == 'X') {
            clearLetter();
        }
        return;
    }

    // arrow keys
    if (input == 224 || input == 0) {
        char arrow = _getch();
        if (arrow == 72) { // up
            moveCursor(-1, 0);
        }
        else if (arrow == 80) { // down
            moveCursor(1, 0);
        }
        else if (arrow == 75) { // left
            moveCursor(0, -1);
        }
        else if (arrow == 77) { // right
            moveCursor(0, 1);
        }
        return;
    }
    // when it is a letter input
    if ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z')) {
        typeLetter(static_cast<char>(input));
    }
}

void UI::moveCursor(int rowDiff, int colDiff) {
    if (puzzle == nullptr) return;
    int newRow = cursorRow + rowDiff;
    int newCol = cursorCol + colDiff;
    while (puzzle->inBounds(newRow, newCol)) {
        if (!puzzle->isBlack(newRow, newCol)) {
            cursorRow = newRow;
            cursorCol = newCol;
            return;
        }
        newRow += rowDiff;
        newCol += colDiff;
    }
}

void UI::typeLetter(char letter) {
    if (puzzle == nullptr) return;
    if (!puzzle->inBounds(cursorRow, cursorCol)) {
        return;
    }
    if (puzzle->isBlack(cursorRow, cursorCol)) {
        return;
    }
    // uppercase to lowercase
    if (letter >= 'A' && letter <= 'Z') {
        letter = letter - 'A' + 'a';
    }
    puzzle->setUsrLetter(cursorRow, cursorCol, letter);
    
    if (puzzle->isPuzzleComplete()) {
        render();
        std::cout << "Congratulations! You've completed the puzzle!\n";
        isRunning = false;
        return;
    }
    if (currentDirection == across) {
        moveCursor(0, 1);
    }
    else {
        moveCursor(1, 0);
    }
}

void UI::clearLetter() {
    if (puzzle == nullptr) return;
    if (!puzzle->inBounds(cursorRow, cursorCol)) {
        return;
    }
    if (puzzle->isBlack(cursorRow, cursorCol)) {
        return;
    }
    puzzle->clearUsrLetter(cursorRow, cursorCol);
}