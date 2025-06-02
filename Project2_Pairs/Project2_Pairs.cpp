//DT Nesimi
#include <allegro5/allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>	
#include <allegro5\allegro_native_dialog.h> 
#include "logic.h"
#include <iostream>

int posX = 0, posY = 0;

void draw_board();
void get_mouse_input(int x, int y, logic& game_logic, int &click);
void drawShape(int x, int y);
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

	bool draw = false, done = false;

	ALLEGRO_EVENT_QUEUE* event_queue = NULL;

	event_queue = al_create_event_queue();


	al_register_event_source(event_queue, al_get_display_event_source(Screen));
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_register_event_source(event_queue, al_get_mouse_event_source());

	game_logic.setup();
	draw_board();
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
		draw_board();


		if (draw) {
			

			get_mouse_input(posX, posY, game_logic, click);


			draw = false;
		}
		al_flip_display();
	}


	
	//al_rest(5.0);
	al_destroy_event_queue(event_queue);
	al_destroy_display(Screen);

	return 0;
}

void draw_board() {
	al_draw_line(0, 96, 640, 96, al_map_rgb(255, 255, 255), 2);
	al_draw_line(0, 192, 640, 192, al_map_rgb(255, 255, 255), 2);
	al_draw_line(0, 288, 640, 288, al_map_rgb(255, 255, 255), 2);
	al_draw_line(0, 384, 640, 384, al_map_rgb(255, 255, 255), 2);

	al_draw_line(128, 0, 128, 480, al_map_rgb(255, 255, 255), 2);
	al_draw_line(256, 0, 256, 480, al_map_rgb(255, 255, 255), 2);
	al_draw_line(384, 0, 384, 480, al_map_rgb(255, 255, 255), 2);
	al_draw_line(512, 0, 512, 480, al_map_rgb(255, 255, 255), 2);
}

void drawShape(int x, int y) {
	al_draw_filled_circle(x, y, 20, al_map_rgb(255, 0, 0));
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
	if ((x < 128 && y > 96 && y < 192)) {
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
	if ((x < 128 && y > 192 && y < 288)) {
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
	if ((x < 128 && y > 288 && y < 384)) {
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
	if ((x < 128 && y > 384)) {
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
	else if ((x > 512 && y > 384)) {
		flipCard(576, 432, 4, 4, game_logic, click);
	}
}

void flipCard(int x, int y, int boardx, int boardy, logic& game_logic, int &click) {
	if (click == 0) {
		drawShape(x, y);
		game_logic.setFirstCard(x, y);
		click = 1;
	}
	else if (click == 1) {
		drawShape(x, y);
		click = 0;
		al_flip_display();
		al_rest(1.0);

	//check if they match...
		int firstX = game_logic.getFirstCardX();
		int firstY = game_logic.getFirstCardY();
		al_draw_filled_rectangle(firstX - 64, firstY - 48, firstX + 64, firstY + 48, al_map_rgb(0, 0, 0));
		al_draw_filled_rectangle(x - 64, y - 48, x + 64, y + 48, al_map_rgb(0, 0, 0));
	}
}