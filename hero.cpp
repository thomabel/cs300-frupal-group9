   Hero class implementation
   November 2020
 */
#include "hero.h"
using namespace std;

//constructor
hero::hero(){
    hasBinoculars_ = false;
    hasShip_ = false;
    whiffles_ = 1000;
    energy_ = 100;
}

hero::hero(const  hero & orig){
    this->hasBinoculars_ = orig.hasBinoculars_;
    this->hasShip_ = orig.hasShip_;
    this->inventory_ = orig.inventory_;
    this->whiffles_ = orig.whiffles_;
    this->energy_ = orig.energy_;
}
//returns list of tools usable on obstacle
vector<tool*> hero::getUsableTools(obstacle current){
    vector<tool*> usableTools_;
    for(auto i = inventory_.cbegin(); i != inventory_.cend(); ++i){
        // if(i->usableOn(current))
        // {
        usableTools_.push_back(*i);
        // }
    }

    return usableTools_;
}

void hero::addInventory(tool * toAdd){
    inventory_.push_back(toAdd);
}

bool hero::consumeTool(tool * xtool){
    bool success = false;
    for(auto i = inventory_.begin(); i != inventory_.end(); ++i){
        if(*i == xtool){
            inventory_.erase(i);
            success = true;
        }
    }
    return success;
}

int hero::addWhiffles(int value){
    whiffles_ += value;
    return whiffles_;
}

int hero::addEnergy(int value){
    energy_ += value;
    return energy_;
}

void hero::giveBinoculars(void){
    hasBinoculars_ = true;
}

void hero::giveShip(void) {
    hasShip_ = true;
}

//getter functions
int hero::visionRange(void) const{
    if(hasBinoculars_) return 2;
    else return 1;
}

bool hero::hasShip(void) const{
    return hasShip_;
}

int hero::whiffles(void) const{
    return whiffles_;
}

int hero::energy(void) const{
    return energy_;
}

