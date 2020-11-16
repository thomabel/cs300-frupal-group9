CXXFLAGS = -g -Wall -Werror
TARGET = a.out
OBJS = main.o

$(TARGET): $(OBJS)
	g++ $(CXXFLAGS) -o $(TARGET) $(OBJS) -lncurses

clean:
	-rm -f $(TARGET) $(OBJS)

