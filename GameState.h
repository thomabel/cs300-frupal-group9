/*
 GameState Class
 Author: Mohamed-Amin Cheaito
 November 2020
*/
#ifndef GameState_CLASS
#define GameState_CLASS

#include"Map.h"
#include"Hero.h"
#include"UI.h"
//Screen size
int MaxScreenX = 0; //COLS


int MaxScreenY = 0; //LINES

//The max we can go on the screen
int MenuBorder = 0; // MaxScreenX for frupal Map

//Map coordinates (within array)
int MaxX= 0;
int MaxY = 0;
int MinX = 0;
int MinY = 0;

class GameState
{
	public:
		
		GameState();
		~GameState();
		
		void travel(int & direction, WINDOW * win);

		void cursorTravel(int direction);

		bool HeroTravel(int & direction);

		bool ExpandMap();

		bool occupantCheck(int & direction);

		void HeroVision();
		void HeroVision(int tempHeroY, int tempHeroX);
		void RunGame(WINDOW * win);
	
	private:
		Hero theHero;
		Map map;
		UserInterface UI;
		int cursorX;
		int cursorY;
		int heroX;
		int heroY;
};
#endif
