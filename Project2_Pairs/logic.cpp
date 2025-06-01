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


}

void logic::setup() {
	std::vector<char> cards;

	for (char c = 'A'; c < 'A' + 12; c++) {
		cards.push_back(c);
		cards.push_back(c);
		std::cout << c << " ";
	}
	std::cout << "\n";

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

bool logic::compare(int x, int y) {
	if (playBoard[x][y] == board[x][y]) {
		return true;
	}
	else {
		return false;
	}
}

char logic::get_shape(int x, int y) {
	return board[x][y];
}

void logic::set_shape(int x, int y, char c) {
	playBoard[x][y] == c;
}

//void reset() {
//
//}