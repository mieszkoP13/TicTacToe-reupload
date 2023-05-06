#ifndef BOARD_HH
#define BOARD_HH

#include <iostream>
#include <initializer_list>

class Board
{
protected:
  int bSize;
  char **board;

  bool isFieldOccupied(int ind1, int ind2) const;
  bool isCharAcceptable(char cH) const;
  bool isFieldAcceptable(unsigned int ind1, unsigned int ind2) const;
  bool areFieldsAcceptable() const;

public:
  Board(const int &W);
  Board(const Board &B);
  Board(const int &W, const std::initializer_list<std::initializer_list<char>> il);
  void setField(int ind1, int ind2, const char &cH);
  char getField(int ind1, int ind2) const;
  int getBsize() const { return bSize; };
};

std::ostream &operator<<(std::ostream &strumienWy, const Board &M);

#endif
