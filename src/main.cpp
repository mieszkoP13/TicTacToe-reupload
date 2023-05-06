#include <iostream>
#include <ctime>
#include <cctype>
#include "Board.hh"
#include "TicTacToe.hh"

#define CZERWONY "\x1b[1;91m"
#define GREEN "\x1b[1;32m"
#define ZOLTY "\x1b[1;93m"
#define BLUE "\x1b[1;94m"
#define WHITEUNDERL "\x1b[4;37m"
#define CZARNY "\x1b[1;90m"
#define BIALE_TLO "\x1b[47m"
#define RESET "\x1b[0m"

bool readCoordinates(int *x, int *y)
{
  if (!isdigit(std::cin.get())) // sprawdzenie czy nastepny znak jest cyfra
    return false;
  else
    std::cin.unget();

  std::cin >> *x;

  if (std::cin.get() != ' ') // sprawdzenie czy nastepny znak jest spacja
    return false;

  if (!isdigit(std::cin.get())) // sprawdzenie czy nastepny znak jest cyfra
    return false;
  else
    std::cin.unget();

  std::cin >> *y;
  return true;
}

void wyswietlMenu()
{
    std::cout << "g - gra\n";
    std::cout << "m - wyswietl menu\n";
    std::cout << "k - koniec dzialania programu\n";
}

void wait4key()
{
    std::cin.clear();
    std::cout << GREEN << "Naciśnij ENTER, aby kontynuowac\n" << RESET;
    std::cin.ignore(10000, '\n');
}

int main()
{
    wait4key();

    char znakMenu('x');

    wyswietlMenu();

    while (znakMenu != 'k')
    {
        std::cout << BLUE << "Twoj wybor? (m - menu) > " << RESET;
        std::cin >> znakMenu;
        
        switch (znakMenu)
        {
        case 'g':
        {
          std::cout << "Wybierz rozmiar planszy NxN do gry: (Wpisz N, przedzial 3-5)\n";

          int size(0);
          std::cin >> size;

          if (!std::cin || size < 3 || size > 5)
          { std::cout << CZERWONY << "Bledny rozmiar pola lub niepoprawny format; nie rozpoczeto gry\n" << RESET; }
          else
          {
            std::cout << "Wybierz ilosc N wygrywajacych znakow w rzedzie: (Przedzial 2-6, ale prosze wpisac ilosc adekwatna do rozmiaru planszy)\n";
            int numChrsToWin(0);
            std::cin >> numChrsToWin;

            if (!std::cin || numChrsToWin < 2 || numChrsToWin > 5)
            { std::cout << CZERWONY << "Bledna ilosc N wygrywajacych znakow w rzedzie; nie rozpoczeto gry\n" << RESET; }
            else
            {
              std::cout << "Wybierz znak ktorym bedziesz grac: (X lub O)\n";
              char PL_char('z');
              std::cin >> PL_char;

              if (!std::cin || (PL_char != 'X' && PL_char != 'O'))
              { std::cout << CZERWONY << "Bledny znak; nie rozpoczeto gry\n" << RESET; }
              else
              {
                std::cout << "Wybierz znak ktory zacznie rozgrywke: (X lub O)\n";
                char __char('z');
                std::cin >> __char;

                if (!std::cin || (__char != 'X' && __char != 'O'))
                { std::cout << CZERWONY << "Bledny znak; nie rozpoczeto gry\n" << RESET; }
                else
                {
                  TicTacToe game{Board(size), numChrsToWin, PL_char, PL_char=='X'?'O':'X'};
                  std::cout << game;

                  if(__char==game.getAIchar())
                  {
                    Move bstMov = game.findBestMove();
                    std::cout << bstMov.x << " " << bstMov.y << "\n";

                    try { game.setField(bstMov.x, bstMov.y, game.getAIchar()); }
                    catch (const char* msg) { std::cerr << CZERWONY << msg << RESET "\n"; }

                    std::cout << game;
                  }

                  while(1)
                  {
                    if(!std::cin || !std::cin.eof())
                    {
                      std::cin.clear();
                      std::cin.ignore(100000,'\n');
                    }

                    std::cout << "Twoj ruch! Podaj wspolrzedne y x pola ktore chcesz zajac: (odzielone spacja, np. "
                    << BLUE << 2 << RESET << " " << GREEN << 1 << RESET << ")\n";

                    // wczytywanie wspolrzednych pola; jesli sie nie uda
                    int x(0), y(0);
                    if(!readCoordinates(&x, &y))
                    {
                      std::cout << CZERWONY << "Bledne wspolrzedne; sprobuj ponownie\n" << RESET;
                      continue;
                    }

                    try { game.setField(x,y,PL_char); }
                    catch (const char* msg) { std::cerr << CZERWONY << msg << RESET "\n"; continue; }

                    std::cout << game;

                    if(game.winConditionMet(PL_char) == PL_char)
                    {
                      std::cout << "Gracz wygral! Gra zakonczyla sie.\n";
                      break;
                    }
                    if(game.winConditionMet(PL_char) == '=')
                    {
                      std::cout << "Remis! Gra zakonczyla sie.\n";
                      break;
                    }

                    Move bstMov = game.findBestMove();

                    try { game.setField(bstMov.x, bstMov.y, game.getAIchar()); }
                    catch (const char* msg) { std::cerr << CZERWONY << msg << RESET "\n"; }

                    std::cout << game;

                    if(game.winConditionMet(game.getAIchar()) == game.getAIchar())
                    {
                      std::cout << "AI wygralo! Gra zakonczyla sie.\n";
                      break;
                    }
                    if(game.winConditionMet(PL_char) == '=')
                    {
                      std::cout << "Remis! Gra zakonczyla sie.\n";
                      break;
                    }
                  }
                }
              }
            }
          }
        }
        break;
        case 'm':
            wyswietlMenu();
            break;
        case 'k':
            std::cout << "Koniec dzialania programu\n";
            exit(0);
        default:
            std::cout << "Taka opcja nie istnieje; sprobuj ponownie\n";
            break;
        }
        std::cin.clear();
        std::cin.ignore(100000,'\n');
    }

    return 0;
}