#ifndef TICTACTOE_HH
#define TICTACTOE_HH

#include <iostream>
#include "Board.hh"

#define MAX_DEPTH_5x5 6
#define MAX_DEPTH_4x4 10
#define MAX_DEPTH_3x3 10

struct Move
{
    int x, y;
};

class TicTacToe : public Board
{
    private:
    int numOfCharsToWin;
    char PLAYER_char, AI_char;
    int maxDepth;

    public:
    TicTacToe(const Board &B, int nOCTW, char PL_ch, char AI_ch) : Board(B), numOfCharsToWin(nOCTW), PLAYER_char(PL_ch), AI_char(AI_ch)
    {
        switch (bSize)
        {
        case 3:
            maxDepth = MAX_DEPTH_3x3;
            break;
        case 4:
            maxDepth = MAX_DEPTH_4x4;
            break;
        case 5:
            maxDepth = MAX_DEPTH_5x5;
            break;
        default:
            exit(-1);
        }
    };

    int getNumOfCharsToWin() const { return numOfCharsToWin; };
    void setNumOfCharsToWin(const int& NOCTW) const;
    char getPLchar() const { return PLAYER_char; };
    char getAIchar() const { return AI_char; };
    int getMaxDepth() const { return maxDepth; };
    void swapPlayersChars();

    char winConditionMet(const char &checkedChar) const;
    Move findBestMove();
    int minimax(int depth, bool isMax, int alpha, int beta);
};

#endif