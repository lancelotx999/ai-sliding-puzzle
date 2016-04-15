#CC = gcc or g++
CC = g++
#CFLAGS are compile flags such as -lm to include <math.h>
#or -std=c++0x for C++11
CFLAGS = -std=c++0x -ggdb
#TARGET is the name of your main file
TARGET = main
#OBJECTS = $(TARGET).o library1.o library.o, all the header files here
OBJECTS = $(TARGET).o nodemap.o shared.o ai.o dfs.o bfs.o
#EXTRA Command line arguments
#Syntax: make EXTRA="arg1 arg2"
?EXTRA =

#Do not modify
$(TARGET) : clean $(OBJECTS)
		$(CC) $(CFLAGS) $(EXTRA) $(OBJECTS) -o $(TARGET).bin

#%.c or %.cpp
%.o : %.cpp
		$(CC) $(CFLAGS) $(EXTRA) -c $<

clean:
	rm -rvf $(OBJECTS) $(TARGET).bin *~
