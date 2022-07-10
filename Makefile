# define variables
SHELL = /bin/sh

VPATH=./src
SOURCE = $(wildcard ./src/*.cpp)
CPPFILES = $(notdir $(SOURCE))
OBJS = $(patsubst %.cpp, %.o, $(CPPFILES))
EXE = main
CFLAG = -Wall
CC = g++
INCLUDES = -I ./include
LIBS = 

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

%.o: %.cpp
	${CC} ${CFLAGS} ${INCLUDES} -o $@ -c $^

.PHONY:clean

clean:
	-rm -f *.o $(EXE)

