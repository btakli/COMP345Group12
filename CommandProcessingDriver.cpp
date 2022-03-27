#include "CommandProcessing.h"
#include "GameEngine.h"
#include <iostream>

using namespace std;

int main(){
    LogObserver* lo = new LogObserver();
    //string input_option;
    GameEngine* myGame; // create a new game
    myGame = new GameEngine(); // initialize the game
    myGame->attach(lo);
    CommandProcessor* processor = myGame->getCommandProcessor();
    processor->attach(lo);
    cout << "line 15" <<endl;
    list<Command>* commandList = processor->getCommand(); // get the command of gameengine from its commandprocessor object
    
    //For all the command it has:
    // validate each of them in current state
    // if it is valide, execute and save the effect
    // else, reject and save "INVALID COMMAND" 
    cout << "got commands" << endl;
    for(Command& command : *commandList){
        command.attach(lo);
        processor->validate(myGame, &command);
    }
    //prevent memory leak:
    //delete myGame;  
    delete lo;                                                                                                                                                                                                                                                 
    return 0;
}