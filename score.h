// score.h - header file for score.cpp
#include <iostream>
#include <string>
#include <vector>

// score.h - header file for score.cpp
#ifndef SCORE_H
#define SCORE_H

class score {
private:
    // Points added for each completely correct word.
    const int POINTS_PER_WORD = 10;

    // Points subtracted for each attempted but incorrect word.
    const int POINTS_PER_PENALTY = 3;

    // Stores the player's current score.
    int userScore;

    // Stores how many full words are currently correct.
    int correctWords;

    // Stores how many attempted words are currently incorrect.
    int incorrectWords;

public:
    // Default constructor.
    score();

    // Recalculates the score based on the current puzzle.
    int calculateScore(int wordsCorrect, int wordsIncorrect);

    // Returns the current score.
    int getScore();

    // Returns the number of correct full words.
    int getCorrectWords();

    // Returns the number of incorrect attempted words.
    int getIncorrectWords();
};

#endif

