#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <cstdlib>
#include "Ship.h"

using namespace std;

class Player {
    public:
        Player();
        virtual void setFiringBoardValue(int x, int y, char c);
        virtual void setShipBoardValue(int x, int y, char c);
        virtual void printBoards(bool showCursor);
        virtual void printShipBoard();
        virtual void setSystemColor(int x, int y, char board[9][9]);
        virtual void placeShips();
        virtual void changeCurrentPosition(char input);
        virtual bool isCurrentLocation(int x, int y);
        virtual void buildShipsArray();
        virtual bool placeCurrentBoatAtCurrentPosition(int index);
        virtual void copyBoard(char from[9][9], char to[9][9]);
        virtual bool hasHealth();
        virtual bool isHit(int x, int y);
        virtual pair<int, int> fireShot();
    private:
        HANDLE hConsole;
        int health;
        pair<int, int> currentLocation;
        char firingBoard[9][9];
        char shipBoard[9][9];
        char resetBoard[9][9];
        Ship* ships[5];
        bool placingShipsPhase;
};
#endif
