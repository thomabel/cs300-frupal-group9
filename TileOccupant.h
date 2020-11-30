/*
FileName:	TileOccupant.h
Author:		Drew McKinney
Group:		9
Description:	
		TileOccupant and derived classes header file
*/

#include <ncurses.h>
#include <string>
#include <vector>
#include <stdexcept>
#include "Hero.h"

using namespace std;

// Used by Obstacle to validate user choice of tool
int charToChoiceIndex(char c);
char choiceIndexToChar(int ind);


class TileOccupant
{
	public:
		TileOccupant();
        virtual ~TileOccupant();
		virtual bool permanent()=0;
		virtual int color()=0;
		virtual char marker()=0;
		virtual vector<string> getDetails()=0;
		virtual string promptMsg(Hero& theHero)=0;
		virtual bool interact(char promptResponse, Hero& theHero);
        virtual string typeStr() const =0;
        virtual string dataAsCsv() const =0;
	protected:
};



class Treasure: public TileOccupant
{
	public:
		Treasure();
		Treasure(int worth);
		bool permanent() override;
		int color() override;
		char marker() override;
		vector<string> getDetails() override;
		string promptMsg(Hero& theHero) override;
		bool interact(char promptResponse, Hero& theHero) override;
        string typeStr() const override;
        string dataAsCsv() const override;
	protected:
		int worth_;
};

class Ship: public TileOccupant
{
	public:
		Ship();
		Ship(int whiffleCost);
		bool permanent() override;
		int color() override;
		char marker() override;
		vector<string> getDetails() override;
		string promptMsg(Hero& theHero) override;
		bool interact(char promptResponse, Hero& theHero) override;
        string typeStr() const override;
        string dataAsCsv() const override;
	protected:
		int whiffleCost_;
		bool bought_;
};

class Tool: public TileOccupant
{
	public:
		Tool();
        Tool(const Tool& obj);
		Tool(string name, int whiffleCost, int rating, vector<string> obst);
		bool usableOn(const Obstacle& onObstacle) override;
		int rating() override;
		bool permanent() override;
		int color() override;
		char marker() override;
		vector<string> getDetails() override;
		string promptMsg(Hero& theHero) override;
		bool interact(char promptResponse, Hero& theHero) override;
        string typeStr() const override;
        string dataAsCsv() const override;
	protected:
		string name_;
	    bool bought_;	
        int whiffleCost_;
		int rating_;
		vector<string> forObstacles;
};

class Food: public TileOccupant
{
	public:
		Food();
		Food(string name, int whiffleCost, int energyProvided);
		bool permanent() override;
		int color() override;
		char marker() override;
		vector<string> getDetails() override;
		string promptMsg(Hero& theHero) override;
		bool interact(char promptResponse, Hero& theHero) override;
        string typeStr() const override;
        string dataAsCsv() const override;
	protected:
		string name_;
        bool consumed_;
		int whiffleCost_;
		int energyProvided_;
};

class Clue: public TileOccupant
{
	public:
		Clue();
		Clue(string msg);
		bool permanent() override;
		int color() override;
		char marker() override;
		vector<string> getDetails() override;
		string promptMsg(Hero& theHero) override;
		bool interact(char promptResponse, Hero& theHero) override;
        string typeStr() const override;
        string dataAsCsv() const override;
	protected:
		string msg_;
};

class Diamond: public TileOccupant
{
	public:
		Diamond();
		bool permanent();
		int color() override;
		char marker() override;
		vector<string> getDetails() override;
		string promptMsg(Hero& theHero) override;
		bool interact(char promptResponse, Hero& theHero) override;
        string typeStr() const override;
        string dataAsCsv() const override;
	protected:
};

class Obstacle
{
public:
    Obstacle() = delete;
    Obstacle(std::string name, int energyCost);

    string name() const;
    std::string promptMsg(Hero& theHero) override;
    bool interact(char promptResponse, Hero& theHero) override;
    bool permanent() override;
    int color() override;
    char marker() override;
    std::vector<std::string> getDetails() override;

private:
    std::string name_;
    int energyCost_;
};

class Binoculars
{
public:
    Binoculars() = delete;
    Binoculars(int whiffleCost);

    std::string promptMsg(Hero& theHero) override;
    bool interact(char promptResponse, Hero& theHero) override;
    bool permanent() override;
    int color() override;
    char marker() override;
    std::vector<std::string> getDetails() override;
    string typeStr() const override;
    string dataAsCsv() const override;

private:
    bool bought_;
    int whiffleCost_;
};
