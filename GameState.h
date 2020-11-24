
//Screen size
//int MaxScreenX = 0; //COLS
int MaxScreenY = 0; //LINES

//The max we can go on the screen
int border = 0; // MaxScreenX for frupal Map

//Map coordinates (within array)
int MaxX= 0;
int MaxY = 0;
int MinX = 0;
int MinY = 0;

class GameState
{
	public:
		GameState(string mapSrcFile);
		
		//Do we Need this??
		/*
		int getHeroRow();
		int getHeroCol();
		bool moveHeroTo( int row, int col);
		*/
		void travel(char direction, WINDOW * win);

		void cursorTravel(char direction);
		bool ExpandMap();

		void HeroVision();
	
	private:
		Hero theHero;
		Map map;
		int CursorX;
		int CursorY;
		int HeroX;
		int HeroY;
};
