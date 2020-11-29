/*
FileName:	TileOccupant.cpp
Author:		Drew McKinney
Group:		9
Description:	
		TileOccupant and derived classes implementation 
*/
#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include "TileOccupant.h"

using namespace std;


/*
TileOccupant abstract base class
*/
TileOccupant::TileOccupant()
{
}

/*
/////////////////////////////////////////////////////////////////
Treasure class derived from TileOccupant
/////////////////////////////////////////////////////////////////
*/

Treasure::Treasure() : worth_(0)
{
}

Treasure::Treasure(int worth) : worth_(worth)
{
}

bool Treasure::permanent()
{
	return false;
}

/*
Function:	color
Description:	return appropriate color for derived class,
		black? Not sure
Arguments:	none
Return:		int - color for this class, treasure
*/
int Treasure::color()
{
	return COLOR_BLACK;
}

/*
Function:	marker
Description:	return appropriate marker for derived class
Arguments:	none
Return:		char - marker for this class, treasure
*/
char Treasure::marker()
{
	return '$';
}

/*
Function:	getDetails
Description:	returns data in the form of strings to pass to ui
Arguments:
Return:		vector<string> - object data to pass to ui
*/
vector<string> Treasure::getDetails()
{
	vector<string> data;
	data.push_back(" ");
	data.push_back(to_string(worth_));
	data.push_back("Treasure");
	data.push_back("Worth");
	
	return data;
}


/*
Function:	promptMsg
Description:	returns message specific to this class, treasure
Arguments:	none
Return:		string - message to display to player
*/
string Treasure::promptMsg(Hero& theHero)
{
	string msg = "A treasure chest has been found " 
			+ "containing: " + to_string(worth_) 
			+ " Whiffles!";
	return msg;
}

/*
Function:	interact
Description:	occupant interacts with player according to 
		promptResponse
Arguments:	char - player response to prompt 
		Hero& - player 
Return:		none
*/
void Treasure::interact(char promptResponse, Hero& theHero)
{
	theHero.addWhiffles(worth_);
}


/*
/////////////////////////////////////////////////////////////////
 Ship class derived from TileOccupant
/////////////////////////////////////////////////////////////////
*/



Ship::Ship() : whiffleCost_(0), bought_(false)
{
}

Ship::Ship(int whiffleCost) : whiffleCost_(whiffleCost), bought(false)
{
}

/*
Function:	permanent
Description:	returns if occupant is permanent or not?
Arguments:	none
Return:		none
*/
bool Ship::permanent()
{
	return false;
}

/*
Function:	color
Description:	return appropriate color for derived class
Arguments:	none
Return:		int - color for this class, ship
*/
int Ship::color()
{
	return COLOR_BLACK;
}

/*
Function:	marker
Description:	return appropriate marker for derived class
Arguments:	none
Return:		char - marker for this class, ship
*/
char Ship::marker()
{
	return 'S';
}

/*
Function:	getDetails
Description:	returns data in the form of strings to pass to ui
Arguments:
Return:		vector<string> - object data to pass to ui
*/
vector<string> Ship::getDetails()
{
	vector<string> data;
	data.push_back(" ");
	data.push_back(to_string(whiffleCost_));
	if(bought_)
		data.push_back("True");
	else
		data.push_back("False");
	data.push_back("Ship");
	data.push_back("Cost");
	data.push_back("Bought");
	
	return data;
}

/*
Function:	promptMsg
Description:	returns message specific to this class, treasure
Arguments:	none
Return:		string - message to display to player
*/
string Ship::promptMsg(Hero& theHero)
{
	string msg;

	if(bought_)
	{
		msg = "Welcome back! Sail in ship? (Y/N):";
	}	
	
	msg = "A ship has been found! ";
	if(theHero.whiffles() < whiffleCost_)
	{
		msg = msg + "But you don't have enough Whiffles!"
			+ "Sorry!";
	}
	else
	{
		msg = msg + "Purchase ship for " 
			+ to_string(whiffleCost_)
			+ " Whiffles?(Y/N):";
	}
	return msg;
}

/*
Function:	interact
Description:	occupant interacts with player according to 
		promptResponse
Arguments:	char - player response to prompt 
		Hero& - player 
Return:		none
*/
void Ship::interact(char promptResponse, Hero& theHero)
{
	if(bought_)
	{
		theHero.giveShip();
		return;
	}
	else if(theHero.whiffles() < whiffleCost_)
		return;

	if(promptResponse == 'y' || promptResponse == 'Y')
	{
		theHero.addWhiffles(-whiffleCost_);
		theHero.giveShip();
	}
}

/*
/////////////////////////////////////////////////////////////////
 Tool class derived from TileOccupant
/////////////////////////////////////////////////////////////////
*/

Tool::Tool() : name_(0), whiffleCost_(0), rating_(0), forObstacles(0)
{
}

Tool::Tool(string name, int whiffleCost, int rating, vector<string> usableOn) : name_(name), whiffleCost_(whiffleCost), rating_(rating), forObstacles(usableOn)
{
}

/*
Function:	usableOn
Description:	determines if tool is usable on given obstacle
Arguments:	Obstacle& - obstacle to check against
Return:		bool - true if usable on obstacle, 
			false if not
*/
bool Tool::usableOn(const Obstacle& onObstacle)
{
	vector<string>::iterator i;
	for(i=forObstacles.begin(); i<forObstacles.end(); i++)
	{
		if(*i == onObstacle.name())
			return true;
	}
	return false;
}

/*
Function:	rating
Description:	returns rating of tool
Arguments:	none
Return:		int - rating of tool
*/
int Tool::rating()
{
	return rating_;
}

/*
Function:	permanent
Description:	determines if tool is permanent
Arguments:	none
Return:		bool - true if permanent,
			false if not
*/
bool Tool::permanent()
{
	return false;
}

/*
Function:	color
Description:	gets color of occupant depending on derived class
Arguments:	none
Return:		int - color value for ncurses
*/
int Tool::color()
{
	return COLOR_BLACK;
}

/*
Function:	marker
Description:	gets marker for occupant
Arguments:	none
Return:		char - marker for specific occupant class
*/
char Tool::marker()
{
	return 'T';
}

/*
Function:	getDetails
Description:	returns data in the form of strings to pass to ui
Arguments:
Return:		vector<string> - object data to pass to ui
*/
vector<string> Tool::getDetails()
{
	int obstacleCount;

	vector<string> data;
	// push name of tool to vector
	data.push_back(name_);

	// push all strings from forObstacles
	obstacleCount = 0;
	for (vector<string>::iterator it = forObstacles.begin()
		; it != forObstacles.end(); ++it)
	{
		data.push_back(*it);
		++obstacleCount;
	}

	// push values for cost and rating
	data.push_back(to_string(whiffleCost_));
	data.push_back(to_string(rating_));
	
	// push labels 
	for (int i = 0; i < obstacleCount; ++i)
	{
		data.push_back("Obstacle");
	}
	data.push_back("Cost");
	data.push_back("Rating");

	return data;
}

/*
Function:	promptMsg
Description:	gets correct prompt for player for class
Arguments:	Hero& - player 
Return:		string - message to prompt player
*/
string Tool::promptMsg(Hero& theHero)
{
	string msg;

	msg = "Tool found!\n";
	if(theHero.whiffles() >= whiffleCost_)
	{
		msg = msg + name_ + "\n";
		// get all obstacles tool works for
		for (vector<string>::iterator it = forObstacles.begin()
			; it != forObstacles.end(); ++it)
		{
			msg = msg + *it.name() + " : Obstacle\n";
		}
		
		// get tool cost and rating
		msg = msg + to_string(whiffleCost_) + " : Cost\n";
		msg = msg + "X" + to_string(rating_) 
			+ " : Rating\n";
	
		msg = msg + "Purchase? (Y/N):";
	}
	else
	{
		msg = msg + "But you don't have enough Whiffles! "			+ "Sorry!";
	}
	return msg;
}

/*
Function:	interact
Description:	interacts with player according to player response
Arguments:	char - player response to prompt
		Hero& - player
Return:		none
*/
void Tool::interact(char promptResponse, Hero& theHero)
{
	if(theHero.whiffles() < whiffleCost_)
		return;

	switch(promptResponse)
	{
		case 'y':
		case 'Y':
			theHero.addWhiffles(-whiffleCost_);
			theHero.addInventory(this);
			break;
		default:
			return;
	}
}


/*
/////////////////////////////////////////////////////////////////
 Food class derived from TileOccupant
/////////////////////////////////////////////////////////////////
*/

Food::Food(): name_(0), whiffleCost_(0), energyProvided_(0)
{
}

Food::Food(string name, int whiffleCost, int energyProvided)
	: name_(name), whiffleCost_(whiffleCost)
	, energyProvided_(energyProvided)
{
}

/*
Function:	permanent
Description:	determines if occupant is permanent or not
Arguments:	none
Return:		bool - true if perm, false if not
*/
bool Food::permanent()
{
	return false;
}

/*
Function:	color
Description:	gets occupant marker color
Arguments:	none
Return:		int - marker color
*/
int Food::color()
{
	return COLOR_BLACK;
}

/*
Function:	marker
Description:	gets occupant marker 
Arguments:	none
Return:		char - marker 
*/
char Food::marker()
{
	return 'F';
}

/*
Function:	getDetails
Description:	gets data to send to ui
Arguments:	none
Return:		vector<string> - data strings for ui
*/
vector<string> Food::getDetails()
{
	vector<string> data;
	data.push_back(name_);
	data.push_back(to_string(whiffleCost_));
	data.push_back(to_string(energyProvided_));

	// labels
	data.push_back("Food");
	data.push_back("Cost");
	data.push_back("Energy");

	return data;
}

/*
Function:	promptMsg
Description:	gets message to display to user
Arguments:	Hero& - hero to prompt
Return:		string - message to display
*/
string Food::promptMsg(Hero& theHero)
{
	string msg;

	msg = "Food found!\n";
	if(theHero.whiffles() >= whiffleCost_)
	{
		msg = msg + name_ + "\n"
			+ to_string(whiffleCost_) + " : Cost\n"
			+ to_string(energyProvided_) + " : Energy\n";	

		msg = msg + "Purchase? (Y/N):";
	}
	else
	{
		msg = msg + "But you don't have enough Whiffles! "
			+ "Sorry!";
	}
	return msg;
}

/*
Function:	interact
Description:	interacts with user according to response key
Arguments:	char - prompt response key
		, Hero& - hero to interact with
Return:		string - message to display
*/
void Food::interact(char promptResponse, Hero& theHero)
{
	if(theHero.whiffles() < whiffleCost_)
		return;
	switch(promptResponse)
	{
		case 'y':
		case 'Y':
			theHero.addWhiffles(-whiffleCost_);
			theHero.addEnergy(energyProvided_);
			break;
		default:
			return;
	}
}

/*
/////////////////////////////////////////////////////////////////
 Binoculars class derived from TileOccupant
/////////////////////////////////////////////////////////////////
*/

Binoculars::Binoculars(): whiffleCost_(0)
{
}

Binoculars::Binoculars(int whiffleCost): whiffleCost_(whiffleCost)
{
}

/*
Function:	permanent
Description:	determines if occupant is permanent or not
Arguments:	none
Return:		bool - true if perm, false if not
*/
bool Binoculars::permanent()
{
	return false;
}

/*
Function:	color
Description:	gets occupant marker color
Arguments:	none
Return:		int - marker color
*/
int Binoculars::color()
{
	return COLOR_BLACK;
}

/*
Function:	marker
Description:	gets occupant marker 
Arguments:	none
Return:		char - marker 
*/
char Binoculars::marker()
{
	return 'B';
}

/*
Function:	getDetails
Description:	gets data to send to ui
Arguments:	none
Return:		vector<string> - data strings for ui
*/
vector<string> Binoculars::getDetails()
{
	vector<string> data;
	data.push_back("Binoculars");
	
	return data;
}

/*
Function:	promptMsg
Description:	gets message to display to user
Arguments:	Hero& - hero to prompt
Return:		string - message to display
*/
string Binoculars::promptMsg(Hero& theHero)
{
	string msg;

	msg = "Binoculars found!\n";
	if(theHero.whiffles() >= whiffleCost_)
	{
		msg = msg + "Buy Binoculars and double your "
			+ "vision for " + to_string(whiffleCost_) 
			+ " Whiffles? (Y/N):";
	}
	else
	{
		msg = msg + "But you don't have enough Whiffles! "
			+ "Sorry!";
	}
	return msg;
}

/*
Function:	interact
Description:	interacts with user according to response key
Arguments:	char - prompt response key
		, Hero& - hero to interact with
Return:		string - message to display
*/
void Binoculars::interact(char promptResponse, Hero& theHero)
{
	if(theHero.whiffles() < whiffleCost_)
		return;
	switch(promptResponse)
	{
		case 'y':
		case 'Y':
			theHero.addWhiffles(-whiffleCost_);
			theHero.giveBinoculars();
			break;
		default:
			return;
	}
}


/*
/////////////////////////////////////////////////////////////////
 clue class derived from TileOccupant
/////////////////////////////////////////////////////////////////
*/

Clue::Clue(): msg_(0)
{
}

Clue::Clue(string msg): msg_(msg)
{
}

/*
Function:	permanent
Description:	determines if occupant is permanent or not
Arguments:	none
Return:		bool - true if perm, false if not
*/
bool Clue::permanent()
{
	return true;
}

/*
Function:	color
Description:	gets occupant marker color
Arguments:	none
Return:		int - marker color
*/
int Clue::color()
{
	return COLOR_BLACK;
}

/*
Function:	marker
Description:	gets occupant marker 
Arguments:	none
Return:		char - marker 
*/
char Clue::marker()
{
	return '?';
}

/*
Function:	getDetails
Description:	gets data to send to ui
Arguments:	none
Return:		vector<string> - data strings for ui
*/
vector<string> Clue::getDetails()
{
	vector<string> data;
	data.push_back("Clue");
	
	return data;
}

/*
Function:	promptMsg
Description:	gets message to display to user
Arguments:	Hero& - hero to prompt
Return:		string - message to display
*/
string Clue::promptMsg(Hero& theHero)
{
	string msg;
	
	msg = "Clue found!\n";
	return msg + msg_;
}

/*
Function:	interact
Description:	interacts with user according to response key
Arguments:	char - prompt response key
		, Hero& - hero to interact with
Return:	
*/
void Clue::interact(char promptResponse, Hero& theHero)
{
}


/*
/////////////////////////////////////////////////////////////////
 Diamond class derived from TileOccupant
/////////////////////////////////////////////////////////////////
*/

Diamond::Diamond()
{
}

/*
Function:	permanent
Description:	determines if occupant is permanent or not
Arguments:	none
Return:		bool - true if perm, false if not
*/
bool Diamond::permanent()
{
	return false;
}

/*
Function:	color
Description:	gets occupant marker color
Arguments:	none
Return:		int - marker color
*/
int Diamond::color()
{
	return COLOR_WHITE;
}

/*
Function:	marker
Description:	gets occupant marker 
Arguments:	none
Return:		char - marker 
*/
char Diamond::marker()
{
	return '$';
}

/*
Function:	getDetails
Description:	gets data to send to ui
Arguments:	none
Return:		vector<string> - data strings for ui
*/
vector<string> Diamond::getDetails()
{
	vector<string> data;

	data.push_back("Royal Diamonds");

	return data;
}

/*
Function:	promptMsg
Description:	gets message to display to user
Arguments:	Hero& - hero to prompt
Return:		string - message to display
*/
string Diamond::promptMsg(Hero& theHero)
{
	string msg = "Congratulations! You've found the Royal Diamonds!";
	return msg;
}

/*
Function:	interact
Description:	interacts with user according to response key
Arguments:	char - prompt response key
		, Hero& - hero to interact with
Return:	
*/
void Diamond::interact(char promptResponse, Hero& theHero)
{
}





