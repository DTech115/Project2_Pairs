//DT Nesimi

// two logical back-end 2Darrays.
// ONE tracks all the matches via pairs of LETTERS.
// the other is full of "n"s & tracks the player's moves.
// when they make a guess, it compares the guess to the filled board's letters.
// if it's right, the letter is added to the corresponding coordinate on the player board over the "n"
// if the player clicks on a square that links to the playerboard 
// with a LETTER & not an "n", nothing happens

class logic {
public:
	logic();
	void setup();
	
	//returns the letter that links to a shape in main
	char get_shape(int x, int y);
	
	//returns the letter in the playing board, whether it's an empty 'n' or a matched letter
	char get_playing_shape(int x, int y);
	void set_playing_shape(int x, int y, char c); //	sets the 'n' in the playing board to the matched letter

	//these all grab the first card's coords for when we check with the second card
	void setFirstCard(int x, int y, int boardx, int boardy);
	int getFirstCardX();
	int getFirstCardY();
	int getFirstBoardX();
	int getFirstBoardY();

	void increasePairs();	//increases score
	int getPairs(); //gets the pairs left
	int getMatched(); //gets the matches made

private:
	char board[5][5];	//randomized letter-board
	char playBoard[5][5];	//initially 'n' playing board

	int totalPairs;
	int matchedPairs;

	int firstCardX;
	int firstCardY;
	int firstCardBoardX;
	int firstCardBoardY;
	
};