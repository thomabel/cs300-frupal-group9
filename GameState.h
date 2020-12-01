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

//Map coordinates (within array)

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
