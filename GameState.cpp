#include"GameState.h"
#include"Map.h"

GameState::GameState(string mapSrcFile) : Map(mapSrcFile)
{
	CursorX = 0;
	CursorY =0;

	//Where should the player start?
	HeroX =
        HeroY =
}

void GameState::travel(char direction, WINDOW * win)
{
	TileType * temp_type = NULL;
	TileOccupant * occupant_temp = NULL;

	switch(direction)
	{
		//These four cases is when user wants
		//to move the Hero.
		case 'i':
			if(heroY-1 >= -1)
			{
				if(heroY-1 == -1)
					--heroY;
				else
				{
					--heroY;
					temp_type = tileTypeAt(heroX+MinX, heroY+MinY);
					if(temp_type.CanEnter(theHero))
						temp_type.energyCost(theHero);
					else
					{
						++heroY;
						return;
					}
				}
			}
			else
				heroY = 0;
			break;

		case 'k':
			if(heroY+1 < MaxScreenY+1)
			{
				if(heroY+1 == MaxScreenY)
                                        ++heroY;
				else
				{
					++heroY;
					temp_type = tileTypeAt(heroX+MinX, heroY+MinY);
					if(temp_type.CanEnter(theHero))
						temp_type.energyCost(theHero);
					else
					{
						--heroY;
						return;
					}
				}
			
			}
			else
				heroY = MaxScreenY-1;
			break;

		case 'l':
			if(heroX+1 < border+1)
			{
				if(heroX+1 == border)
                                        ++heroX;
                                else
                                {
                                        ++heroX;
                                        temp_type = tileTypeAt(heroX+MinX, heroY+MinY);
                                        if(temp_type.CanEnter(theHero))
                                                temp_type.energyCost(theHero);
                                        else
					{
                                                --heroX;
						return;
					}
                                }

			}
			else
				heroX = border-1;

			break;
		case 'j':
			if(heroX-1 >= -1)
			{
				if(heroX-1 == -1)
                                        --heroX;
                                else
                                {
                                        --heroX;
                                        temp_type = tileTypeAt(heroX+MinX, heroY+MinY);
                                        if(temp_type.CanEnter(theHero))
                                                temp_type.energyCost(theHero);
                                        else
					{
                                                ++heroX;
						return;
					}
                                }

			}
			else
				heroX = 0;
			break;
		default:
			cursorTravel(direction);
			return;

			//break;

	}
	if(ExpandMap())
	{
		for(int i = 0; i<MaxScreenY; ++i)
		{
			for(int j = 0; j<border; ++j)
			{
					attron(COLOR_PAIR(3));
					mvwprintw(win,i ,j," ");

			}
		}
	}

	HeroVision();


	map.displayMap(win);
	attron(COLOR_PAIR(6));
	mvwprintw(win,heroY, heroX, "@");

	wmove(win,cursorY, cursorX);
	wrefresh(win);
}
void GameState::HeroVision()
{
	int visionMax = theHero.visionRange()+1; //With B = 2 without = 1

	if((heroY < MaxScreenY && heroY >= 0) && (heroX < border && heroX >= 0))
	{
		for(int l = 1; l < visionMax; l++)
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
				if((checkI >= 0 && checkI <MaxScreenY) && (checkJ >=0 && checkJ < border))
				{
					//Tile is discovered, set it to true
					 map.tile_revealed(checkI+MinY, checkJ+MinX);
					 //array[checkI+MinY][checkJ+MinX].used = true;
				}
				if(k==6)
					//check down
					checkI = i+1;
				else
					//check right
					checkJ = j+1;
			}
		}
	}
}
void GameState::cursorTravel(char direction)
{
	switch(direction)
	{
		//These four cases is when user wants
                //to move cursor, and these cases move the
                //cursor accordingly.

		//WHat Function to call to get details of Tile
		case 'e':
                        if(cursorY-1 > 0)
                                --cursorY;
                        else
                                cursorY = 0;
                        break;

                case 'd':
                        if(cursorY+1 < MaxScreenY)
                                ++cursorY;
                        else
                                cursorY = MaxScreenY-1;

                        break;


                case 'f':
                        if(cursorX+1 < border)
                                ++cursorX;
                        else
                                cursorX = border-1;
                        break;

                case 's':
                        if(cursorX-1 > 0)
                                --cursorX;
                        else
                                cursorX = 0;
                        break;



	}

}

bool GameState::ExpandMap()
{

		//Explore down the map
		if(heroY == MaxScreenY)
		{
			--heroY;

			temp = heroY + MinY;

			MinY = MaxY - (MaxScreenY/2);
			MaxY = MaxY + (MaxScreenY/2);

			if(MaxY > (MAPSIZE-1))
			{
				MaxY = MAPSIZE;
				MinY = MAPSIZE - MaxScreenY;
			}

			heroY = abs((temp-MinY));
			heroX = heroX;
			return true;

		}
		//Go back up 
		else if(heroY == -1)
		{
			++heroY;
			temp = heroY + MinY;

			MinY -= (MaxScreenY/2);
			MaxY -=(MaxScreenY/2);

			if(MinY <= -1)
			{
				MaxY = MaxScreenY;
				MinY = 0;
			}



			heroY = abs((temp-MinY));
			heroX = heroX;
			return true;

		}
		
		//Explore right
		else if(heroX == border)
		{
			--heroX;

			temp = heroX + MinX;

			MinX = MaxX - (border/2);
			MaxX = MaxX + (border/2);

			if(MaxX > (MAPSIZE -1))
			{
				MaxX = MAPSIZE;
				MinX = MAPSIZE - border;
			}


			heroX = abs(temp-MinX);
                        heroY = heroY;
			return true;
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

				if(MinX <= -1)
				{
					MaxX = border;
					MinX = 0;
				}


				heroX = abs(temp-MinX);
				heroY = heroY;
				return true;
			}

		}
		return false;
}
