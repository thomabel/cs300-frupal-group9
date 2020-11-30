/*
FileName:	TileOccupant.h
Author:		Drew McKinney
Group:		9
Description:	
		TileOccupant and derived classes header file
*/

#ifndef TileOccupant_CLASS
#define TileOccupant_CLASS

#include<ncurses.h>
#include<vector>
#include <string>
#include <stdexcept>
#include "Hero.h"

using namespace std;

class TileOccupant
{
	public:
		TileOccupant();
		virtual bool permanent()=0;
		virtual int color()=0;
		virtual char marker()=0;
		virtual vector<string> getDetails()=0;
		virtual string promptMsg(Hero& theHero)=0;
		virtual void interact(char promptResponse, Hero& theHero)=0;
	protected:
};


class Treasure: public TileOccupant
{
	public:
		Treasure();
		Treasure(int worth);
		bool permanent();
		int color();
		char marker();
		vector<string> getDetails();
		string promptMsg(Hero& theHero);
		void interact(char promptResponse, Hero& theHero);
	protected:
		int worth_;
};

class Ship: public TileOccupant
{
	public:
		Ship();
		Ship(int whiffleCost);
		bool permanent();
		int color();
		char marker();
		vector<string> getDetails();
		string promptMsg(Hero& theHero);
		void interact(char promptResponse, Hero& theHero);
	protected:
		int whiffleCost_;
		bool bought_;
};

class Obstacle : public TileOccupant
{
public:
    Obstacle(std::string name, int energyCost);

    std::string name() const;

    std::string promptMsg(Hero& theHero) override;
    void interact(char promptResponse, Hero& theHero) override;
    bool permanent() override;
    int color() override;
    char marker() override;
    std::vector<std::string> getDetails() override;

private:
    std::string name_;
    int energyCost_;
};

class Tool: public TileOccupant
{
	public:
		Tool();
		Tool(string name, int whiffleCost, int rating);
		bool usableOn(const Obstacle& onObstacle);
		int rating();
		bool permanent();
		int color();
		char marker();
		vector<string> getDetails();
		string promptMsg(Hero& theHero);
		void interact(char promptResponse, Hero& theHero);
	protected:
		string name_;
		int whiffleCost_;
		int rating_;
		vector<string> forObstacles;
};

class Food: public TileOccupant
{
	public:
		Food();
		Food(string name, int whiffleCost, int energyProvided);
		bool permanent();
		int color();
		char marker();
		vector<string> getDetails();
		string promptMsg(Hero& theHero);
		void interact(char promptResponse, Hero& theHero);
	protected:
		string name_;
		int whiffleCost_;
		int energyProvided_;
};

class Binoculars: public TileOccupant
{
	public:
		Binoculars();
		Binoculars(int whiffleCost);
		bool permanent();
		int color();
		char marker();
		vector<string> getDetails();
		string promptMsg(Hero& theHero);
		void interact(char promptResponse, Hero& theHero);
	protected:
		int whiffleCost_;
};

class Clue: public TileOccupant
{
	public:
		Clue();
		Clue(string msg);
		bool permanent();
		int color();
		char marker();
		vector<string> getDetails();
		string promptMsg(Hero& theHero);
		void interact(char promptResponse, Hero& theHero);
	protected:
		string msg_;
};

class Diamond: public TileOccupant
{
	public:
		Diamond();
		bool permanent();
		int color();
		char marker();
		vector<string> getDetails();
		string promptMsg(Hero& theHero);
		void interact(char promptResponse, Hero& theHero);
	protected:
};
