#ifndef CsvToOccupant_CLASS
#define CsvToOccupant_CLASS

#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

#include "TileOccupant.h"

using std::stringstream;
using std::string;
using std::getline;
using std::stoi;
using std::vector;
using std::ifstream;

TileOccupant *newOccupant(const string &type, const string &csv);

TileOccupant *csvToFood(const string &csv);

TileOccupant *csvToBinoculars(const string &csv);

TileOccupant *csvToShip(const string &csv);

TileOccupant *csvToTreasure(const string &csv);

TileOccupant *csvToClue(const string &csv);

TileOccupant *csvToDiamond(const string &csv);

TileOccupant *csvToObstacle(const string &csv);

TileOccupant *csvToTool(const string &csv);

vector<string> inputFile(string src);

vector<string> cleanFile(vector<string> src);

#endif
