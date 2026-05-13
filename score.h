// score.h - header file for score.cpp
#include <iostream>
#include <string>
#include <vector>

#ifndef SCORE_H
#define SCORE_H

class score {
private:
	// Points constants
	const int POINTS_PER_WORD = 10;
	const int POINTS_PER_PENALTY = 3;

	// Variable declarations
	int userScore;
	int correctWords;
	int incorrectWords;

public:
	score();

	// Updates score based on correctness
	void addCorrectWord();
	void addIncorrectWord();

	// Calculates and returns final score
	int calculateScore(int wordsCorrect, int wordsIncorrect);

};

#endif

