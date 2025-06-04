//DT Nesimi

#include <vector>
#include <random>
#include "logic.h"
#include <iostream>

// constructor fills the two boards with 'n's & sets scores to default
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

// setup generates 12 letters A-L to a vector, adding each one twice & shuffles them randomly
// it then adds those randomized letters to the main board, making sure the bottom right is '*' as it's not
// used in gameplay. 
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
				//std::cout << board[i][j] << " ";
			}
			else {
				board[i][j] = cards[count++];
				//std::cout << board[i][j] << " ";
			}
		}
		//std::cout << "\n";
	}
	//std::cout << "\n";
}

// returns the character from the main board which links to a shape in main
char logic::get_shape(int x, int y) {
	return board[x][y];
}
// returns the character from the playing board, which can either be a matched letter [ignored on click]
// or an 'n' if its free.
char logic::get_playing_shape(int x, int y) {
	return playBoard[x][y];
}
//sets the character in the playing board to the matched shape-letter
void logic::set_playing_shape(int x, int y, char c) {
	playBoard[x][y] = c;
}

//simply sets the first card's coord info for later comparisons
void logic::setFirstCard(int x, int y, int boardx, int boardy) {
	firstCardX = x;
	firstCardY = y;
	firstCardBoardX = boardx;
	firstCardBoardY = boardy;
	
}
//returns the relevant info
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

//increases score
void logic::increasePairs() {
	matchedPairs += 1;
	totalPairs -= 1;
}

//return pairs & matches
int logic::getMatched() {
	return matchedPairs;
}
int logic::getPairs() {
	return totalPairs;
}