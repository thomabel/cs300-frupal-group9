#include<ncurses.h>
#include<vector>
#include<cstring>
#include <string>
#include <cmath>
        
#include<fstream>
#include<iostream>
using namespace std;
/*
#include "TileType.h"
#include"TileOccupant.h"
*/
int MAPSIZE = 128;

struct Tile
{
	Tile();

	bool revealed;
	TileType* type;
	TileOccupant* occupant;
};

class Map
{
	public:
		Map() = delete;
		Map(string srcFile);
		TileType * tileTypeAt(int row, int col);
		TileOccupant * occupantAt(int row, int col);
        void setOccupantAt(int row, int col, TileOccupant* newOccupant);

		void tile_revealed(int row, int col);

		bool isTileDiscovered(int row, int col);

		void displayMap(WINDOW * win);


		bool loadFile(string src);
		bool loadOccupants(string src);

		//Write to a file
		bool saveFile(string dest);
		bool saveOccupants(string dest);

	private:
		//vector<vector<Tile>> tileArray;
		Tile tileArray[128][128];
};
