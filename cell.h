// for the cells
#ifndef CELL_H
#define CELL_H
// cells in the crossword puzzle
class cell {
    public:

        // constructor
        cell();
        // default
        cell (char letter, bool black, bool across_start, bool down_start, int num);
        bool isCorrect(); // see if word is right
        // setters
        void setUsrLetter(char letter); // set the user's letter in the cell
        void setBlack(bool black); // set cell to black or not
        void setLetter(char letter); // set the letter in the cell
        void setIsAcrossStart(bool is_start); // set if cell starts an across word
        void setIsDownStart(bool is_start); // set if cell starts a down word
        void setClueNum(int num); // set the clue number for the cell
        // getters
        bool getCellType(); // see if cell is black or not
        char getUsrLetter(); // get the user's letter in the cell
        char getLetter(); // get the right letter in the cell
        bool getIsAcrossStart(); // see if cell starts an across word
        bool getIsDownStart(); // see if cell starts a down word
        int getClueNum(); // get the clue number for the cell
    private:
        char usr_letter = ' '; // the letter user input
        char right_letter = ' '; // the letter in the cell
        bool is_black = false; // cell is black or not
        bool is_across_start = false;   // starts an across word
        bool is_down_start = false;     // starts a down word
        int clue_num = 0; // clue number for the cell
};

#endif