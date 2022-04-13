#include "CommandProcessing.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

ostream& operator<<(ostream& os, const Command& c) {
    return cout << "the name of the command is " << *(c._command) << endl
        << ", and the effect of the command is " << *(c._effect) << endl;
}

ostream& operator<<(ostream& os, const CommandProcessor& cp) {
    return cout << "the address of the command list is " << cp.commands_ptr << endl;

}
ostream& operator<<(ostream& os, const FileLineReader& flr) {
    return cout << "the path of the file line reader is " << *(flr._path) << endl;
}

ostream& operator<<(ostream& os, const FileCommandProcessorAdapter& fcpa) {
    return cout << "the path of the file command processor adaptor is " << *(fcpa._pathIn) << endl;
}
/*****************************************
 ******************Command****************
******************************************/
Command::Command() {
    _currentState = new string("ASDf");
}

//set a deefault effect to avoid segmentation fault:
Command::Command(string command) {
    _command = new string(command);
    string* defaultEffect = new string("no effect yet");
    _effect = defaultEffect;
    ILoggable::_currentState->assign(*_effect);
}

Command::~Command() {
    //delete this->_command;
    //delete this->_effect;
}

void Command::saveEffect(string nextState) {
    _effect = new string(nextState);
    ILoggable::_currentState->assign(*_effect);
    notify(this);
}

string Command::getCommandName() {
    if (_command) {
        return *_command;
    }
    else {
        return "error!!";
    }
}

string Command::getEffect() {
    if (_effect) {
        string effect = *_effect;
        return effect;
    }
    else {
        return "error!! Effect for this command has not been initialized!";
    }
}

string Command::stringToLog() {
    return "Command's Effect: Transitioning to state " + *ILoggable::_currentState;
}
//Deep copy constructor:
Command::Command(const Command& c) {
    this->_command = new string(*(c._command));
    this->_effect = new string(*(c._effect));
}
//operator:
Command& Command::operator = (const Command& c) {
    this->_command = new string(*(c._command));
    this->_effect = new string(*(c._effect));
    return *this;
}

/*****************************************
 *************CommandProcessor************
******************************************/
CommandProcessor::CommandProcessor() {
    command_in = new string("ASDFADSF");
    this->commands_ptr = new list<Command>();
    //a3
    this->_commands_map = new list<string>();
    this->_commands_players = new list<string>();
    this->_game_num = new string();
    this->_max_turn = new string();
    this->reject = false;
    this->tournament_mode = false;
    ILoggable::_currentState->assign("Initial");
}

CommandProcessor::~CommandProcessor() {
    delete this->commands_ptr; //avoid memory leak
    delete this->command_in;
    //a3
    delete this->_commands_map;
    delete this->_commands_players;
    delete this->_game_num;
    delete this->_max_turn;
}

void CommandProcessor::setPath(string newPath) {
    //placeholder
}

void CommandProcessor::readCommand() {
    string commands;
    cout << endl;
    cout << "Please enter your commands (please seperated your commands with space):" << endl;
    //used getline because commands are separated using spaces
    getline(cin, commands);
    command_in = new string(commands);
}

/************************
 * A3 TOURNAMENT helper
************************/
void CommandProcessor::tournamentHelper(string commandLine) {
    size_t map_index = commandLine.find("-M");
    size_t player_index = commandLine.find("-P");
    size_t game_num_index = commandLine.find("-G");
    size_t game_turn_index = commandLine.find("-D");
    this->reject = false;
    // make sure all options are entered:
    if (map_index == std::string::npos) {
        cout << "Please enter a valid list of map file from 1 to 5." << endl;
        this->reject = true;
        showHelpPage();
    }
    if (player_index == std::string::npos) {
        cout << "Please enter a valid list of player strategies from 2 to 4." << endl;
        this->reject = true;
        showHelpPage();
    }
    //validate game numbers
    if (game_num_index == std::string::npos) {
        cout << "Please enter a valid number of game you would like to play." << endl;
        this->reject = true;
        showHelpPage();
    }


    //validate game turns
    if (game_turn_index == std::string::npos) {
        cout << "Please enter a valid number of maximum truns you would like to have for each game." << endl;
        this->reject = true;
        showHelpPage();
    }

    // If have the command for all options, continue:
    if (!reject) {

        //get the map list:
        string mapCommands;
        try {
            mapCommands = commandLine.substr(map_index + 3, (player_index - 1) - (map_index + 3));
        }
        catch (out_of_range& e) {
            cout << "Please enter at least one map file." << endl;
            reject = true;
        }

        //get the player list:
        string playerCommand;
        try {
            playerCommand = commandLine.substr(player_index + 3, (game_num_index - 1) - (player_index + 3));
        }
        catch (out_of_range& e) {
            cout << "Please enter at least one player strategy." << endl;
            reject = true;
        }
        //get game number:
        string gameNum;
        try {
            gameNum = commandLine.substr(game_num_index + 3, 1);
            if (((game_turn_index - 1) - (game_num_index + 3)) > 1) {
                cout << "Please make sure you enter one number between 1 and 5 for -G." << endl;
                reject = true;
            }
        }
        catch (out_of_range& e) {
            cout << "Please enter a number for -G." << endl;
            reject = true;
        }
        //get max turn number:
        string maxTurn;
        try {
            maxTurn = commandLine.substr(game_turn_index + 3, 2);
            if (commandLine.substr(game_turn_index + 3).length() > 2) {
                cout << "Please make sure to enter one number between 10 and 50 for -D." << endl;
            }
        }
        catch (out_of_range& e) {
            cout << "Please enter a number for -D." << endl;
            reject = true;
        }

        // After second round of validation:
        if (!reject) {
            //Third round of validation:
            int gameNumInt = std::stoi(gameNum);
            if (gameNumInt > 5 || gameNumInt < 1) {
                this->reject = true;
                cout << "The number of games for each map has to be between 1 to 5" << endl;
            }
            int maxTurnInt = std::stoi(maxTurn);
            if (maxTurnInt > 50 || maxTurnInt < 10) {
                this->reject = true;
                cout << "The number of maximum turns for each game has to be between 10 to 50" << endl;
            }
            //save map files:
            stringstream ms(mapCommands);
            string map;
            while (ms >> map) {
                this->_commands_map->push_back(map);
            }
            //save player strategies:
            stringstream ps(playerCommand);
            string playerS;
            while (ps >> playerS) {
                this->_commands_players->push_back(playerS);
            }

            //save game number:
            this->_game_num = new string(gameNum);
            //save max turn:
            this->_max_turn = new string(maxTurn);
            this->turn_num = new string(maxTurn);
        }

    }
}
// SPECIAL NOTES HERE:
// If the command has a prefix as "loadmap" or "addplayer"
// sasvemap would stop adding it to the list until it reads the name
// of the mapfile or the name of the player
void CommandProcessor::saveCommand() {
    string commandLine = *command_in;
    string t_mode = commandLine.substr(0, 10);

    if (t_mode == "tournament") {
        /*******************
         * TOURNAMENT MODE
        ********************/
        this->tournament_mode = true;
        //save all info needed:
        tournamentHelper(commandLine);
        if (!reject) {
            //save all commands to commandlist:
            string replayCountStr = *_game_num;
            int replayCount = std::stoi(replayCountStr);
            for (string m : *_commands_map) {
                int mapReplayCount = replayCount;
                while (mapReplayCount > 0) {
                    //add the loadmap command:
                    commands_ptr->push_back(Command("loadmap " + m));
                    //add the vlidatemap command:
                    commands_ptr->push_back(Command("validatemap"));
                    //add all addplayer commands:
                    for (string p : *_commands_players) {
                        commands_ptr->push_back(Command("addplayer " + p));
                    }
                    //push game start:
                    commands_ptr->push_back(Command("gamestart"));
                    // push replay:
                    commands_ptr->push_back(Command("replay"));
                    mapReplayCount -= 1;
                }
                //replay the game with the next map:
                //commands_ptr->push_back(Command("replay"));
            }
            commands_ptr->pop_back();
            commands_ptr->push_back(Command("quit"));
        }
    }
    else {
        /*****************
         * REGULAR MODE
        ******************/
        this->tournament_mode = false;
        //use stringstream to seperate the command with "space"
        stringstream ss(commandLine);
        string prev_command;
        string oneCommand;
        while (ss >> oneCommand) {

            if (oneCommand != "loadmap" && oneCommand != "addplayer") {
                if (prev_command == "loadmap") {
                    (*commands_ptr).push_back(Command(("loadmap " + oneCommand)));
                    string newStateMap = "loadmap " + oneCommand;
                    ILoggable::_currentState->assign(newStateMap);
                    notify(this);
                }
                else if (prev_command == "addplayer") {
                    (*commands_ptr).push_back(Command(("addplayer " + oneCommand)));
                    string newStatePlayer = "addplayer " + oneCommand;
                    ILoggable::_currentState->assign(newStatePlayer);
                    notify(this);
                }
                else {
                    (*commands_ptr).push_back(Command(oneCommand));
                    ILoggable::_currentState->assign(oneCommand);
                    notify(this);
                }
            }
            prev_command = oneCommand;
        }
    }
    cout << "The size of the command list is: " << (*commands_ptr).size() << endl;

}


std::string CommandProcessor::stringToLog() {
    return "Command: " + *ILoggable::_currentState;
}

// command getCommand() read commands, and then save them to a list of Command objects
std::list<Command>* CommandProcessor::getCommand() {
    // As long as the command is rejected, we keep asking for new command:
    do {
        readCommand();
        saveCommand();
    } while (reject);

    return commands_ptr;
}

list<Command>* CommandProcessor::getCommandList() {
    return this->commands_ptr;
}

// If the command is valid, save the command's effect, 
// else save an error message
bool CommandProcessor::validate(GameEngine* myGame, Command* command) {
    
    if (myGame != NULL && command != NULL) {

        GameState* currentState = myGame->getCurrentState();

        string commandName = command->getCommandName();
        size_t pos1 = commandName.find(" ");
        string commandprefix = commandName.substr(0, pos1);

        //if the command is loadmap <mapfile> or addplayer <playername>
        // validate the prefix of the command:
        if (commandprefix == "loadmap" || commandprefix == "addplayer") {
            if (currentState->validate(commandprefix)) {
                cout << "The current command: " << commandName
                    << " is valid in current state: " << currentState->getName() << endl;
                myGame->transit(commandprefix);
                currentState = myGame->getCurrentState();
                command->saveEffect(currentState->getName());
                cout << "The effect of the command is:" << command->getEffect() << endl;
                return true;
            }
            else {
                cout << "The current command: " << commandName
                    << " is INVALID in current state: " << currentState->getName() << endl;
                command->saveEffect("INVALID COMMAND");
                cout << "The effect of the command is:" << command->getEffect() << endl;
            }
        }
        // else, validate the whole command:
        else {
            if (currentState->validate(commandName)) {
                cout << "The current command: " << commandName
                    << " is valid in current state: " << currentState->getName() << endl;
                myGame->transit(commandName);
                currentState = myGame->getCurrentState();
                command->saveEffect(currentState->getName());
                cout << "The effect of the command is:" << command->getEffect() << endl;
                return true;
            }
            else {
                cout << "The current command: " << commandName
                    << " is INVALID in current state: " << currentState->getName() << endl;
                command->saveEffect("INVALID COMMAND");
                cout << "The effect of the command is:" << command->getEffect() << endl;
            }
        }

    }
    else {
        cout << "uninitialized game detected!" << endl;
    }
    return false;
}

CommandProcessor::CommandProcessor(const CommandProcessor& cp) {
    this->command_in = new string(*(cp.command_in));
    this->commands_ptr = new list<Command>(*(cp.commands_ptr));
}

CommandProcessor& CommandProcessor::operator = (const CommandProcessor& cp) {
    this->command_in = new string(*(cp.command_in));
    this->commands_ptr = new list<Command>(*(cp.commands_ptr));
    return *this;
}

/****************************************
 * a3 methods:
*****************************************/
list<string>* CommandProcessor::getMapCommands() {
    return this->_commands_map;
}

list<string>* CommandProcessor::getPlayerCommands() {
    return this->_commands_players;
}

string* CommandProcessor::getGameNum() {
    return this->_game_num;
}

string* CommandProcessor::getMaxTurns() {
    return this->_max_turn;
}

void CommandProcessor::setMaxTurns(string newNum) {
    this->_max_turn = new string(newNum);
}

void CommandProcessor::showHelpPage() {

    cout << "Tournament Mode:" << endl;
    cout << "Use -M <listofmapfiles> to specify the list of maps;" << endl;
    cout << "Use -P <listofplayerstrategies> to specify the player strategies;" << endl;
    cout << "Use -G <numberofgames> to specify the number of games to play;" << endl;
    cout << "Use -D <maxnumberofturns> to specify the maximum turns for each game." << endl;

}
/*****************************************
 *******FileCommandProcessorAdapter*******
******************************************/
FileCommandProcessorAdapter::FileCommandProcessorAdapter() {}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(string pathIn) {
    this->_pathIn = new string(pathIn);
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    delete this->_pathIn;
}

void FileCommandProcessorAdapter::setPath(string newPath) {
    this->_pathIn = new string(newPath);
}
void FileCommandProcessorAdapter::readCommand() {
    string str_path;
    if (reject) {
        cout << "Please enter a new file name: " << endl;
        cin >> str_path;
    }
    else {
        str_path = *_pathIn;
    }

    flr = new FileLineReader(str_path);
    string* commandsFile = new string(flr->readLineFromFile());
    command_in = commandsFile;
    delete(flr);
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& fcpa) {
    this->_pathIn = new string(*(fcpa._pathIn));
    this->flr = new FileLineReader(*(fcpa.flr));
}

FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator= (const FileCommandProcessorAdapter& fcpa) {
    this->_pathIn = new string(*(fcpa._pathIn));
    this->flr = new FileLineReader(*(fcpa.flr));
    return *this;
}
/*****************************************
 ****************LineReader***************
******************************************/
FileLineReader::FileLineReader() {}

FileLineReader::FileLineReader(string path) {
    this->_path = new string(path);
}

FileLineReader::~FileLineReader() {
    delete _path;
}

string FileLineReader::readLineFromFile() {
    string command;
    string line;

    bool valid;

    do {

        ifstream fileIn(*_path);

        valid = fileIn.is_open();

        if (fileIn.is_open()) {
            while (getline(fileIn, line)) {
                command = command + " " + line;
            }
            fileIn.close();
        }
        else {
            cout << "The file you entered does not exist!!" << endl;
            cout << "please enter a new file name:" << endl;

            string newPath;
            getline(cin, newPath);
            this->_path = new string(newPath);
        }
    } while (!valid);
    //delete the extra space:
    command = command.substr(1);
    return command;
}

string FileLineReader::getPath() {
    if (_path) {
        string strPath = *_path;
        return strPath;
    }
    else {
        return "no path";
    }
}

FileLineReader::FileLineReader(const FileLineReader& flr) {
    this->_path = new string(*(flr._path));
}

FileLineReader& FileLineReader::operator = (const FileLineReader& flr) {
    this->_path = new string(*(flr._path));
    return *this;

}