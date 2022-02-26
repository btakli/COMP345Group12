#include  "GameEngine.h"
#include <iostream>
using namespace std;

int main(){
    string command;
    GameEngine* myGame;
    myGame = new GameEngine();
    while(myGame->getStatus() == true){
        myGame->getCurrentState()->toString();
        cout << endl;
        //test the stream insertion operator for Game States
        myGame->getCurrentState()->commandMessage();
        cout << endl;
        cout << "Please enter a command:";
        cin >> command;
        myGame->transit(command);
        cout << endl << "_____________________________________"<< endl;
        cout << endl;
    }
    delete myGame;
    return 0;    
}