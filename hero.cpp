/*
   Hero class implementation
   November 2020
 */
#include "hero.h"
using namespace std;

//constructor
hero::hero()
{
    hasBinoculars_ = false;
    hasShip_ = false;
    whiffles_ = 1000;
    energy_ = 100;
}

hero::~hero()
{
   hasBinoculars_ = false;
   hasShip_ = false;
   whiffles_ = 0;
   energy_ = 0;
   inventory_.clear();
}

hero::hero(const  hero & orig)
{
    this->hasBinoculars_ = orig.hasBinoculars_;
    this->hasShip_ = orig.hasShip_;
    this->inventory_ = orig.inventory_;
}
//returns list of tools usable on obstacle
vector<tool*> hero::getUsableTools(obstacle current)
{
    vector<tool*> usableTools_;
    for(auto i = inventory_.cbegin(); i != inventory_.cend(); ++i)
    {
        // if(i->usableOn(current))
        // {
        usableTools_.push_back(*i);
        // }
    }

    return usableTools_;
}

void hero::addInventory(tool * toAdd)
{
    inventory_.push_back(toAdd);
}

bool hero::consumeTool(tool * xtool)
{
    bool success = false;
    for(auto i = inventory_.begin(); i != inventory_.end(); ++i)
    {
        if(*i == xtool)
        {
            inventory_.erase(i);
            success = true;
        }
    }
    return success;
}

int hero::addWhiffles(int value)
{
    whiffles_ += value;
    return whiffles_;
}

int hero::addEnergy(int value)
{
    energy_ += value;
    return energy_;
}

//getter functions
int hero::visionRange(void)
{
    if(hasBinoculars_) return 2;
    else return 1;
}

bool hero::hasShip(void)
{
    return hasShip_;
}

int hero::whiffles(void)
{
    return whiffles_;
}

int hero::energy(void)
{
    return energy_;
}

