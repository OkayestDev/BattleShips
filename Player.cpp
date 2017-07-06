#include <iostream>
#include <conio.h>
#include <cstdio>
#include <windows.h>
#include "Player.h"
#include "Ship.h"

using namespace std;

/**
construct empty boards and boats
*/
Player::Player() {
    buildShipsArray();
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            firingBoard[i][j] = '~';
        }
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
           shipBoard[i][j] = '~';
        }
    }
    health = 17;
    placingShipsPhase = true;
}

void Player::buildShipsArray() {
    ships[4] = new Ship("Carrier", 5);
    ships[3] = new Ship("Battleship", 4);
    ships[2] = new Ship("Cruiser", 3);
    ships[1] = new Ship("Submarine", 3);
    ships[0] = new Ship("Destroyer", 2);
}

void Player::placeShips() {
    int boatCount = 4;
    while (boatCount >= 0) {
        printBoards(true);
        ships[boatCount]->printBoatInfo();
        char input = getch();
        if (input == 'X' || input =='x') {
            if (placeCurrentBoatAtCurrentPosition(boatCount)) {
                boatCount--;
            }
            else {
                SetConsoleTextAttribute(hConsole, 12);
                cout<<"Invalid ship placement"<<endl;
                Sleep(1000);
            }
        }
        else if (input == 'Z' || input == 'z') {
            ships[boatCount]->changeOrientation();
        }
        else {
            changeCurrentPosition(input);
        }
    }
    placingShipsPhase = false;
}

bool Player::placeCurrentBoatAtCurrentPosition(int index) {
    Ship* currentShip = ships[index];
    currentShip->setStartingPosition(currentLocation);
    int x = currentLocation.first;
    int y = currentLocation.second;
    copyBoard(resetBoard, shipBoard);
    if (currentShip->getOrientation() == 'v') {
        for (int i = 0; i < currentShip->getHealth(); i++) {
            if (shipBoard[x + i][y] == 'B' || x + i > 8) {
                copyBoard(shipBoard, resetBoard);
                return false;
            }
            else {
                shipBoard[x + i][y] = 'B';
            }
        }
    }
    else {
        for (int i = 0; i < currentShip->getHealth(); i++) {
            if (shipBoard[x][y + i] == 'B' || y + i > 8) {
                cout<<"Invalid placement of ship"<<endl;
                copyBoard(shipBoard, resetBoard);
                return false;
            }
            else {
                shipBoard[x][y + i] = 'B';
            }
        }
    }
    return true;
}

pair<int, int> Player::fireShot() {
    currentLocation = make_pair(0, 0);
    while(true) {
        printBoards(true);
        char input = getch();
        if (input == 'X' || input == 'x') {
            return currentLocation;
        }
        else {
            changeCurrentPosition(input);
        }
    }
}

void Player::copyBoard(char to[9][9], char from[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            to[i][j] = from[i][j];
        }
    }
}

/**
change the location of the current player's cursor
*/
void Player::changeCurrentPosition(char input) {
    int x = currentLocation.first;
    int y = currentLocation.second;
    switch (input) {
    case 'A': case 'a':
        if (y != 0) {
            y--;
        }
        break;
    case 'W': case 'w':
        if (x != 0) {
            x--;
        }
        break;
    case 'S': case 's':
        if (x != 8) {
            x++;
        }
        break;
    case 'D': case 'd':
        if (y != 8) {
            y++;
        }
        break;
    }
    currentLocation = make_pair(x, y);
}

/**
Print boats, hits, and misses on both boards
*/
void Player::printBoards(bool showCursor) {
    system("cls");
    SetConsoleTextAttribute(hConsole, 7);
    cout<<"use WASD to move around the board, X as input, and Z to change orientation"<<endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            setSystemColor(i, j, firingBoard);
            if (placingShipsPhase == false && isCurrentLocation(i, j) && showCursor) {
                SetConsoleTextAttribute(hConsole, 5);
                cout<<'X'<<" ";
            }
            else {
                cout<<firingBoard[i][j]<<" ";
            }
        }
        cout<<endl;
    }
    SetConsoleTextAttribute(hConsole, 7);
    cout<<"-----------------"<<endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            setSystemColor(i, j, shipBoard);
            if (placingShipsPhase && isCurrentLocation(i, j) && showCursor) {
                SetConsoleTextAttribute(hConsole, 5);
                cout<<'X'<<" ";
            }
            else {
                cout<<shipBoard[i][j]<<" ";
            }
        }
        cout<<endl;
    }
    SetConsoleTextAttribute(hConsole, 7);
}

bool Player::isCurrentLocation(int x, int y) {
    if (currentLocation.first == x && currentLocation.second == y) {
        return true;
    }
    return false;
}

void Player::setSystemColor(int x, int y, char board[9][9]) {
    switch (board[x][y]) {
        case '~':
            SetConsoleTextAttribute(hConsole, 3); //aqua
            break;
        case 'B':
            SetConsoleTextAttribute(hConsole, 4); //grey
            break;
        case 'M':
            SetConsoleTextAttribute(hConsole, 7); //white
            break;
        case 'H':
            SetConsoleTextAttribute(hConsole, 12); //red
            break;
    }
}

bool Player::hasHealth() {
    if (health == 0) {
        return false;
    }
    return true;
}

void Player::setFiringBoardValue(int x, int y, char c) {
    firingBoard[x][y] = c;
}

void Player::setShipBoardValue(int x, int y, char c) {
    shipBoard[x][y] = c;
}

bool Player::isHit(int x, int y) {
    if (shipBoard[x][y] == 'B') {
        health--;
        return true;
    }
    return false;
}

void Player::printShipBoard() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            setSystemColor(i, j, shipBoard);
            cout<<shipBoard[i][j]<<" ";
        }
        cout<<endl;
    }
}
