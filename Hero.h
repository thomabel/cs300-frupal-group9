/*
Hero class header
November 2020
*/
#include <vector>
using namespace std;

class Hero{
    public:
    Hero();
    Hero(const  hero &);
    vector<tool*> getUsableTools(obstacle);
    void addInventory(tool *);
    bool consumeTool(tool *);
    int visionRange(void) const;
    bool hasShip(void) const;
    int whiffles(void) const;
    int energy(void) const;
    int addEnergy(int);
    int addWhiffles(int);
    void giveBinoculars(void);
    void giveShip(void);

    private:
    vector<tool*> inventory_;
    bool hasBinoculars_;
    bool hasShip_;
    int whiffles_;
    int energy_;
};

