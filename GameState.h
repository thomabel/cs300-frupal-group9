
#include"Map.h"

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
		
		GameState(string MapsrcFile);
		
		//Do we Need this??
		/*
		int getHeroRow();
		int getHeroCol();
		bool moveHeroTo( int row, int col);
		*/
		void travel(char & direction, WINDOW * win, WINDOW * menu);


		void cursorTravel(char direction);

		bool HeroTravel(char & direction, WINDOW * menu);

		bool ExpandMap();

		bool ccupantCheck(char & direction, WINDOW * win);

		void HeroVision();
		void HeroVision(int tempHeroY, int tempHeroX);
	
	private:
		Hero theHero;
		Map map;
		UserInterface UI;
		int cursorX;
		int cursorY;
		int heroX;
		int heroY;
};
