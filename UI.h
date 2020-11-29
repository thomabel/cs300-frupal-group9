/*
UI Class
Author: Thomas Abel
Date: 2020-11-19
*/
#ifndef UI_CLASS
#define UI_CLASS
#include <ncurses.h>
#include <string>
#include <vector>

class UserInterface {
private:
    const int MINY = 20;
    const int MINX = 80;
    const char BVER = '#';
    const char BHOR = '=';
    const std::string LABEL_Whiffles = "Whiffles";
    const std::string LABEL_Energy = "Energy";
    const std::string LABEL_Actions = "~Actions~";
    const std::string LABEL_Inspect = "~Inspect~";

public:
	bool intialize();
    void WhiffEn(int whiffles, int energy);
    void Actions(std::vector<std::string> keys,
                 std::vector<std::string> labels);
private:
    void printDualColVector(
        int ver_offset, int hor_offset,
        std::string title,
        std::vector<std::string> values, 
        std::vector<std::string> labels);
	WINDOW *info;
};

#endif
