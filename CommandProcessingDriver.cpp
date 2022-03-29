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
    
    list<Command>* commandList = processor->getCommandList(); // get the command of gameengine from its commandprocessor object
    myGame->startupPhase();

    //play phase:
     while(myGame->getStatus() == true){
    commandList->clear();
    if(myGame->fileReader){
        
        cout << "please enter a new file name:" <<endl;
        string newPath;
        getline(cin, newPath);
        processor->setPath(newPath);
    }
    //get a new command list:
    commandList = processor->getCommand();
    //For all the command it has:
    // validate each of them in current state
    // if it is valide, execute and save the effect
    // else, reject and save "INVALID COMMAND" 
    for(Command& command : *commandList){
        command.attach(lo);
        processor->validate(myGame, &command);
    }
    }
    
    //prevent memory leak:
    //delete myGame;  
    delete lo;                                                                                                                                                                                                                                                 
    return 0;
}