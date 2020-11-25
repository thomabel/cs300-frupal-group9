#include<ncurses.h>
#include<vector>
#include<cstring>
#include <string>
#include <cmath>

#include<fstream>
#include<iostream>
using namespace std;


/*
                if(isdigit(choice))
                {
                        if(choice - '0' == 1)
                        {
                                attron(COLOR_PAIR(2));
                                mvwprintw(win,10,10,"hello");
                                wrefresh(win);
                        }
                }
                */
struct tile{
	int color=0;
	char c = 'Z';
	bool used = false;
};

const int MAPSIZE = 128;
void WriteFile(tile array[][128])
{
        //Variable: Outfile
        ofstream outfile;
        //Open the data.txt files
        outfile.open("Custom.txt");
        //Clear what was in function
        outfile.clear();
        //Close the file
        outfile.close();
        //Reopen another file
        outfile.open("Custom.txt", ios::app);


        //Loop through list.

        for(int i=0;i<MAPSIZE;++i)
        {
                for(int j = 0; j<MAPSIZE; ++j)
                {
			switch(array[i][j].c)
			{
				case 'W':
					outfile<<"W";
					break;
				case 'M':
					outfile<<"M";
					break;
				case 'S':
					outfile<<"S";
					break;
				case 'G':
					outfile<<"G";

					break;
			}

                }
                outfile<<endl;
        }
        //Close the file
        outfile.close();
}

void readFile(tile array[][128], string StringTemp, WINDOW * win)
{
        string temp;
        int i = 0;
        int j = 0;

        //if(read_file==0)
        ifstream infile;
        //Open the designated file
        //infile.open("practice.txt");
	infile.open(StringTemp);
	
	
         //If file was open sucessfully then eneter
        if(infile)
        {

                //If end of file is not triggered then enter the loop
                while(getline(infile,temp))
                {
                        for(unsigned int k = 0;k<temp.size();++k)
                        {
                                if(j == 128)
                                {
                                        ++i;
                                        j=0;
                                }
                                array[i][j].c = temp[k];

				switch(array[i][j].c)
				{
					case 'W':
						array[i][j].color = 1;
						break;
					case 'M':
						array[i][j].color = 2;
						break;
					case 'S':
						array[i][j].color = 5;
						break;
					case 'G':
						array[i][j].color = 4;
						break;
				}




                                ++j;

                        }




                }
                infile.close();

        }
	
	//attron(COLOR_PAIR(5));
	wattron(win,COLOR_PAIR(5));
	mvwprintw(win,5 ,5," ");
//	wrefresh(win);
}


int main()
{
	string StringTemp;
	cout<<"WHAT FILE"<<endl;
	cin>>StringTemp;
	cin.ignore(100,'\n');
	StringTemp+=".txt";

	initscr();
	noecho();
	keypad(stdscr, true);

	int border =0;

	//The right side border of the screen
	if(COLS > 128)
		border = 128;
	else
		border = COLS - COLS/4;




	
	tile array[128][128];
	//readFile(array, StringTemp);

	//Assign the colors, could do this within readfile, this loop uncessary 
	for(int i = 0; i<128; ++i)
	{
                for(int j = 0; j<128;++j)
                {
			switch(array[i][j].c)
			{
				case 'W':
					array[i][j].color = 1;
					break;
				case 'M':
                                        array[i][j].color = 2;
                                        break;
				case 'S':
                                        array[i][j].color = 5;
                                        break;
				case 'G':
                                        array[i][j].color = 4;
                                        break;
			}

                }
	}
	start_color();



	init_pair(1, COLOR_YELLOW, COLOR_BLUE);
	init_pair(2, COLOR_GREEN, COLOR_WHITE);
	init_pair(3, COLOR_BLACK, COLOR_BLACK);
	init_pair(4, COLOR_BLACK, COLOR_GREEN);
	init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(6, COLOR_YELLOW, COLOR_RED);

	// For the actual game

	/*
	init_pair(2, COLOR_BLACK, COLOR_GREEN);
	init_pair(3, COLOR_BLACK, COLOR_BLACK);
	init_pair(4, COLOR_WHITE, COLOR_BLUE);
	init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
        init_pair(6, COLOR_YELLOW, COLOR_RED);
        init_pair(7, COLOR_BLACK, COLOR_WHITE);
	*/



	int cursorX = COLS/2;
        int cursorY= LINES/2;

	
	//int MaxScreenX= border;

	//int MaxScreenY = LINES;

	int MaxX= border;

        int MaxY = LINES;


	int MinX = 0;
	int MinY = 0;

	int temp;

	int FrupalY = 0;
	int FrupalX = 0;


	int heroX = cursorX;
	int heroY = cursorY;

	WINDOW * win;
	win = newwin(LINES, COLS-border, 0, border);
	refresh();


	//First four = sides, last four = corners
	wborder(win, '#', ' ', ' ', ' ','#', ' ', '#', ' ');
	wrefresh(win);
	readFile(array, StringTemp, win);
	wrefresh(win);

	mvwprintw(win, 0, (COLS-border)/2, "HI");
	wrefresh(win);


	//readFile(array,stdscr);

	int  choice = 'a';

	while(choice != 'q')
	{
		choice = wgetch(stdscr);

		if(isdigit(choice))
                {
			int i = choice - '0';

			switch(i)
			{
				case 1:
					if(heroY-1 >= -1)
						--heroY;
					else
						heroY = 0;
					break;

				case 2:
					if(heroY+1 < LINES+1)
                                                ++heroY;
                                        else
                                                heroY = LINES-1;
                                        break;

				case 3:
					if(heroX+1 < border+1)
                                                ++heroX;
                                        else
                                                heroX = border-1;

                                        break;
				case 4:
					if(heroX-1 >= -1)
                                                --heroX;
                                        else
                                                heroX = 0;
                                        break;

			}
			//cursorX = heroX-1;
			//cursorY = heroY;
                }
		else
		{




			switch(choice)
			{
				
				//These four cases is when user wants
				//to move cursor, and these cases move the
				//cursor accordingly.
				case KEY_UP:
					if(cursorY-1 > 0)
						--cursorY;
					else
						cursorY = 0;
					break;

				case KEY_DOWN:
					if(cursorY+1 < LINES)
						++cursorY;
					else
						cursorY = LINES-1;

					break;


				case KEY_RIGHT:
					if(cursorX+1 < border)
						++cursorX;
					else
						cursorX = border-1;
					break;

				case KEY_LEFT:
					if(cursorX-1 > 0)
						--cursorX;
					else
						cursorX = 0;
					break;

				
			}

		}
		/*
		//Within the border
		if((heroY < LINES && heroY >= 0) && (heroX < border && heroX >= 0))
		{
			//This is for the hero later on don't need to worry about it now
			int checkJ = heroX-1;
			int checkI = heroY;
			int i = heroY;
			int j = heroX;
			for(int k = 0; k<8;k++)
			{
				//If we are at 2 or 4 then
				//Go up or down 2D array.
				if(k == 2 || k == 4)
				{
					if(k==4)
						//Up 2D array
						checkI = i-1;
					else
						//Down 2D array
						checkI = i+1;
					//Left
					checkJ = j-1;
				}
				else if(k==6)
                                {
					//Check upper cell from original cell we are checking
                                        checkI = i-1;
					//Stay same column
                                        checkJ = j;
                                }
				//Don't go outside the boundries of array
				if((checkI >= 0 && checkI <LINES) && (checkJ >=0 && checkJ < border))
				{
					 attron(COLOR_PAIR(array[checkI+FrupalY][checkJ+FrupalX].color));
					 mvwprintw(stdscr,checkI-FrupalY,heroX-FrupalX," ");
					 array[checkI+FrupalY][checkJ+FrupalX].used = true;
				}
				if(k==6)
					//check down
					checkI = i+1;
				else
					//check right
					checkJ = j+1;
			}
			
			attron(COLOR_PAIR(array[cursorY+FrupalY][cursorX+FrupalX].color));
			mvwprintw(stdscr,cursorY,cursorX," ");
			array[cursorY+FrupalY][cursorX+FrupalX].used = true;
		}
		*/


		//Reset the map to all black, this will probably only
		//be needed when we go to another section of the map, don't need to do it everytime.
		/*
		for(int i = MinY; i<MaxY; ++i)
                {
                        for(int j = MinX; j<MaxX; ++j)
                        {
                                        attron(COLOR_PAIR(3));
                                        mvwprintw(stdscr,i -FrupalY ,j-FrupalX," ");

                        }
                }
		*/

		//Explore down the map
		if(heroY == LINES)
		{
			--heroY;

			temp = heroY + MinY;

			MinY = MaxY - (LINES/2);
			MaxY = MaxY + (LINES/2);

			if(MaxY - MinY < LINES)
				++MaxY;

			if(MaxY > 127)
			{
				MaxY = 128;
				MinY = 128- LINES;
			}
			FrupalY = MinY;

			heroY = abs((temp-MinY));
	//		heroX = heroX;
			//array[heroY+FrupalY][heroX+FrupalX].used = true;

		}
		//Go back up 
		else if(heroY == -1)
		{
			++heroY;
			temp = heroY + MinY;

			MinY -= (LINES/2);
			MaxY -=(LINES/2);

			if(MinY <= -1)
			{
				MaxY = LINES;
				MinY = 0;
			}

			FrupalY = MinY;


			heroY = abs((temp-MinY));
	//		heroX = heroX;

		}
		
		//Explore right
		else if(heroX == border)
		{
			--heroX;

			temp = heroX + MinX;

			MinX = MaxX - (border/2);
			MaxX = MaxX + (border/2);

			if(MaxX - MinX < border)
                                ++MaxX;

			if(MaxX > 127)
			{
				MaxX = 128;
				MinX = 128- border;
			}
			FrupalX = MinX;


			heroX = abs(temp-MinX);
          //              heroY = heroY;
		}

		//explore left
		else if(heroX == -1)
		{
			++heroX;

			if(MinX != 0)
			{

				temp = heroX + MinX;

				MinX -= (border/2);
				MaxX -= (border/2);
				/*
				if(MaxX < 128)
				{
					MaxX = border;
					MinX = 0;
				}
				*/
				if(MinX <= -1)
				{
					MaxX = border;
					MinX = 0;
				}
				FrupalX = MinX;


				heroX = abs(temp-MinX);
	//			heroY = heroY;
			}

			//array[heroY+FrupalY][heroX+FrupalX].used = true;
		}
		/*
		for(int i = MinY; i<MaxY; ++i)
                {
                        for(int j = MinX; j<MaxX; ++j)
                        {
                                        attron(COLOR_PAIR(3));
                                        mvwprintw(stdscr,i -FrupalY ,j-FrupalX," ");

                        }
                }
		*/
		

		for(int i = 0; i<LINES; ++i)
                {
                        for(int j = 0; j<border; ++j)
                        {
                                        attron(COLOR_PAIR(3));
                                        mvwprintw(stdscr,i ,j," ");

                        }
                }


		if((heroY < LINES && heroY >= 0) && (heroX < border && heroX >= 0))
		{
			//This is for the hero later on don't need to worry about it now
			int checkJ = heroX-1;
			int checkI = heroY;
			int i = heroY;
			int j = heroX;
			for(int l = 1; l< 3; l++)
			{
				for(int k = 0; k<8;k++)
				{
					//If we are at 2 or 4 then
					//Go up or down 2D array.
					if(k == 2 || k == 4)
					{
						if(k==4)
							//Up 2D array
							checkI = i-l;
						else
							//Down 2D array
							checkI = i+l;
						//Left
						checkJ = j-l;
					}
					else if(k==6)
					{
						//Check upper cell from original cell we are checking
						checkI = i-l;
						//Stay same column
						checkJ = j;
					}
					//Don't go outside the boundries of array
					if((checkI >= 0 && checkI <LINES) && (checkJ >=0 && checkJ < border))
					{
						 //attron(COLOR_PAIR(array[checkI+FrupalY][checkJ+FrupalX].color));
						 //mvwprintw(stdscr,checkI-FrupalY,heroX-FrupalX," ");
						 array[checkI+FrupalY][checkJ+FrupalX].used = true;
					}
					if(k==6)
						//check down
						checkI = i+l;

					else
					{
						//check right
						checkJ = j+l;
					}
				}
			}
		}
		//Print the Grovnicks that are used
		for(int i = MinY; i<MaxY; ++i)
		{
			for(int j = MinX; j<MaxX; ++j)
			{
				if(array[i][j].used)
				{
					attron(COLOR_PAIR(array[i][j].color));
					mvwprintw(stdscr,i -FrupalY ,j-FrupalX," ");
				}

			}
		}
		attron(COLOR_PAIR(6));
		mvwprintw(stdscr,heroY, heroX, "@");

		wmove(stdscr,cursorY, cursorX);
                refresh();





	}
	WriteFile(array);

	endwin();

	return 0;
}
