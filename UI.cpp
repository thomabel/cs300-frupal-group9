#include "UI.h"

bool UserInterface::initialize(unsigned int width){
    // Sets up the UI. Returns false if the screen is the wrong size.
	int scrY, scrX;
    int xp;
	int y, x;
    int yl, xl;

	getmaxyx(stdscr, scrY, scrX);
	if (scrY < MINY || scrX < MINX)
		return false;

	//xp = scrX * 3 / 10;
    xp = width;
	y = scrY;
    x = xp;
    yl = 0;
    xl = scrX - xp;

    // Create the windows.
// b windows are borders only.
	bmain = newwin(y, x, yl, xl);

// These are the side windows.
    y -= 2;
    x -= 4;
    yl += 1; 
    xl += 2;
    info = newwin(y, x, yl, xl);
    inven = newwin(y, x, yl, xl);

// Popup window border.
    float factor = 1.5;
    y = scrY / factor;
    x = (scrX - xp) / factor;
    yl = (scrY - y) / 2;
    xl = (scrX - xp - x) / 2;
    bpop = newwin(y, x, yl, xl);

// Popup window.
    y -= 2;
    x -= 4;
    yl += 1;
    xl += 2;
    pop = newwin(y, x, yl, xl);

    // Add them to the panels.
    pbmain = new_panel(bmain);
    pinfo = new_panel(info);
    pinven = new_panel(inven);
    pbpop = new_panel(bpop);
    ppop = new_panel(pop);

    // Set borders.
	wborder(bmain,
		BVER, BVER, BHOR, BHOR,
		BVER, BVER, BVER, BVER);
	wborder(bpop,
		BVER, BVER, BHOR, BHOR,
		BVER, BVER, BVER, BVER);

    // Hide inventory and popup.
    hide_panel(pinven);
    hide_panel(pbpop);
    hide_panel(ppop);

    // Refresh the screen.
    update_panels();
    doupdate();
	return true;
}


// Information window functions.
void UserInterface::actions(
    std::vector<std::string> values){
    // Prints the actions a player can take at the current time.
    int ypos = 0;
    int xoffset = -3;
    printTitle(info, ypos, xoffset, LABEL_Actions);
    printDualCol(info, ++ypos, xoffset, values);
    return;
}

void UserInterface::tileInspect(
    std::vector<std::string> values){
    // Prints the information of a grovenik and its occupant.
    int ypos = getmaxy(info) / 2 - 2;
    int xoffset = -1;
    printTitle(info, ypos, xoffset, LABEL_Inspect);
    printDualCol(info, ++ypos, xoffset, values);
    return;
}

void UserInterface::whifflesEnergy(int whiffles, int energy){
    // Prints the number of whiffles and energy of the hero.
    std::vector<std::string> values;
    int ypos, xoffset;

    values = {
    std::to_string(whiffles), 
    std::to_string(energy),
    LABEL_Whiffles, 
    LABEL_Energy};
    ypos = getmaxy(info) - 3;
    xoffset = 0;

    printDualCol(info, ypos, xoffset, values);
    return;
}

char UserInterface::displayInventory(
    std::vector<std::vector<std::string>> tools,
    bool getInput){
    char ch;
    int ist;
    int y, cy, cx;
    int ts;

    show_panel(pinven);
    werase(inven);

    ist = 0;
    y = getmaxy(inven);
    cy = 0;
    ts = tools.size();

    do {
        // Print all the tools.
        werase(inven);
        for (int i = ist; i < ts; i++){
            printDualCol(inven, cy, 0, tools[i]);
            getyx(inven, cy, cx);
            cy += 2;
            if (cy > y)
                break;
        }
        cy = 0;
        ch = getch();

        // Scroll upwards.
        if (ch == CTRL_UP){
            ist -= 1;
            if (ist < 0)
                ist = 0;
        }
        // Scroll downwards.
        else if (ch == CTRL_DOWN){
            if (ist < ts)
              ist++;
        }
        else if (getInput && ch != CTRL_INV){
            break;
        }
    } while (ch != CTRL_INV);

    hide_panel(pinven);
    update_panels();
    doupdate();
    return ch;
}

// Popup
char UserInterface::popup(std::string msg){
    char ch;
    // Activate the panels that the popup is on.
    show_panel(pbpop);
    show_panel(ppop);
    
    // Add the string, get input.
    werase(pop);
    mvwaddstr(pop, 0, 0, msg.data());
    ch = getch();

    // Hide popup when finished.
    hide_panel(pbpop);
    hide_panel(ppop);
    update_panels();
    doupdate();

    return ch;
}

char UserInterface::popup(std::string msg,
    std::vector<std::string> values){
    char ch;
    int ypos;
    // Activate the panels that the popup is on.
    show_panel(pbpop);
    show_panel(ppop);

    // Add the string.
    werase(pop);
    mvwaddstr(pop, 0, 0, msg.data());
    ypos = getmaxy(pop) - values.size() / 2 - 1;
    printDualCol(pop, ypos, 0, values);
    // Wait for input.
    ch = getch();

    // Hide the popup when finished.
    hide_panel(pbpop);
    hide_panel(ppop);
    update_panels();
    doupdate();

    return ch;
}

char UserInterface::popup(std::string message,
        std::vector<std::string> obstacle,
        std::vector<std::vector<std::string>> tools){
    char ch;
    int ypos;

    // Activate the panels that the popup is on.
    show_panel(pbpop);
    show_panel(ppop);

    // Display popup text.
    werase(pop);
    mvwaddstr(pop, 0, 0, message.data());
    ypos = getmaxy(pop) - obstacle.size() / 2 - 1;
    printDualCol(pop, ypos, 0, obstacle);
    // Display inventory and get input.
    ch = displayInventory(tools, true);

    // Hide the popup when finished.
    hide_panel(pbpop);
    hide_panel(ppop);
    update_panels();
    doupdate();

    return ch; 
}

// Prints a title string in the center of a window.
void UserInterface::printTitle(
    WINDOW *win, int ypos, int hor_offset, std::string title){
    // Prints the title in the center.
    int start;
    start = (getmaxx(win) - title.length()) / 2;
    mvwaddstr(win, ypos, start, title.data());
    return;
}

// The main method of printing information to the UI elements.
void UserInterface::printDualCol(
    WINDOW *win, int ypos, int hor_offset,
    std::vector<std::string> values){
    int center, start;
    int vcen;
    std::string str;

    // Find center of window and vector.
    center = getmaxx(win) / 2;
    vcen = values.size() / 2;

    // Prints through the vector.
    for (int i = 0; i < vcen; i++){
        // Clear the line of old text.
        wmove(win, ypos + i, 0);
        wclrtoeol(win);
        // Create the string and center it correctly.
        str = values[i] + " : " + values[vcen + i];
        start = center - str.find_first_of(':') + hor_offset;
        if (start < 0)
            start = 0;
        // Print the string.
        mvwaddstr(win, ypos + i, start, str.data());
        // If string is too wide, update ypos.
        int s = str.length();
        int w = getmaxx(win);
        while (s > w){
            ypos++;
            s -= w;
        }
    }
    update_panels();
    doupdate();
    return;
}
