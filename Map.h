/*
 Map Class
 Author: Mohamed-Amin Cheaito
 November 2020
*/
/*
#include<ncurses.h>
#include<vector>
#include<cstring>
#include <string>
#include <cmath>
        
#include<fstream>
#include<iostream>
using namespace std;
*/

#ifndef Map_CLASS
#define Map_CLASS

#include "TileType.h"
#include"TileOccupant.h"


const int MAPSIZE = 128;

struct Tile
{
	Tile();
	~Tile();

	bool revealed;
	TileType* type;
	TileOccupant* occupant;
};

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
