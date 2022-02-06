#include <iostream>

#include "Player.h"


int main() {
    Player  *p = new Player();
    delete(p);

    cout << *p << endl;

    return 0;
}