//DT Nesimi

class logic {
public:
	logic();
	void setup();
	//game_object get_shape();
	bool set_shape(int x, int y);

private:
	char board[5][5];
	char playBoard[5][5];
};