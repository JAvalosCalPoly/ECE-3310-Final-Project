// score.h - header file for score.cpp
#include <iostream>
#include <string>
#include <vector>

// score.h - header file for score.cpp
#ifndef SCORE_H
#define SCORE_H

class score {
private:
    // Points added for each fully completed correct word.
    const int POINTS_PER_COMPLETED_WORD = 5;

    // Stores the player's current score.
    int userScore;

    // Stores how many full words are currently completed correctly.
    int completedWords;

    // Stores how many letters are correct.
    int correctLetters;

public:
    // Default constructor.
    score();

    // Recalculates the score based on correct letters and completed words.
    int calculateScore(int lettersCorrect, int wordsCompleted);

    // Returns the current score.
    int getScore();

    // Returns the number of completed words.
    int getCompletedWords();

    // Returns how many letters are correct.
    int getCorrectLetters();
};

#endif
