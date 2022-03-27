#include "CommandProcessing.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

/*****************************************
 ******************Command****************
******************************************/
Command::Command(){

}  

//set a deefault effect to avoid segmentation fault:
Command::Command(string command){
    _command = new string(command);
    string* defaultEffect = new string("no effect yet");
    _effect = defaultEffect;
}

Command::~Command(){
    delete this->_command;
    delete this->_effect;
}

void Command::saveEffect(string nextState){
    _effect = &nextState;
}

string Command::getCommandName(){
    if(_command){
        return *_command;
    }else{
        return "error!!";
    }
}

string Command::getEffect(){
    if(_effect){
        string effect = *_effect;
        return effect;
    }else{
        return "error!! Effect for this command has not been initialized!";
    } 
}

//Deep copy constructor:
Command::Command(const Command &c){
    this->_command = new string(*(c._command));
    this->_effect = new string(*(c._effect));
}
//operator:
Command& Command::operator = (const Command& c){
    this->_command = new string(*(c._command));
    this->_effect = new string(*(c._effect));
    return *this;
}

/*****************************************
 *************CommandProcessor************
******************************************/
CommandProcessor::CommandProcessor(){
    command_in = new string("ASDFADSF");
    this->commands_ptr = new list<Command>();
}

CommandProcessor::~CommandProcessor(){
    delete this->commands_ptr; //avoid memory leak
    delete this->command_in;
}

void CommandProcessor::readCommand(){
    string commands;
    cout << endl;
    cout << "Please enter your commands (please seperated your commands with space):" << endl;
    //used getline because commands are separated using spaces
    getline(cin, commands);
    command_in = &commands;
}

// SPECIAL NOTES HERE:
// If the command has a prefix as "loadmap" or "addplayer"
// sasvemap would stop adding it to the list until it reads the name
// of the mapfile or the name of the player
void CommandProcessor::saveCommand(){
    if(command_in){
        string commandLine = *command_in;
        //use stringstream to seperate the command with "space"
        stringstream ss (commandLine);
        string prev_command;
        string oneCommand;
        while (ss >> oneCommand){
            if(oneCommand != "loadmap" && oneCommand != "addplayer"){
                if(prev_command == "loadmap"){
                    (*commands_ptr).push_back(Command(("loadmap "+ oneCommand)));
                }else if(prev_command == "addplayer"){
                    (*commands_ptr).push_back(Command(("addplayer " + oneCommand)));
                }else{
                    (*commands_ptr).push_back(Command(oneCommand));
                }
             }
             prev_command = oneCommand;
        }
        cout << "The size of the list is: " << (*commands_ptr).size() << endl;
    }else{
        cout << "error!! no commands received!!" << endl;
    }
}

// command getCommand() read commands, and then save them to a list of Command objects
std::list<Command>* CommandProcessor::getCommand(){
    readCommand();
    saveCommand();
    return commands_ptr;
}

// If the command is valid, save the command's effect, 
// else save an error message
bool CommandProcessor::validate(GameEngine* myGame, Command* command){
    if(myGame != NULL && command != NULL){
    GameState* currentState;
    currentState = myGame->getCurrentState();

    string* commandName = new string(command->getCommandName());
    cout << *commandName <<endl;
    size_t pos1 = (*commandName).find(" ");
    size_t pos2 = 0;
    int length = pos1 - pos2;
    string commandprefix = (*commandName).substr(0, length);
    //if the command is loadmap <mapfile> or addplayer <playername>
    // validate the prefix of the command:
    if(commandprefix == "loadmap" || commandprefix == "addplayer"){
        if(currentState->validate(commandprefix)){
            cout << "The current command: " << *commandName
            << " is valid in current state: " << currentState->getName() << endl;
            myGame->transit(commandprefix);
            currentState = myGame->getCurrentState();
            command->saveEffect(currentState->getName());
            cout << "The effect of the command is:" << command->getEffect() << endl;
            return true;
        }else{
            cout << "The current command: " << *commandName 
            << " is INVALID in current state: " << currentState->getName() << endl;
            command->saveEffect("INVALID COMMAND");
            cout << "The effect of the command is:" << command->getEffect() << endl;
        }
    }
    // else, validate the whole command:
    else{
        if(currentState->validate(*commandName)){
            cout << "The current command: " << *commandName 
            << " is valid in current state: " << currentState->getName() << endl;
            myGame->transit(*commandName);
            currentState = myGame->getCurrentState();
            command->saveEffect(currentState->getName());
            cout << "The effect of the command is:" << command->getEffect() << endl;
            return true;
        }else{
            cout << "The current command: " << *commandName 
            << " is INVALID in current state: " << currentState->getName() << endl;
            command->saveEffect("INVALID COMMAND");
            cout << "The effect of the command is:" << command->getEffect() << endl;
         }
    }
        
    }else{
        cout << "uninitialized game detected!" << endl;
    }
    return false;
}

/*****************************************
 *******FileCommandProcessorAdapter*******
******************************************/
FileCommandProcessorAdapter::FileCommandProcessorAdapter(){}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(string pathIn){
    this->_pathIn = new string(pathIn);
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter(){
    delete this->_pathIn;
}

void FileCommandProcessorAdapter::readCommand(){
    string str_path = *_pathIn;
    flr = new FileLineReader(str_path);
    string* commandsFile = new string(flr->readLineFromFile());
    command_in = commandsFile;
    delete(flr);
}

/*****************************************
 ****************LineReader***************
******************************************/
FileLineReader::FileLineReader(){}

FileLineReader::FileLineReader(string path){
    this->_path = new string (path);
}

FileLineReader::~FileLineReader(){
    delete _path;
}

string FileLineReader::readLineFromFile(){
    ifstream fileIn(*_path);
    string command;
    string line;
    if(fileIn.is_open()){
        while(getline(fileIn,line)){
            command = command + " " + line;
        }
        fileIn.close();
    }else{
        cout << "The file you entered does not exist!!" << endl;
    }
    return command;
}

string FileLineReader::getPath(){
    if(_path){
        string strPath = *_path;
        return strPath;
    }else{
        return "no path";
    }
}

int main(){
    //string input_option;
    GameEngine* myGame; // create a new game
    myGame = new GameEngine(); // initialize the game
    CommandProcessor* processor = myGame->getCommandProcessor();
    list<Command>* commandList = processor->getCommand(); // get the command of gameengine from its commandprocessor object
    //For all the command it has:
    // validate each of them in current state
    // if it is valide, execute and save the effect
    // else, reject and save "INVALID COMMAND" 
    for(Command& command : *commandList){
        processor->validate(myGame, &command);
    }



    /*
    
        Startup phase? - Yu

    */
    


    //prevent memory leak:
    //delete myGame;                                                                                                                                                                                                                                                   
    return 0;
}