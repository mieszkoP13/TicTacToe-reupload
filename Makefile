CC = g++
CPPFLAGS = -Wall -pedantic -I inc -Werror -std=c++0x
LIBS = -lm

SRC = main.cpp TicTacToe.cpp Board.cpp
SRCDIR = src

OBJ = $(SRC:.cpp=.o)
OBJDIR = obj
OBJSUBST = $(patsubst %,$(OBJDIR)/%,$(OBJ))

DEPS =  TicTacToe.hh Board.hh #bez maina
DEPSDIR = inc
DEPSSUBST = $(patsubst %,$(DEPSDIR)/%,$(DEPS))

all: a.out

obj:
	mkdir -p obj

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(DEPSSUBST) obj
	$(CC) -c $< -o $@ $(CPPFLAGS) $(LIBS)

a.out: $(OBJSUBST)
	$(CC) $(OBJSUBST) $(CPPFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f obj/*.o *.out
