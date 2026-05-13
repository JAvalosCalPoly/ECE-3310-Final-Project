#include <iostream>
#include "score.h"

// Initialize starting values
score::score() : userScore(0), correctWords(0), incorrectWords(0) {}

// Increments number of correct word guesses
void score::addCorrectWord() {
	correctWords++;
}

// Increments number of incorrect word guesses
void score::addIncorrectWord() {
	incorrectWords++;
}

// Calculates and returns final score
int score::calculateScore(int wordsCorrect, int wordsIncorrect) {
	userScore = (correctWords * POINTS_PER_WORD) - (incorrectWords * POINTS_PER_PENALTY);
	return userScore;
}
