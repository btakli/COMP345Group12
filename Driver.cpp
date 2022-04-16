#include "CommandProcessing.h"
#include "GameEngine.h"
#include <iostream>

using namespace std;

int main(){
    LogObserver* lo = new LogObserver();
    
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
    if(processor->tournament_mode){
        cout << "Game Result:" << *myGame->getResult() <<endl;
    }
    //prevent memory leak:
    delete myGame;  
    delete lo;                                                                                                                                                                                                                                                 
    return 0;
}
