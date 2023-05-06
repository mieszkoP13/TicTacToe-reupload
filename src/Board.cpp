#include "Board.hh"
#include <iostream>

#define GREEN "\x1b[1;32m"
#define ZOLTY "\x1b[1;93m"
#define BLUE "\x1b[1;94m"
#define RESET "\x1b[0m"

bool Board::isFieldOccupied(int ind1, int ind2) const
{
    if(getField(ind1,ind2) == ' ')
        return false;
    return true;
}

bool Board::isCharAcceptable(char cH) const
{
    if(cH != 'X' && cH != 'O' && cH != ' ')
        return false;
    return true;
}

bool Board::isFieldAcceptable(unsigned int ind1, unsigned int ind2) const
{
    if(!isCharAcceptable( getField(ind1,ind2) ))
        return false;
    return true;
}


bool Board::areFieldsAcceptable() const
{
    for(int i(0); i<bSize ;++i)
        for(int j(0); j<bSize ;++j)
            if(!isFieldAcceptable(i,j))
                return false;
    return true;
}

Board::Board(const int &W) : bSize(W)
{
    char** newBoard = new char*[bSize];
    for(int i(0); i < bSize; ++i)
        newBoard[i] = new char[bSize];

    for (int i(0); i < bSize; ++i)
        for (int j(0); j < bSize; ++j)
            newBoard[i][j] = ' ';
    board = newBoard;
}

Board::Board(const Board &B) : bSize(B.getBsize())
{
    char** newBoard = new char*[bSize];
    for(int i(0); i < bSize; ++i)
        newBoard[i] = new char[bSize];

    for (int i(0); i < bSize; ++i)
        for (int j(0); j < bSize; ++j)
            newBoard[i][j] = B.getField(i,j);
    
    board = newBoard;
}

Board::Board(const int &W, const std::initializer_list<std::initializer_list<char>> il) : bSize(W)
{
    char** newBoard = new char*[bSize];
    for(int i(0); i < bSize; ++i)
        newBoard[i] = new char[bSize];

    int counter(0);
    for (auto row : il)
        std::copy(row.begin(), row.end(), newBoard[counter++]);

    board = newBoard;

    if(!areFieldsAcceptable())
        throw "Nielegalny znak podczas tworzenia planszy!";
}

void Board::setField(int ind1, int ind2, const char &cH)
{
    if(isFieldOccupied(ind1,ind2))
        throw "Pole jest juz zajete; nie postawiono znaku!";

    if(!isCharAcceptable(cH))
        throw "Nielegalny znak podczas ustawiania pola!";

    if(ind1 < 0 || (ind1 >= bSize) || ind2 < 0 || (ind2 >= bSize))
        throw "Krytyczny blad - proba dostania sie do nieistniejacego elementu planszy";
    board[ind1][ind2] = cH;
}

char Board::getField(int ind1, int ind2) const
{
    if(ind1 < 0 || (ind1 >= bSize) || ind2 < 0 || (ind2 >= bSize))
        throw "Krytyczny blad - proba dostania sie do nieistniejacego elementu planszy";
    return board[ind1][ind2];
}

std::ostream &operator<<(std::ostream &strumienWy, const Board &M)
{
    strumienWy << "   ";
    for(int i(0); i < M.getBsize(); ++i)
      strumienWy << " " << GREEN << i << RESET << "  ";
    strumienWy << "\n";


    strumienWy << "  -";
    for(int i(0); i < M.getBsize(); ++i)
        strumienWy << "----";
    strumienWy << "\n";
  
    for (int j(0); j < M.getBsize(); ++j)
    {
        strumienWy << BLUE << j << RESET << " | ";
        for (int k(0); k < M.getBsize(); ++k)
            strumienWy << M.getField(j,k) << " | ";
        strumienWy << "\n";

        strumienWy << "  -";
        for(int l(0); l < M.getBsize(); ++l)
            strumienWy << "----";
        strumienWy << "\n";
    }
    return strumienWy;
}