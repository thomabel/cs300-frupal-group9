#include <sstream>
#include <string>

#include "TileOccupant.h"

using std::stringstream;
using std::string;
using std::getline;
using std::stoi;
using std::vector;

TileOccupant *newOccupant(const string &type, const string &csv);

TileOccupant *csvToFood(const string &csv);

TileOccupant *csvToBinoculars(const string &csv);

TileOccupant *csvToShip(const string &csv);

TileOccupant *csvToTreasure(const string &csv);

TileOccupant *csvToClue(const string &csv);

TileOccupant *csvToDiamond(const string &csv);

TileOccupant *csvToObstacle(const string &csv);

TileOccupant *csvToTool(const string &csv);
