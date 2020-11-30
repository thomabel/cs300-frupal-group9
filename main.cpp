#include"GameState.h"
int main()
{
	initscr();
	noecho();
	keypad(stdscr, true);
	start_color();

	init_pair(1, COLOR_WHITE, COLOR_CYAN);
	init_pair(2, COLOR_BLACK, COLOR_GREEN);
	init_pair(3, COLOR_BLACK, COLOR_BLACK);
	init_pair(4, COLOR_WHITE, COLOR_BLUE);
	init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
        init_pair(6, COLOR_YELLOW, COLOR_RED);
        init_pair(7, COLOR_BLACK, COLOR_WHITE);

	GameState Game;

	Game.RunGame(stdscr);

	endwin();

	return 0;
}
