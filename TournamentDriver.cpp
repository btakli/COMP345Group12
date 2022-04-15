#include "CommandProcessing.h"
#include "GameEngine.h"
#include <iostream>

using namespace std;

void main_menu();

int main(){
    LogObserver* lo = new LogObserver();
    //string input_option;
    GameEngine* myGame; // create a new game
    myGame = new GameEngine(); // initialize the game
    myGame->attach(lo);
    CommandProcessor* processor = myGame->getCommandProcessor();
    
    list<Command>* commandList = processor->getCommandList(); // get the command of gameengine from its commandprocessor object
    myGame->get_all_map_commands();
    for (Command& command : *commandList) {
        command.attach(lo);
        processor->validate(myGame, &command);
    }
    cout << "Game Result:" << *myGame->getResult() <<endl;
    //prevent memory leak:
    delete myGame;  
    delete lo;                                                                                                                                                                                                                                                 
    return 0;
}
