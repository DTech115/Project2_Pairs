//DT Nesimi

class logic {
public:
	logic();
	void setup();
	bool already_played();
	
	bool set_shape(int boxNum);

private:
	char board[5][5];
	char playBoard[5][5];
};