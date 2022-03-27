#include "CommandProcessing.h"
//#include "GameEngine.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

/*****************************************
 ******************Command****************
******************************************/
Command::Command(){

}  

Command::Command(string command){
    _command = new string(command);
    string* defaultEffect = new string("no effect yet");
    _effect = defaultEffect;
}

Command::~Command(){}

void Command::saveEffect(string nextState){
    string errorMessage = "THE COMMAND IS INVALID";
    _effect = &nextState;
}

string Command::getCommandName(){
    if(_command){
        //string command = *_command;
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
        return "error!!";
    } 
}

Command::Command(const Command &c){
    this->_command = new string(*(c._command));
    this->_effect = new string(*(c._effect));
}

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
    delete this->commands_ptr;
}

void CommandProcessor::readCommand(){
    string commands;
    cout << endl;
    cout << "Please enter your commands (please seperated your commands with space):" << endl;
    //used getline because commands are separated using spaces
    //testing:
    commands = "loadmap loadmap mymap haha";
    command_in = &commands;
    /*getline(cin, commands);
    command_in = &commands;*/
}

void CommandProcessor::saveCommand(){
    //list<Command> commands;
    //commands_ptr = &commands;
    //new command:

    if(command_in){
        string commandLine = *command_in;
        //use stringstream to seperate the command with "space"
        stringstream ss (commandLine);
        string oneCommand;
        while (ss >> oneCommand){
            //create a new Command object
            /*Command* newCommand = new Command(oneCommand);
            Command* current = newCommand;*/
            //push the Command object to the list
            //cout << "current command is:" << oneCommand << endl;
            (*commands_ptr).push_back(Command(oneCommand));
        }
        cout << "The size of the list is: " << (*commands_ptr).size() << endl;
    }else{
        cout << "error!! no commands received!!" << endl;
    }
    /*list<Command>::iterator itConsole;
    itConsole = commands_ptr->begin();
    cout << "The begin() gives us: " << itConsole->getCommandName() << endl;
    itConsole++;
    cout << "The begin() gives us: " << itConsole->getCommandName() << endl;
    cout << "The front() gives us: " << (commands_ptr->front()).getCommandName() << endl;
    cout << "The back() gives us: " << (commands_ptr->back()).getCommandName() << endl;*/
    
}
std::list<Command>* CommandProcessor::getCommand(){
    readCommand();
    saveCommand();
    return commands_ptr;
}

// If the command is valid, save the command's effect, 
// else save an error message
bool CommandProcessor::validate(GameEngine* myGame, Command* command){
    if(myGame != NULL && command != NULL){
    cout << "validating" << endl; 
    // Note: We made a copy of myGame but not command
    // because we don't want to modify the value of the input
    // game, but we want to save the effect of the input command
    // if the command string is valid 
    //GameEngine* copy = new GameEngine(*myGame);
    GameState* currentState;
    currentState = myGame->getCurrentState();

    string* commandName = new string(command->getCommandName());
    //list<Command>::iterator it;
    //for(it = commands_ptr->begin() ; it != commands_ptr->end(); it++){
        //string currentCommand;
        //currentCommand = it->getCommandName();
        //cout << currentCommand << endl;

        //Note: from grading sheet:
        //"For valid command, it results in correct effect and state change"
        if(currentState->validate(*commandName)){
            cout << "The current command: " << *commandName 
            << " is valid in current state: " << currentState->getName() << endl;
            myGame->transit(*commandName);
            currentState = myGame->getCurrentState();
            command->saveEffect(currentState->getName());
            cout << "The effect of the command is:" << command->getEffect() << endl;
            return true;
        }else{
            cout << "The current command: " << commandName 
            << " is INVALID in current state: " << currentState->getName() << endl;
            command->saveEffect("INVALID COMMAND");
            cout << "The effect of the command is:" << command->getEffect() << endl;
        //}
    }
    //delete copy;
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

FileCommandProcessorAdapter::~FileCommandProcessorAdapter(){}

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
    GameEngine* myGame;
    myGame = new GameEngine();
    CommandProcessor* processor = myGame->getCommandProcessor();
    list<Command>* commandList = processor->getCommand();
    //while(myGame->getStatus() == true && commandList->empty() == false){
        
        for(Command& command : *commandList){
            processor->validate(myGame, &command);
                //if validated:
                //myGame->transit(command.getCommandName());
            }
        
    //}
    /*CommandProcessor* cp = new CommandProcessor();
    
    cout << endl;
    cout << "How would you like to input commands?" << endl;
    cout << "Please choose from the following:" << endl;
    cout << "1. -console" << endl;
    cout << "2. -file <filename>" <<endl;
    //getline(cin, input_option);
    //input_option = "-console";
    input_option = "-file <command.txt>";
    string option_prefix = input_option.substr(0, 5);
    if(input_option == "-console"){
        list<Command>* l1 = cp->getCommand();
        //loop through the list:
        list<Command>::iterator itConsole;
        try{
            for(itConsole = l1->begin(); itConsole != l1->end();itConsole++){
                cout << "current command is: " << itConsole -> getCommandName() << endl;
            }
        }catch(const std::bad_alloc&){
            cout << "Out of memory!!" << endl;
            return -1;
        }
        l1->clear();
    }else if(option_prefix == "-file"){
        cout << "get here" <<endl;
        size_t pos = input_option.find("<");
        size_t pos2 = input_option.find(">");
        int length = pos2 - pos - 1;
        string pathIn = input_option.substr(pos+1, length);
        cout << "path name is:" << pathIn << endl;
        FileCommandProcessorAdapter* fcpa = new FileCommandProcessorAdapter(pathIn);
        list<Command>* l2 = fcpa->getCommand();
         //case #1 Start State:
        cout << "before validation: " << myGame->getCurrentState()->getName() << endl; 
        fcpa->validate(myGame);
        cout << "after validation: " << myGame->getCurrentState()->getName() << endl;
        //loop through the list:
        list<Command>::iterator itFile;
        for(itFile = l2->begin(); itFile != l2->end(); ++itFile){
            cout << itFile -> getCommandName() << endl;
        }
       
         while(myGame->getStatus() == true){
             
         }
        delete fcpa;   
    }else{
        cout << "Please enter a correct option." << endl;
    }
    

    delete cp;   */                                                                                                                                                                                                                                                                                             
    return 0;
}