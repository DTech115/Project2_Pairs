//DT Nesimi

#include <vector>
#include <random>
#include "logic.h"
#include <iostream>

logic::logic() {

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			board[i][j] = 'n';
			playBoard[i][j] = 'n';
		}
	}
	matchedPairs = 0;
	totalPairs = 12;

}

void logic::setup() {
	std::vector<char> cards;

	for (char c = 'A'; c < 'A' + 12; c++) {
		cards.push_back(c);
		cards.push_back(c);
	}

	srand(time(NULL));
	std::random_shuffle(cards.begin(), cards.end());

	int count = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (i == 4 && j == 4) {
				board[i][j] = '*'; 
				std::cout << board[i][j] << " ";
			}
			else {
				board[i][j] = cards[count++];
				std::cout << board[i][j] << " ";
			}
		}
		std::cout << "\n";
	}

}

char logic::get_shape(int x, int y) {
	return board[x][y];
}
char logic::get_playing_shape(int x, int y) {
	return playBoard[x][y];
}
void logic::set_playing_shape(int x, int y, char c) {
	playBoard[x][y] = c;
}

void logic::setFirstCard(int x, int y, int boardx, int boardy) {
	firstCardX = x;
	firstCardY = y;
	firstCardBoardX = boardx;
	firstCardBoardY = boardy;
	
}

int logic::getFirstCardX() {
	return firstCardX;
}
int logic::getFirstCardY() {
	return firstCardY;
}
int logic::getFirstBoardX() {
	return firstCardBoardX;
}
int logic::getFirstBoardY() {
	return firstCardBoardY;

}

void logic::increasePairs() {
	matchedPairs += 1;
	totalPairs -= 1;
}

int logic::getMatched() {
	return matchedPairs;
}

int logic::getPairs() {
	return totalPairs;
}


void logic::reset() {
	setup();
}