CXXFLAGS = -g -Wall -Werror
TARGET = Frupal
OBJS = Main.o GameState.o Map.o Hero.o TileOccupant.o TileType.o CsvToOccupant.o UI.o

$(TARGET): $(OBJS)
	g++ $(CXXFLAGS) -o $(TARGET) $(OBJS) -lpanel -lncurses

clean:
	-rm -f $(TARGET) $(OBJS)

