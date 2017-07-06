#ifndef SHIP_H_INCLUDED
#define SHIP_H_INCLUDED
using namespace std;
class Ship {
    public:
        Ship();
        Ship(string name, int health) {
            this->name = name;
            this->health = health;
            orientation = 'v';
        }

        void decreaseHealth() { health--; }
        void setStartingPosition(pair<int, int> currentLocation) { startingPosition = currentLocation; }

        void changeOrientation() {
            if (orientation == 'v') {
                orientation = 'h';
            }
            else {
                orientation = 'v';
            }
        }

        void printBoatInfo() {
            cout<< "Currently placing " << name << " with a size of " << health << endl;
            cout<< "Current orientation ";
            if (orientation == 'v') {
                cout<<"vertical"<<endl;
            }
            else {
                cout<<"horizontal"<<endl;
            }
        }

        string getName() { return name; }
        int getHealth() { return health; }
        char getOrientation() { return orientation; }
        pair<int, int> getStartingPosition() { return startingPosition; }
    private:
        string name;
        int health;
        char orientation;
        pair<int, int> startingPosition = make_pair(0, 0);
};
#endif // SHIP_H_INCLUDED
