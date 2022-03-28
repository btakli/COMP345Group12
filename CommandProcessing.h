//To prevent mutiple inclusion:
#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H

#include "GameEngine.h"
#include "LoggingObserver.h"
#include <string>
#include <list>

class GameEngine;
//Command class:
class Command : public ILoggable, public Subject
{
    public:
    //Default constructor:
    Command();
    //Destructor:
    ~Command();
    //Command that has a specific command name and a default effect:
    Command(std::string command);
    //save the effect:
    void saveEffect(string nextState);
    // returns the name of the command as a string
    std::string getCommandName();
    // returns the name of the effect as a string
    std::string getEffect();
    //logger function:
    std::string stringToLog();
    //copy constructor:
    Command(const Command &c);
    //assignment operator:
    Command& operator = (const Command& c);

    //stream insertion operator:
    friend ostream& operator<<(ostream& os, const Command& c);

    private:
    std::string* _command;
    std::string* _effect;
};

//CommandProcessor:
/*
 * The CommandProcessor class.
 * This is the Target class. 
*/
class CommandProcessor: public ILoggable, public Subject
{
    public:
    //Default constructor:
    CommandProcessor();
    //Destructor:
    virtual ~CommandProcessor();
    //getCommand function that read command and save them to the list
    //of command:
    std::list<Command>* getCommand();
    //Validate a command on curernt state:
    bool validate(GameEngine* myGame, Command* command);
    
    //returns the command list pointer
    list<Command>* getCommandList();

    //Logger function:
    std::string stringToLog();
    //copy constructor
    CommandProcessor(const CommandProcessor &cp);
    //assignment operator:
    CommandProcessor& operator = (const CommandProcessor& cp);

    //stream insertion operator:
    friend ostream& operator<<(ostream& os, const CommandProcessor& cp);

    protected:
    //implemented as virtual function so it would work for both console
    // and file inputs:
    virtual void readCommand();
    void saveCommand();
    std::string* command_in;
    std::list<Command>* commands_ptr;
};

//FileLineReader
/*
 * The FileLineReader class.
 * This is the Adaptee class.
*/
class FileLineReader
{
    public:
    //default constructor:
    FileLineReader();
    //Constructor with a file path explicitly inputed
    FileLineReader(std::string path);
    //Destructor:
    ~FileLineReader();
    // Used to read line from the file and get everthing into 
    // a single string:
    std::string readLineFromFile();
    //returns the path that the fileLineReader is reading
    std::string getPath();

    //copy constructor
    FileLineReader(const FileLineReader &flr);
    //assignment operator:
    FileLineReader& operator = (const FileLineReader& flr);

    //stream insertion operator:
    friend ostream& operator<<(ostream& os, const FileLineReader& flr);

    private:
    std::string* _path;
};

//FileCommandProcessorAdapter:
/*
 * The FileCommandProcessorAdaptor class.
 * This is the adapter class.
 * It adapts a CommandProcessor to a FileLineReader. 
 * Its interface is CommandProcessor.
*/
class FileCommandProcessorAdapter : public CommandProcessor
{
    public:
    //Default Constructor
    FileCommandProcessorAdapter();
    //Destructor:
    ~FileCommandProcessorAdapter();
    //Processes a specific file:
    FileCommandProcessorAdapter(std::string pathIn);

    //copy constructor
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter &fcpa);
    //assignment operator:
    FileCommandProcessorAdapter& operator = (const FileCommandProcessorAdapter& fcpa);

    //stream insertion operator:
    friend ostream& operator<<(ostream& os, const FileCommandProcessorAdapter& fcpa);

    protected:
    void readCommand();
    //file lien reader is called to read command from file:
    FileLineReader* flr;
    std::string* _pathIn;
};



#endif