#include "UI.h"
bool UserInterface::initialize(){
	int scrY, scrX;
	int y, x;

	getmaxyx(stdscr, scrY, scrX);
	if (scrY < MINY || scrX < MINX)
		return false;

	y = scrY;
	x = scrX * 3 / 10;

    if (info != NULL)
        delete info;

	info = newwin(y, x, 0, scrX - x);
	wborder(info,
		BSIDE, BSIDE, BTOP, BTOP,
		BSIDE, BSIDE, BSIDE, BSIDE);
    wrefresh(info);

	return true;
}

void UserInterface::WhiffEn(int whiffles, int energy){
    std::vector<std::string> values;
    std::vector<std::string> labels;

    values.push_back(std::to_string(whiffles));
    values.push_back(std::to_string(energy));
    labels.push_back(LABEL_Whiffles);
    labels.push_back(LABEL_Energy);

    int y;
    y = getmaxy(info);
    printDualColVector(y - 4, 0, "", values, labels);
    return;
}

void UserInterface::Actions(
    std::vector<std::string> keys, 
    std::vector<std::string> labels)
    {
    printDualColVector(1, 0, LABEL_Actions, keys, labels);
    return;
}

void UserInterface::printDualColVector(
    int y, int hor_offset,
    std::string title,
    std::vector<std::string> values, 
    std::vector<std::string> labels)
    {
    int x;
    int center;
    int start;
    std::string str;

    x = getmaxx(info);
    center = x / 2;
    start = title.length() / 2;
    mvwaddstr(info, y++,
        center - start, title.data());
   
    for (unsigned int i = 0; i < values.size(); i++){
        wmove(info, y + i, 0);
        wclrtoeol(info);
        
        if (i >= labels.size())
            continue;
        str = values[i] + " : " + labels[i];
        start = str.find_first_of(':');
        mvwaddstr(info, y + i, 
            center - start + hor_offset, 
            str.data());
    }
    wrefresh(info);
    return;
}

