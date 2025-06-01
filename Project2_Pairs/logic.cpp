//DT Nesimi

#include <vector>
#include <random>
#include "logic.h"

void logic::setup() {
	int pairs[24];
	std::vector<char> cards;

	for (char c = 'A'; c < 'A' + 12; c++) {
		cards.push_back(c);
		cards.push_back(c);
	}

	srand(time(NULL));
	std::random_shuffle(cards.begin(), cards.end());

	int count = 0;
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			board[i][j] = cards[count++];
		}
	}

}