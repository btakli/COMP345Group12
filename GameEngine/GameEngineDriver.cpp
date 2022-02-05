#include "GameEngine.h"
#include <iostream> 
using namespace std; 

int main(){
    string command;
    Game* myGame;
    myGame = new Game();
    while(myGame->getStatus() == true){
        cout << "Please enter a command:";
        cin >> command;
        myGame->transition(command);
    }
    return 0;    
}