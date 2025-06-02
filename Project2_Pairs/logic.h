//DT Nesimi

class logic {
public:
	logic();
	void setup();
	bool compare(int x, int y);
	char get_shape(int x, int y);
	void set_shape(int x, int y, char c);
	void setFirstCard(int x, int y);
	int getFirstCardX();
	int getFirstCardY();
	//void reset();

private:
	char board[5][5];
	char playBoard[5][5];
	int firstCardX;
	int firstCardY;
};