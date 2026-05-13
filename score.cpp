#include "score.h"

// Initialize starting values.
score::score() : userScore(0), completedWords(0), correctLetters(0) {}

// Calculates score using correct letters plus a bonus for completed words.
int score::calculateScore(int lettersCorrect, int wordsCompleted) {
    correctLetters = lettersCorrect;
    completedWords = wordsCompleted;

    // Each correct letter is 1 point.
    // Each completed word adds 5 bonus points.
    userScore = correctLetters + (completedWords * POINTS_PER_COMPLETED_WORD);

    return userScore;
}

// Returns the player's current score.
int score::getScore() {
    return userScore;
}

// Returns how many words are fully completed correctly.
int score::getCompletedWords() {
    return completedWords;
}

// Returns how many letters are currently correct.
int score::getCorrectLetters() {
    return correctLetters;
}
