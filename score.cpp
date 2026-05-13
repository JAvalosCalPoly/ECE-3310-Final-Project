#include "score.h"

// Initialize starting values.
score::score() : userScore(0), completedWords(0), correctLetters(0) {}

// Calculates score using the number of correct and incorrect words.
int score::calculateScore(int lettersCorrect, int wordsCompleted) {
    correctLetters = lettersCorrect;
    completedWords = wordsCompleted;

    //Each correct letter is 1 point
    //Each completed word adds 5 bonuns points
    userScore = correctLetters +(completedWords * POINTS_PER_COMPLETED_WORD);

    return userScore;
}

// Returns the player's current score.
int score::getScore() {
    return userScore;
}

// Returns how many full words are correct.
int score::getCompletedWords() {
    return completedtWords;
}

// Returns how many attempted words are incorrect.
int score::getCorrectLetters() {
    return correctLetters;
}
