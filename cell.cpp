// cell.cpp
#include "cell.h"

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