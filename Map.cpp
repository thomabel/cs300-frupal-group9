#include "Map.h"
#include "CsvToOccupant.h"

Tile::Tile() : revealed(false), type(0), occupant(0)
{}

Map::Map()
{
	//Default Map?
}
Map::Map(string srcFile)
{
	if(!(loadFile(srcFile)))
	{
		cout<<"File cannot open"<<endl;
	}
}

//Read in the map
bool Map::loadFile(string src)
{

        string temp;
        int i = 0;
        int j = 0;

        //if(read_file==0)
        ifstream infile;
        //Open the designated file
        //infile.open("practice.txt");
	infile.open(src);
	
	
         //If file was open sucessfully then eneter
        if(infile)
        {

                //If end of file is not triggered then enter the loop
                while(getline(infile,temp))
                {
                        for(unsigned int k = 0;k<temp.size();++k)
                        {

                                if(j == MAPSIZE)
                                {
                                        ++i;
                                        j=0;
                                }

				switch(temp[k])
				{               
					case 'W':
						tileArray[i][j].type = new Water;//Color num 4
						break;
					case 'M':
						tileArray[i][j].type = new Wall;//Color num 7
						break;
					case 'S':
						tileArray[i][j].type = new Swamp; //Color num 5
						break;
					case 'G':
						tileArray[i][j].type = new Meadow; //Color num 2
						break;
				}


                                ++j;

				//How should we go about occupants?

                        }




                }
                infile.close();

        }
	else
	{
		return false;
	}
	/*
	attron(COLOR_PAIR(5));
	mvwprintw(win,5 ,5," ");
	wrefresh(win);
	*/
	
	return true; // placeholder for better things
}

bool Map::loadOccupants(string src)
{
        string temp;

        ifstream fin(src);

        if (fin)
        {
                getline(fin, temp);
                int qty = stoi(temp);
                
                for(int i = 0; i < qty; ++i)
                {
			// Discard whitespace line
                        getline(fin, temp);
                        
                        // Read coordinates of tileOccupant
                        getline(fin, temp, ',');
                        int row = stoi(temp);
                        getline(fin, temp);
                        int col = stoi(temp);
                        
                        // Read tileOccupant type string (without trailing
                        // whitespace)
                        getline(fin, temp);
                        string type = temp.erase(
                                temp.find_last_not_of(" \n\t"));
                                
                        // Read tileOccupant data as comma-separated values
                        getline(fin, temp);
                        
                        // Quit and fail if there were issues with the stream
                        if (!fin)
                                return false;
                        
                        // If the tile already has an occupant, remove it.
                        if (tileArray[row][col] != 0)
                        	delete tileArray[row][col];
                        	
                        tileArray[row][col].occupant = newOccupant(type, temp);
                }
        }
	else
	{
                return false;
	}

        return true;
}

bool Map::saveFile(string dest)
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
			if(tileArray[i][j].type->toString() == "Meadow")
				outfile<<"G";
			else if(tileArray[i][j].type->toString() == "Water")
				outfile<<"W";
			else if(tileArray[i][j].type->toString() == "Wall")
				outfile<<"M";
			else if(tileArray[i][j].type->toString() == "Swamp")
				outfile<<"S";

		}
		outfile<<endl;
	}
	//Close the file
        outfile.close();

	return true;
}

bool Map::saveOccupants(string dest)
{
        ofstream fout("CustomOccupants.txt");

	// Collect occupants (in order to count) before saving to file.
	vector<TileOccupant*> occupants;
	vector<int> rows;
	vector<int> cols;

	for (int i = 0; i < MAPSIZE; ++i)
	{
		for (int j = 0; j < MAPSIZE; ++j)
		{
			TileOccupant *occ = tileArray[i][j].occupant;
			
			if (occ)
			{
                                occupants.push_back(occ);
				rows.push_back(i);
				cols.push_back(j);
			}
		}
	
	}

	if (fout)
	{
		fout << occupants.size() << "\n";

		for (int i = 0; i < occupants.size(); ++i)
		{
			fout << "\n" << rows[i] << "," cols[i] << "\n"
				<< occupants[i]->typeStr() << "\n"
				<< occupants[i]->dataAsCsv() << "\n";
		}
	}
        else
	{
	        return false;	
	}

	return true;
}

//Return what type of tile it is
TileType * Map::tileTypeAt(int row, int col)
{
	return tileArray[row][col].type;
}
//Return what  occupies the tile
TileOccupant * Map::occupantAt(int row, int col)
{
	return tileArray[row][col].occupant;
}
//Reveal the tile(Discovered)
void Map::tile_revealed(int row, int col)
{
	tileArray[row][col].revealed = true;
}

//Have we been at tile before
bool Map::isTileDiscovered(int row, int col)
{
	if(tileArray[row][col].revealed)
		return true;

	return false;
}

//Display what is discovered
void Map::displayMap(WINDOW * win)
{

		//Print the Grovnicks that are used
		for(int i = MinY; i<MaxY; ++i)
		{
			for(int j = MinX; j<MaxX; ++j)
			{
				if(tileArray[i][j].revealed)
				{

					attron(COLOR_PAIR(tileArray[i][j].type->color()));
					mvwprintw(win,i -MinY ,j-MinX," ");
				}

			}
		}
}
