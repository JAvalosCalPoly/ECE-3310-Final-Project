#ifndef UI_H
#define UI_H

#include "puzzle.h"
#include "score.h"
#include <vector>
#include <string>


class UI {
    public:
        enum Direction { across, down};
        UI(Puzzle* puzzle);
        void run();

    private:
        Puzzle* puzzle;
        int cursorRow;
        int cursorCol;
        
        bool isRunning;
        score gameScore;
        void render();
        void renderGrid();
        void renderScore();
        void renderGameBoard();
        void renderBoardWithHints();
        std::string getGridLine(int row);
        std::string getHintLine(int index);

        // std::vector<std::string> puzzleWords;
        // std::vector<std::string> puzzleHints;

        void doInput();
        void moveCursor(int rowDiff, int colDiff);
        void typeLetter(char letter);
        void clearLetter();
        Direction currentDirection;
};

#endif