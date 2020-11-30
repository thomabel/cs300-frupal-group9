/*
Hero class header
November 2020
*/

#ifndef Hero_CLASS
#define Hero_CLASS

#include <vector>
#include "Map.h"
#include "TileOccupant.h"
#include <vector>
  
using namespace std;

class Hero{
    public:
      Hero();
      Hero(const  hero &);
      vector<Tool*> getUsableTools(Obstacle&);
      vector<vector<string>> getToolOptions(Obstacle&);
      void addInventory(Tool *);
      bool consumeTool(Tool *);
      int visionRange(void) const;
      bool hasShip(void) const;
      int whiffles(void) const;
      int energy(void) const;
      int addEnergy(int);
      int addWhiffles(int);
      void setHasBinoculars(bool);
      void setHasShip(bool);

    private:
      vector<Tool*> inventory_;
      bool hasBinoculars_;
      bool hasShip_;
      int whiffles_;
      int energy_;
};
