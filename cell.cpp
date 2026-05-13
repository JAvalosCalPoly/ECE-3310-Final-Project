// cell.cpp
#include "cell.h"

// constructor
cell::cell() {
    usr_letter = ' ';
    right_letter = ' ';
    is_black = false;
    is_across_start = false;
    is_down_start = false;
    clue_num = 0;
}
// destructor
cell::~cell() {
}
// default
cell::cell (char letter, bool black, bool across_start, bool down_start, int num) {
    usr_letter = ' ';
    right_letter = letter;
    is_black = black;
    is_across_start = across_start;
    is_down_start = down_start;
    clue_num = num;
}
void cell::setUsrLetter(char letter) {
    usr_letter = letter;
}

void cell::setBlack(bool black) {
    is_black = black;
}

bool cell::getCellType() {
    return is_black;
}

void cell::setLetter(char letter) {
    right_letter = letter;
}

char cell::getUsrLetter() {
    return  usr_letter;
}

char cell::getLetter() {
    return right_letter;
}

void cell::setIsAcrossStart(bool is_start) {
    is_across_start = is_start;
}

bool cell::getIsAcrossStart() {
    return is_across_start;
}

void cell::setIsDownStart(bool is_start) {
    is_down_start = is_start;
}

bool cell::getIsDownStart() {
    return is_down_start;
}

void cell::setClueNum(int num) {
    clue_num = num;
}

int cell::getClueNum() {
    return clue_num;
}

bool cell::isCorrect() {
    return usr_letter == right_letter;
}