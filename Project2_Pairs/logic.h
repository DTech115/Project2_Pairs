//DT Nesimi

class logic {
public:
	logic();
	void setup();

	bool compare(int x, int y);
	char get_shape(int x, int y);
	void set_shape(int x, int y, char c);

	void setFirstCard(int x, int y, int boardx, int boardy);
	int getFirstCardX();
	int getFirstCardY();
	int getFirstBoardX();
	int getFirstBoardY();

	void increasePairs();
	int getPairs();
	int getMatched();
	//void reset();

private:
	char board[5][5];
	char playBoard[5][5];

	int totalPairs = 12;
	int matchedPairs = 0;

	int firstCardX;
	int firstCardY;
	int firstCardBoardX;
	int firstCardBoardY;
	
};