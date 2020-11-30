#include "UI.h"

bool UserInterface::initialize(){
    // Sets up the UI. Returns false if the screen is the wrong size.
	int scrY, scrX;
    int xp;
	int y, x;
    int yl, xl;

	getmaxyx(stdscr, scrY, scrX);
	if (scrY < MINY || scrX < MINX)
		return false;

	//xp = scrX * 3 / 10;
    xp = WIDTH;
	y = scrY;
    x = xp;
    yl = 0;
    xl = scrX - xp;

    // Create the windows.
// b windows are borders only.
	bmain = newwin(y, x, yl, xl);

// These are the side windows.
    y -= 4;
    x -= 4;
    yl += 2; 
    xl += 2;
    info = newwin(y, x, yl, xl);
    inven = newwin(y, x, yl, xl);

// Popup window border.
    y = scrY / 2;
    x = (scrX - xp) / 2;
    yl = (scrY - y) / 2;
    xl = (scrX - x) / 2;
    bpop = newwin(y, x, yl, xl);

// Popup window.
    y -= 4;
    x -= 4;
    yl += 2;
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
    int ypos = getmaxy(info) / 2;
    int xoffset = -1;
    printTitle(info, ypos, xoffset, LABEL_Inspect);
    printDualCol(info, ++ypos, xoffset, values);
    return;
}

void UserInterface::whifflesEnergy(int whiffles, int energy){
    // Prints the number of whiffles and energy of the hero.
    std::vector<std::string> values = 
    {std::to_string(whiffles), std::to_string(energy),
    LABEL_Whiffles, LABEL_Energy};
    int ypos = getmaxy(info) - 2;
    int xoffset = 0;
    printDualCol(info, ypos, xoffset, values);
    return;
}

void UserInterface::displayInventory(
    std::vector<std::vector<std::string>> tools){
    char ch;
    int maxy, y;
    int ts;

    show_panel(pinven);

    maxy = getmaxy(inven);
    y = 0;
    ts = tools.size();

    // Go through all tools.
    for (int i = 0; i < ts; i++){
        // Go through each line in tool.
        
    }

    while (ch != 'q'){
        ch = getch();
        
    }

    hide_panel(pinven);
    return;
}

// Popup
char UserInterface::popup(std::string msg){
    char ch;
    // Activate the panels that the popup is on.
    show_panel(pbpop);
    show_panel(ppop);
    
    // Add the string.
    werase(pop);
    mvwaddstr(pop, 0, 0, msg.data());

    // Refresh the image.
    update_panels();
    doupdate();
    // Wait for input.
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
    // Activate the panels that the popup is on.
    show_panel(pbpop);
    show_panel(ppop);
    // Add the string.
    werase(pop);
    mvwaddstr(pop, 0, 0, msg.data());
    printDualCol(pop, getmaxy(pop) - 4, 0, values);
    // Refresh the image.
    update_panels();
    doupdate();
    // Wait for input.
    ch = getch();
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
        while (s > WIDTH){
            ypos++;
            s -= WIDTH;
        }
    }
    update_panels();
    doupdate();
    return;
}
