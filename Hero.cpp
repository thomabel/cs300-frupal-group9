   Hero class implementation
   November 2020
 */
#include "Hero.h"
using namespace std;

//constructor
Hero::Hero(){
    hasBinoculars_ = false;
    hasShip_ = false;
    whiffles_ = 1000;
    energy_ = 100;
}

Hero::Hero(const  Hero & orig){
    this->hasBinoculars_ = orig.hasBinoculars_;
    this->hasShip_ = orig.hasShip_;
    this->inventory_ = orig.inventory_;
    this->whiffles_ = orig.whiffles_;
    this->energy_ = orig.energy_;
}
//returns list of tools usable on obstacle
vector<tool*> Hero::getUsableTools(obstacle current){
    vector<tool*> usableTools_;
    for(auto i = inventory_.cbegin(); i != inventory_.cend(); ++i){
        if(i->usableOn(current)){
        usableTools_.push_back(*i);
        }
    }

    return usableTools_;
}

void Hero::addInventory(tool * toAdd){
    inventory_.push_back(toAdd);
}

bool Hero::consumeTool(tool * xtool){
    bool success = false;
    for(auto i = inventory_.begin(); i != inventory_.end(); ++i){
        if(*i == xtool){
            inventory_.erase(i);
            success = true;
        }
    }
    return success;
}

int Hero::addWhiffles(int value){
    whiffles_ += value;
    return whiffles_;
}

int Hero::addEnergy(int value){
    energy_ += value;
    return energy_;
}

void Hero::giveBinoculars(void){
    hasBinoculars_ = true;
}

void Hero::giveShip(void) {
    hasShip_ = true;
}

//getter functions
int Hero::visionRange(void) const{
    if(hasBinoculars_) return 2;
    else return 1;
}

bool Hero::hasShip(void) const{
    return hasShip_;
}

int Hero::whiffles(void) const{
    return whiffles_;
}

int Hero::energy(void) const{
    return energy_;
}

