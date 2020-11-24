/*
Hero class header
November 2020
*/
#include <vector>
using namespace std;


struct tool
{
    int num = 0;
};

struct obstacle
{
    int num = 0;
};

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

