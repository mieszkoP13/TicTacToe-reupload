#include "Board.hh"
#include "TicTacToe.hh"

void TicTacToe::setNumOfCharsToWin(const int &NOCTW) const
{
    if (NOCTW < 0 || NOCTW > bSize)
        throw "Bledna ilosc znakow potrzebna aby wygrac; nie zmieniono";
    setNumOfCharsToWin(NOCTW);
}

void TicTacToe::swapPlayersChars()
{
    if (PLAYER_char == 'X')
    {
        PLAYER_char = 'O';
        AI_char = 'X';
    }
    else
    {
        PLAYER_char = 'X';
        AI_char = 'O';
    }
}

// '-' - nikt nie wygral, 'X'- wygral gracz z X, 'O'- wygral gracz z O, '=' - remis
char TicTacToe::winConditionMet(const char &checkedChar) const
{
    // Check Horizontally
    for (int i(0); i < bSize; ++i)
    {
        for (int j(0); j < bSize - numOfCharsToWin + 1; ++j)
        {
            int k(0);
            for (; k < numOfCharsToWin; ++k)
                if (this->getField(i, j + k) != checkedChar)
                    break;

            if (k == numOfCharsToWin)
                return checkedChar;
        }
    }

    // Check Vertically
    for (int i(0); i < bSize; ++i)
    {
        for (int j(0); j < bSize - numOfCharsToWin + 1; ++j)
        {
            int k(0);
            for (; k < numOfCharsToWin; ++k)
                if (this->getField(j + k, i) != checkedChar)
                    break;

            if (k == numOfCharsToWin)
                return checkedChar;
        }
    }

    // Check Left Diagonal first part
    int p(0);
    int k(0);
    int winCounter(0);
    for (int i(bSize - numOfCharsToWin); i >= 0; --i)
    {
        for (int x(0); x <= p; ++x)
        {
            for (k = 0; k < numOfCharsToWin; ++k)
                if (this->getField(i + k + x, k + x) == checkedChar)
                    ++winCounter;

            if (winCounter == numOfCharsToWin)
                return checkedChar;
            winCounter = 0;
        }
        p++;
    }

    p = 0;
    k = 0;
    winCounter = 0;
    // Check Left Diagonal second part
    for (int i(bSize - numOfCharsToWin); i >= 0; --i)
    {
        for (int x(0); x <= p; ++x)
        {
            for (k = 0; k < numOfCharsToWin; ++k)
                if (this->getField(k + x, i + k + x) == checkedChar)
                    ++winCounter;

            if (winCounter == numOfCharsToWin)
                return checkedChar;
            winCounter = 0;
        }
        p++;
    }

    // Check Right Diagonal first part
    p = 0;
    k = 0;
    winCounter = 0;
    for (int i(numOfCharsToWin - 1); i < bSize; ++i)
    {
        for (int x(0); x <= p; ++x)
        {
            for (k = 0; k < numOfCharsToWin; ++k)
                if (this->getField(i - k - x, k + x) == checkedChar)
                    ++winCounter;

            if (winCounter == numOfCharsToWin)
                return checkedChar;
            winCounter = 0;
        }
        p++;
    }

    // Check Right Diagonal second part
    p = 0;
    k = 0;
    winCounter = 0;
    for (int i(bSize - numOfCharsToWin); i >= 0; --i)
    {
        for (int x(0); x <= p; ++x)
        {
            for (k = 0; k < numOfCharsToWin; ++k)
                if (this->getField(i + k + x, bSize - 1 - k - x) == checkedChar)
                    ++winCounter;

            if (winCounter == numOfCharsToWin)
                return checkedChar;
            winCounter = 0;
        }
        p++;
    }

    for (int i(0); i<bSize; ++i)
        for (int j(0); j<bSize; ++j)
            if (board[i][j]==' ')
                return '-'; //brak zwyciezcy

    return '='; //remis
}

const int& min(const int& a, const int& b)
{
    return (b < a) ? b : a;
}

const int& max(const int& a, const int& b)
{
    return (a < b) ? b : a;
}

int TicTacToe::minimax(int depth, bool isMax, int alpha, int beta)
{
    if(depth>=getMaxDepth())
    {
        if(winConditionMet(PLAYER_char)==PLAYER_char)
            return -10;
        else if(winConditionMet(AI_char)==AI_char)
            return 10;
        else
            return 0;
    }

    if(winConditionMet(PLAYER_char)==PLAYER_char)
        return -10;

    if(winConditionMet(AI_char)==AI_char)
        return 10;

    if(winConditionMet('*')=='=')
        return 0;

    if (isMax)
    {
        int best = -1000;
 
        for (int i(0); i<bSize; ++i)
            for (int j(0); j<bSize; ++j)
                if (board[i][j]==' ')
                {
                    board[i][j] = AI_char;
 
                    best = max( best, minimax(depth+1, false,alpha,beta) );
 
                    board[i][j] = ' ';

                    alpha = max(alpha, best);
                    if(alpha>=beta)
                        return best-depth;
                }
        return best-depth;
    }
    else
    {
        int best = 1000;
 
        for (int i(0); i<bSize; ++i)
            for (int j(0); j<bSize; ++j)
                if (board[i][j]==' ')
                {
                    board[i][j] = PLAYER_char;

                    best = min(best, minimax(depth+1, true,alpha,beta));

                    board[i][j] = ' ';

                    beta = min(beta, best);
                    if (beta <= alpha)
                        return best+depth;
                }
        return best+depth;
    }
}

Move TicTacToe::findBestMove()
{
    int bestVal = -1000;
    Move bestMove;
    bestMove.x = -1;
    bestMove.y = -1;

    for (int i(0); i<bSize; ++i)
        for (int j(0); j<bSize; ++j)
            if (board[i][j]==' ')
            {
                board[i][j] = AI_char;

                int moveVal = minimax(0, false,-1000,1000);
 
                board[i][j] = ' ';

                if (moveVal > bestVal)
                {
                    bestMove.x = i;
                    bestMove.y = j;
                    bestVal = moveVal;
                }
            }
    return bestMove;
}