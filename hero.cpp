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


bool hero::consumeTool(tool * xtool)
{

    for(auto i = inventory_.begin(); i != inventory_.end(); ++i)
        if(*i == xtool)
        {
            inventory_.erase(i);
            return true;
        }
        else return false;
}

int hero::visionRange(void)
{
    if(hasBinoculars_) return 2;
    else return 1;
}

bool hero::hasShip(void)
{
    return hasShip_;
}
