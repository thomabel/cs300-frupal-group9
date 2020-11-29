#include <stdexcept>
#include "TileOccupant.h"

Obstacle::Obstacle(std::string name, int energyCost) : name_(name), 
    energyCost_(energyCost)
{}

std::string Obstacle::name()
{
    return name_;    
}

std::string Obstacle::promptMsg(Hero& theHero)
{
    /* The proper operator overloads and implicit constructors are available in
     * <string> for the below statement to compile.
     */
    return std::string("You must remove a " + name_ + " to continue. Doing"
    + " so without a tool will consume " + std::to_string(energyCost)
    + " points of energy. Select a tool or press \"space\" for no tool.");
}

void Obstacle::interact(char promptResponse, Hero& theHero)
{
    std::vector<Tool*> usableTools = theHero.getUsableTools(*this);

    // Throw exception if promptResponse an impossible value. 
    if ((promptResponse >= usableTools.size() || promptResponse < 0) && 
        promptResponse != ' ')
    {
        throw std::invalid_argument("Invalid promptResponse: " 
            + std::to_string(int(promptResponse)) 
            + " (number of usable tools: "
            + std::to_string(usableTools.size())
            + ")");
    }

    // If a tool was chosen, calculate new energy cost and consume the tool.
    if (promptResponse != ' ')
    {
        // Check if the pointer to the chosen tool is null
        Tool *chosenTool = usableTools.at(int(promptResponse));

        if (!chosenTool)
            throw std::runtime_error("missing tool");

        // Cost is reduced by a factor of the rating, rounding up.
        energyCost_ /= usableTools.at(int(promptResponse))->rating();
        energyCost_++;

        // Remove the tool from the Hero's inventory.
        theHero.consumeTool(chosenTool);
    }

    theHero.addEnergy(-energyCost_);

    /* Like for any other TileOccupant, the caller will remove this Obstacle
     * from the map after verifying that it is not permanent. Similarly, caller
     * should check whether the hero has died.
     */
}

bool Obstacle::permanent() override
{
    return false;
}

int Obstacle::color() override
{
    return COLOR_BLACK;
}

char Obstacle::marker() override
{
    return '!';
}

std::vector<std::string> Obstacle::getDetails() override
{
    std::vector<std::string> details;

    details.push_back(name_);
    details.push_back(std::to_string(energyCost_));
    details.push_back("Obstacle");
    details.push_back("Energy cost");

    return details;
}

Binoculars::Binoculars(int whiffleCost) : whiffleCost_(whiffleCost), 
    consumed_(false);
{}

std::string Binoculars::promptMsg(Hero& theHero) override
{
    if (theHero.whiffles() < whiffleCost_)
    {
        return std::string("You cannot afford these binoculars.")
    }
    else
    {
        // Price not listed because item details are also included in the 
        // popup.
        return std::string("Would you like to buy these binoculars? Press Y"
            + " to purchase or any other key to not.");
    }
}

// Gives the Hero binoculars if the user chooses to purchase.
void Binoculars::interact(char promptResponse, Hero& theHero) override
{
    if (theHero.whiffles() < whiffleCost_)
    {
        // Regardless of the response, these binoculars were not purchased.
        return;
    }

    if (promptResponse == 'y' || promptResponse == 'Y')
    {
        theHero.giveBinoculars();
        theHero.addWhiffles(-whiffleCost_);
    }
}

bool Binoculars::permanent() override
{
    return !consumed_;
}

int Binoculars::color() override
{
    return COLOR_BLACK;
}

char Binoculars::marker() override
{
    return 'B';
}

std::vector<std::string> Binoculars::getDetails() override
{
    std::vector<std::string> details;

    details.push_back("Binoculars");
    details.push_back(std::to_string(whiffleCost_));
    details.push_back("Tool");
    details.push_back("Price");

    return details;
}