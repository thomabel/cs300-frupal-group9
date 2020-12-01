/*
 Map Class
 Author: Mohamed-Amin Cheaito
 November 2020
*/

using namespace std;

#ifndef Map_CLASS
#define Map_CLASS

#include<ncurses.h>
#include<vector>
#include<cstring>
#include <string>
#include <cmath>
#include<fstream>
#include<iostream>

#include "TileType.h"
#include "TileOccupant.h"

class TileOccupant;
class TileType;

//Screen size
int MaxScreenX = 0; //COLS

int MaxScreenY = 0; //LINES

//The max we can go on the screen
int MenuBorder = 0; // MaxScreenX for frupal Map

const int MAPSIZE = 128;
int MaxX = 0;
int MaxY = 0;
int MinX = 0;
int MinY = 0;

struct Tile
{
	Tile();
	~Tile();

	bool revealed;
	TileType* type;
	TileOccupant* occupant;
};

class Map
{
	public:
		Map() = delete;
		Map(string srcFile, int & heroX, int & heroY);
		TileType * tileTypeAt(int row, int col);
		TileOccupant * occupantAt(int row, int col);
        void setOccupantAt(int row, int col, TileOccupant* newOccupant);

		void tile_revealed(int row, int col);

		bool isTileDiscovered(int row, int col);

		void displayMap(WINDOW * win);

		bool loadFile(string src, int & heroX, int & heroY);
		bool loadOccupants(string src);

		//Write to a file
		bool saveFile(string dest, int heroX, int heroY);
		bool saveOccupants(string dest);

	private:
		//vector<vector<Tile>> tileArray;
		Tile tileArray[MAPSIZE][MAPSIZE];
};
#endif
