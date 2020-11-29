#include <ncurses>
#include <string>
#include <vector>
#include "Hero.h"

class Obstacle
{
public:
    Obstacle(std::string name, int energyCost);

    std::string name() const;

    /* This is the first message displayed when the Hero enters a Grovnick with an
     * obstacle.
     * For "Obstacle," an incomplete message is provided since Tool options are
     * not printed in the message pop-up window. Instead, they are listed in the
     * side-menu.
     */
    std::string promptMsg(Hero& theHero) override;

    /* Obstacle::interact expects to receive a response to the prompt returned 
     * by promptMsg. Specifically, either ' ' for no tool, or the index of the 
     * selected tool in the vector returned by Hero::getUsableTools (remember 
     * that in C++ 'char' is an integer, always exactly 1-byte).
     * 
     * This function deducts energy and calls Hero::consumeTool to 
     * 
     * Bugs: ' ' is indistinguishable from index 32. The size of char restricts
     * the maximum index to 255 (generally).
     */
    void interact(char promptResponse, Hero& theHero) override;
    
    bool permanent() override;
    int color() override;
    char marker() override;
    std::vector<std::string> getDetails() override;

private:
    std::string name_;
    int energyCost_;
};

class Binoculars
{
public:
    Binoculars(int whiffleCost);

    // This message gives the hero the option to purchase binoculars.
    std::string promptMsg(Hero& theHero) override;

    // Gives the Hero binoculars if the user chooses to purchase. 
    void interact(char promptResponse, Hero& theHero) override;
    
    bool permanent() override;
    int color() override;
    char marker() override;
    std::vector<std::string> getDetails() override;

private:
    bool consumed_;
    int whiffleCost_;
}