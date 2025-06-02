//DT Nesimi

//two logical back-end 2Darrays.
//ONE tracks all the matches via pairs of LETTERS.
//the other is full of "n"'s & tracks the player's moves.
//when they make a guess, it compares the guess to the filled board's letters.
//if it's right, the letter is added to the corresponding coordinate on the player board over the "n"
//if the player clicks on a square that links to the playerboard 
// with a LETTER & not an "n", nothing happens

class logic {
public:
	logic();
	void setup();
	
	char get_shape(int x, int y);

	char get_playing_shape(int x, int y);
	void set_playing_shape(int x, int y, char c);

	void setFirstCard(int x, int y, int boardx, int boardy);
	int getFirstCardX();
	int getFirstCardY();
	int getFirstBoardX();
	int getFirstBoardY();

	void increasePairs();
	int getPairs();
	int getMatched();

	void reset();

private:
	char board[5][5];
	char playBoard[5][5];

	int totalPairs;
	int matchedPairs;

	int firstCardX;
	int firstCardY;
	int firstCardBoardX;
	int firstCardBoardY;
	
};