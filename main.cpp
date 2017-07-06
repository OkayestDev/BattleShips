#include <iostream>
#include "Player.cpp"

using namespace std;

void switchNotification() {
    system("cls");
    cout<<"Switching players.....press enter to continue"<<endl;
    cin.get();
    system("cls");
}

int main() {
    Player playerOne;
    playerOne.placeShips();
    playerOne.printBoards(false);
    cout<<"Switching players.....press enter to continue"<<endl;
    cin.get();

    system("cls");
    cout<<"Press enter to begin placing boats for player two"<<endl;
    cin.get();

    Player playerTwo;
    playerTwo.placeShips();
    playerTwo.printBoards(false);

    cout<<"Switching players.....press enter to continue"<<endl;
    cin.get();

    system("cls");
    cout<<"Beginning game, Player one will fire first.....press enter to continue"<<endl;
    cin.get();

    while (playerOne.hasHealth() && playerTwo.hasHealth()) {// Game sequence begins here - both players have boats/health left
        pair<int, int> shotFired;

        shotFired = playerOne.fireShot();
        if (playerTwo.isHit(shotFired.first, shotFired.second)) {
            playerOne.setFiringBoardValue(shotFired.first, shotFired.second, 'H');
            playerTwo.setShipBoardValue(shotFired.first, shotFired.second, 'H');
        }
        else {
            playerOne.setFiringBoardValue(shotFired.first, shotFired.second, 'M');
            playerTwo.setShipBoardValue(shotFired.first, shotFired.second, 'M');
        }

        playerOne.printBoards(false);
        Sleep(1000);

        if (!playerTwo.hasHealth()) {
            break;
        }

        switchNotification();

        shotFired = playerTwo.fireShot();
         if (playerOne.isHit(shotFired.first, shotFired.second)) {
            playerTwo.setFiringBoardValue(shotFired.first, shotFired.second, 'H');
            playerOne.setShipBoardValue(shotFired.first, shotFired.second, 'H');
        }
        else {
            playerTwo.setFiringBoardValue(shotFired.first, shotFired.second, 'M');
            playerOne.setShipBoardValue(shotFired.first, shotFired.second, 'M');
        }
        playerTwo.printBoards(false);
        Sleep(1000);
        switchNotification();
    }

    if (playerOne.hasHealth()) {
        system("cls");
        cout<<"Player one wins!!!!"<<endl;
        cout<<"Player one's board:"<<endl;
        playerOne.printShipBoard();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout<<"Player two's board:"<<endl;
        playerTwo.printShipBoard();
    }
    else {
        system("cls");
        cout<<"Player two wins!!!!"<<endl;
        cout<<"Player two's board:"<<endl;
        playerTwo.printShipBoard();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout<<"Player one's board:"<<endl;
        playerOne.printShipBoard();
    }
}
