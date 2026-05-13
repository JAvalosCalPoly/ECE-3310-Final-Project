#include "score.h"

// Initialize starting values.
score::score() : userScore(0), correctWords(0), incorrectWords(0) {}

// Calculates score using the number of correct and incorrect words.
int score::calculateScore(int wordsCorrect, int wordsIncorrect) {
    correctWords = wordsCorrect;
    incorrectWords = wordsIncorrect;

    userScore = (correctWords * POINTS_PER_WORD)
        - (incorrectWords * POINTS_PER_PENALTY);

    return userScore;
}

// Returns the player's current score.
int score::getScore() {
    return userScore;
}

// Returns how many full words are correct.
int score::getCorrectWords() {
    return correctWords;
}

// Returns how many attempted words are incorrect.
int score::getIncorrectWords() {
    return incorrectWords;
}
