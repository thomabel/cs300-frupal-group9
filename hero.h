/*
Hero class header
November 2020
*/
#include <vector>
using namespace std;

class hero
{
    public:
    hero();
    hero(const  hero &);
    ~hero();
    

    vector<tool*> getUsableTools(obstacle);
    void addInventory(tool *);
    bool consumeTool(tool *);
    int visionRange(void);
    bool hasShip(void);
    int whiffles(void);
    int energy(void);
    int addEnergy(int);
    int addWhiffles(int);

    private:
    vector<tool*> inventory_;
    bool hasBinoculars_;
    bool hasShip_;
    int whiffles_;
    int energy_;


};
