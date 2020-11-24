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
    

    vector<tool*> getUsableTools(obstacle);
    bool consumeTool(tool *);
    int visionRange(void);
    bool hasShip(void);

    private:
    vector<tool*> inventory_;
    bool hasBinoculars_;
    bool hasShip_;




};

