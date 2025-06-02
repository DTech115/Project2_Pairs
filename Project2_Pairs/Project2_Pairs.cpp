//DT Nesimi
#include <allegro5/allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>	
#include <allegro5\allegro_native_dialog.h> 
#include "logic.h"
#include <iostream>

int posX = 0, posY = 0;

void drawBoard();
void get_mouse_input(int x, int y, logic& game_logic, int &click);
void drawShape(int x, int y, char shape);
void flipCard(int x, int y, int boardx, int boardy, logic& game_logic, int &click);

int main()
{

	logic game_logic;
	ALLEGRO_DISPLAY* Screen = NULL;
	int width = 640, height = 480;

	static int click = 0;


	if (!al_init())
	{
		al_show_native_message_box(NULL, "Error!", "Allegro has failed to initialize.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return (-1);
	}

	Screen = al_create_display(width, height);
	if (Screen == NULL)
	{
		al_show_native_message_box(Screen, "Error!", "Failed to create the display.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return (-1);
	}

	if (!al_install_mouse()) {
		al_show_native_message_box(Screen, "Error!", "Failed to initialize the mouse!\n.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return (-1);
	}
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT* font = al_load_font("DFPPOPCorn-W12.ttf", 14, 0);

	ALLEGRO_FONT* biggerFont = al_load_font("DFPPOPCorn-W12.ttf", 36, 0);

	bool draw = false, done = false;

	ALLEGRO_EVENT_QUEUE* event_queue = NULL;

	event_queue = al_create_event_queue();


	al_register_event_source(event_queue, al_get_display_event_source(Screen));
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_register_event_source(event_queue, al_get_mouse_event_source());

	game_logic.setup();
	drawBoard();
	al_flip_display();
	
	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}

		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1)
			{
				posX = ev.mouse.x;
				posY = ev.mouse.y;

				draw = true;
			}
		}
		drawBoard();

		//score drawing:
		int matches = game_logic.getMatched();
		int totalPairs = game_logic.getPairs();
		al_draw_filled_rectangle(512, 384, width, height, al_map_rgb(0, 0, 0));
		al_draw_textf(font, al_map_rgb(255, 255, 255), 520, 410, 0, "Pairs Left: %i", totalPairs);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 520, 440, 0, "Matches: %i", matches);

		//close game if you won!!!
		if (matches == 12) {
			al_draw_textf(biggerFont, al_map_rgb(255, 0, 0), width / 2, height / 2, ALLEGRO_ALIGN_CENTER, "CONGRATS! You win!");
			al_draw_textf(biggerFont, al_map_rgb(255, 0, 0), width / 2, height / 2 + 40, ALLEGRO_ALIGN_CENTER, "Press SPACEBAR to play again.");
			done = true;
		}

		if (draw) {
			get_mouse_input(posX, posY, game_logic, click);

			draw = false;
		}
		al_flip_display();
	}


	
	al_rest(3.0);
	al_destroy_font(font);
	al_destroy_font(biggerFont);
	al_destroy_event_queue(event_queue);
	al_destroy_display(Screen);

	return 0;
}

void drawBoard() {
	al_draw_line(0, 96, 640, 96, al_map_rgb(255, 255, 255), 2);
	al_draw_line(0, 192, 640, 192, al_map_rgb(255, 255, 255), 2);
	al_draw_line(0, 288, 640, 288, al_map_rgb(255, 255, 255), 2);
	al_draw_line(0, 384, 640, 384, al_map_rgb(255, 255, 255), 2);

	al_draw_line(128, 0, 128, 480, al_map_rgb(255, 255, 255), 2);
	al_draw_line(256, 0, 256, 480, al_map_rgb(255, 255, 255), 2);
	al_draw_line(384, 0, 384, 480, al_map_rgb(255, 255, 255), 2);
	al_draw_line(512, 0, 512, 480, al_map_rgb(255, 255, 255), 2);
}

void drawShape(int x, int y, char shape) {
	ALLEGRO_FONT* font = al_load_font("DFPPOPCorn-W12.ttf", 50, 0);

	int size = 40;
	if (shape == 'A') {
		al_draw_filled_circle(x, y, size, al_map_rgb(255, 0, 0));
	}
	else if (shape == 'B') {
		al_draw_filled_rectangle(x - size, y - size, x + size, y + size, al_map_rgb(0, 215, 100));
	}
	else if (shape == 'C') {
		al_draw_filled_triangle(x, y - size, x - size, y + size, x + size, y + size, al_map_rgb(255, 255, 0));
	}
	else if (shape == 'D') {
		al_draw_text(font, al_map_rgb(100, 255, 0), x, y, ALLEGRO_ALIGN_CENTER, "?");
	}
	else if (shape == 'E') {
		al_draw_filled_rectangle(x - 10, y - size, x + 10, y + size, al_map_rgb(255, 100, 100));
		al_draw_filled_rectangle(x - size, y - 10, x + size, y + 10, al_map_rgb(255, 100, 100));
	}
	else if (shape == 'F') {
		al_draw_filled_triangle(x, y - size, x - 30, y + size, x + 30, y + size, al_map_rgb(255, 215, 0));
		al_draw_filled_triangle(x - size, y - 10, x + size, y - 10, x, y + 20, al_map_rgb(255, 215, 0));
		al_draw_filled_triangle(x, y + 20, x - 30, y + size, x + 30, y + size, al_map_rgb(0, 0, 0));
	}
	else if (shape == 'G') {
		al_draw_filled_triangle(x - size, y - size, x + size, y - size, x, y, al_map_rgb(200, 255, 200));
		al_draw_filled_triangle(x - size, y + size, x + size, y + size, x, y, al_map_rgb(255, 200, 0));
	}
	else if (shape == 'H') {
		al_draw_filled_circle(x, y, size, al_map_rgb(255, 215, 0));
		al_draw_filled_triangle(x, y, x + size, y - size / 2, x + size, y + size / 2, al_map_rgb(0, 0, 0));
	}
	else if (shape == 'I') {
		al_draw_filled_circle(x, y, size, al_map_rgb(255, 100, 0));
		al_draw_filled_circle(x, y, size / 2, al_map_rgb(0, 0, 0));
	}
	else if (shape == 'J') {
		for (int i = 0; i < 4; i++) {
			al_draw_circle(x, y, size - i * 10, al_map_rgb(255, 255, 255), 2);
		}
	}
	else if (shape == 'K') {
		al_draw_filled_ellipse(x, y, size + 20, size, al_map_rgb(255, 150, 0));
	}
	else if (shape == 'L') {
		al_draw_filled_triangle(x, y - size, x - 20, y, x +20, y, al_map_rgb(255, 215, 0));
		al_draw_filled_triangle(x - 20, y, x - size, y + size, x, y + size, al_map_rgb(255, 215, 0));
		al_draw_filled_triangle(x + 20, y, x, y + size, x + size, y + size, al_map_rgb(255, 215, 0));
	}
	al_destroy_font(font);
}

void get_mouse_input(int x, int y, logic& game_logic, int &click) {
	//row 1
	if ((x < 128 && y < 96)) {
		flipCard(64, 48, 0, 0, game_logic, click);
	}
	else if ((x > 128 && x < 256 && y < 96)) {
		flipCard(192, 48, 0, 1, game_logic, click);
	}
	else if ((x > 256 && x < 384 && y < 96)) {
		flipCard(320, 48, 0, 2, game_logic, click);
	}
	else if ((x > 384 && x < 512 && y < 96)) {
		flipCard(448, 48, 0, 3, game_logic, click);
	}
	else if ((x > 512 && y < 96)) {
		flipCard(576, 48, 0, 4, game_logic, click);
	}
	//row 2
	else if ((x < 128 && y > 96 && y < 192)) {
		flipCard(64, 144, 1, 0, game_logic, click);
	}
	else if ((x > 128 && x < 256 && y > 96 && y < 192)) {
		flipCard(192, 144, 1, 1, game_logic, click);
	}
	else if ((x > 256 && x < 384 && y > 96 && y < 192)) {
		flipCard(320, 144, 1, 2, game_logic, click);
	}
	else if ((x > 384 && x < 512 && y > 96 && y < 192)) {
		flipCard(448, 144, 1, 3, game_logic, click);
	}
	else if ((x > 512 && y > 96 && y < 192)) {
		flipCard(576, 144, 1, 4, game_logic, click);
	}
	//row 3
	else if ((x < 128 && y > 192 && y < 288)) {
		flipCard(64, 240, 2, 0, game_logic, click);
	}
	else if ((x > 128 && x < 256 && y > 192 && y < 288)) {
		flipCard(192, 240, 2, 1, game_logic, click);
	}
	else if ((x > 256 && x < 384 && y > 192 && y < 288)) {
		flipCard(320, 240, 2, 2, game_logic, click);
	}
	else if ((x > 384 && x < 512 && y > 192 && y < 288)) {
		flipCard(448, 240, 2, 3, game_logic, click);
	}
	else if ((x > 512 && y > 192 && y < 288)) {
		flipCard(576, 240, 2, 4, game_logic, click);
	}
	//row 4
	else if ((x < 128 && y > 288 && y < 384)) {
		flipCard(64, 336, 3, 0, game_logic, click);
	}
	else if ((x > 128 && x < 256 && y > 288 && y < 384)) {
		flipCard(192, 336, 3, 1, game_logic, click);
	}
	else if ((x > 256 && x < 384 && y > 288 && y < 384)) {
		flipCard(320, 336, 3, 2, game_logic, click);
	}
	else if ((x > 384 && x < 512 && y > 288 && y < 384)) {
		flipCard(448, 336, 3, 3, game_logic, click);
	}
	else if ((x > 512 && y > 288 && y < 384)) {
		flipCard(576, 336, 3, 4, game_logic, click);
	}
	//row 5
	else if ((x < 128 && y > 384)) {
		flipCard(64, 432, 4, 0, game_logic, click);
	}
	else if ((x > 128 && x < 256 && y > 384)) {
		flipCard(192, 432, 4, 1, game_logic, click);
	}
	else if ((x > 256 && x < 384 && y > 384)) {
		flipCard(320, 432, 4, 2, game_logic, click);
	}
	else if ((x > 384 && x < 512 && y > 384)) {
		flipCard(448, 432, 4, 3, game_logic, click);
	}
	
}

void flipCard(int x, int y, int boardx, int boardy, logic& game_logic, int& click) {
	if (game_logic.get_playing_shape(boardx, boardy) == 'n') {

		if (click == 0) {
			char shape = game_logic.get_shape(boardx, boardy); //get corresponding letter from backend 2Darray

			game_logic.set_playing_shape(boardx, boardy, shape);

			drawShape(x, y, shape);

			game_logic.setFirstCard(x, y, boardx, boardy); 		//store the first card's coordinates for later

			click = 1;
		}
		else if (click == 1) {


			//check if the section is already clicked!
			char shape = game_logic.get_shape(boardx, boardy); //get corresponding letter from backend 2Darray

			drawShape(x, y, shape);
			click = 0;

			al_flip_display();
			al_rest(0.4);  //pause!

			//check if they match...
			int firstX = game_logic.getFirstCardX();
			int firstY = game_logic.getFirstCardY();
			int cardBoardX = game_logic.getFirstBoardX();
			int cardBoardY = game_logic.getFirstBoardY();

			//if match, cover square with STATIC! else, remove with black
			if (shape == game_logic.get_shape(cardBoardX, cardBoardY)) {
				for (int px = firstX - 64; px < firstX + 64; px++) {
					for (int py = firstY - 48; py < firstY + 48; py++) {
						ALLEGRO_COLOR color = al_map_rgb(rand() % 255, rand() % 255, rand() % 255);
						al_draw_filled_rectangle(px, py, px + 1, py + 1, color);
					}
				}
				for (int px = x - 64; px < x + 64; px++) {
					for (int py = y - 48; py < y + 48; py++) {
						ALLEGRO_COLOR color = al_map_rgb(rand() % 255, rand() % 255, rand() % 255);
						al_draw_filled_rectangle(px, py, px + 1, py + 1, color);
					}
				}

				game_logic.set_playing_shape(boardx, boardy, shape);

				//also increase score:
				game_logic.increasePairs();
			}
			else { //flips back over to black
				al_draw_filled_rectangle(firstX - 64, firstY - 48, firstX + 64, firstY + 48, al_map_rgb(0, 0, 0));
				al_draw_filled_rectangle(x - 64, y - 48, x + 64, y + 48, al_map_rgb(0, 0, 0));

				//turn failed pair back into n's on the played board
				game_logic.set_playing_shape(cardBoardX, cardBoardY, 'n');
				game_logic.set_playing_shape(boardx, boardy, 'n');
			}
		}
	}
}